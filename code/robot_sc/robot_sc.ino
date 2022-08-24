#include <DynamixelSerial.h>


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int panPos,tiltPos;
int pan=1;
int tilt=2;
int servoPin=2;
int start=500;
byte inByte = 0;         // incoming serial byte
bool expectingDrumPin=false,expectingDrumOnOff=false;
bool expectingServoID=false,expectingServoPos=false,expectingServoSpeed=false;
bool notExpecting=true;
int drumPin;
int servoID=1, servoPos=900,servoSpeed=100;
bool onOff=false;
int ctr=0;

void setup()
{

  Serial.begin(115200);
  
  for(int i=0;i<14;i++) 
  {
      pinMode(i, OUTPUT); 
  }  
  inputString.reserve(200);

  delay(1000);

}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available()>0) 
  {
//    //SIGNIFIER    
    if(inputString=="strike") 
    {
      digitalWrite(13, HIGH);
      expectingDrumPin=true;
      notExpecting=false;
    } 
    else if (inByte==15 && notExpecting) 
    {
      expectingServoID=true;
      notExpecting=false;
    } 
    else if(expectingDrumPin) 
    {
      drumPin=inputString.toInt();
      expectingDrumPin=false;
      expectingDrumOnOff=true;
    } 
    else if(expectingDrumOnOff) 
    {
      expectingDrumOnOff=false;
      notExpecting=true;
      if(inputString.toInt()>0) 
      {
        digitalWrite(drumPin,HIGH);
      } 
      else 
      {
        digitalWrite(drumPin,LOW);
      }
    } 
    else if(expectingServoID) 
    {
      expectingServoID=false;
      expectingServoPos=true;
      servoID=(int)inByte;
    } 
    else if(expectingServoPos) 
    {
      expectingServoPos=false;
      expectingServoSpeed=true;
      servoPos=(int)inByte;
    } 
    else if(expectingServoSpeed) 
    {
      expectingServoSpeed=false;
      notExpecting=true;
      servoSpeed=(int)inByte;
      Serial.end();  
      Dynamixel.begin(1000000,servoPin);
      delay(10);
      moveServo(servoID,servoPos,servoSpeed);
      Dynamixel.end();  
      Serial.begin(115200);
      delay(10);
    }
    inputString="";
  }
}

void moveServo(int iD,int pos, int sp) 
{
 Dynamixel.moveSpeed(iD,pos,sp);
}


