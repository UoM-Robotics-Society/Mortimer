
const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

const int SnareTime = 50;
const int BassTime = 90;
const int CymbalTime = 90;
const int DelayTime = 1000;


void setup() 
{
    // Begin USB Serial
    Serial.begin(9600);

    pinMode(SnarePin, OUTPUT);
    pinMode(BassPin, OUTPUT);
    pinMode(CymbalPin, OUTPUT);

    digitalWrite(SnarePin,LOW);
    digitalWrite(BassPin,LOW);
    digitalWrite(CymbalPin,LOW);
    
}

void loop() 
{
    digitalWrite(SnarePin,HIGH);
    delay(SnareTime);
    digitalWrite(SnarePin,LOW);
    
    delay(DelayTime);

//    digitalWrite(BassPin,HIGH);
//    delay(BassTime);
//    digitalWrite(BassPin,LOW);
//    
//    delay(DelayTime);

    digitalWrite(CymbalPin,HIGH);
    delay(CymbalTime);
    digitalWrite(CymbalPin,LOW);
    
    delay(DelayTime);
    

}
