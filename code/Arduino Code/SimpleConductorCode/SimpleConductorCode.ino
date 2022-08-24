
const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

const int ConductorPin = 8;

const int SnareTime = 50;
const int BassTime = 90;
const int CymbalTime = 90;
const int DelayTime = 100;

int OnSignal = 1;


void setup() 
{
    // Begin USB Serial
    Serial.begin(9600);

    pinMode(SnarePin, OUTPUT);
    pinMode(BassPin, OUTPUT);
    pinMode(CymbalPin, OUTPUT);

    pinMode(ConductorPin, INPUT_PULLUP);

    digitalWrite(SnarePin,LOW);
    digitalWrite(BassPin,LOW);
    digitalWrite(CymbalPin,LOW);
    
}

void loop() 
{
    Serial.println("Loop Start");
   
    OnSignal = 1;
    while (OnSignal > 0)
    {
        OnSignal = digitalRead(ConductorPin); // Wait for Conductor ON (LOW)
    }
    
    digitalWrite(SnarePin,HIGH);
    digitalWrite(CymbalPin,HIGH);
    digitalWrite(BassPin,HIGH);
    
    delay(SnareTime);
    
    digitalWrite(SnarePin,LOW);
    digitalWrite(CymbalPin,LOW);
    digitalWrite(BassPin,LOW);
    
    delay(DelayTime);

    while (OnSignal < 1)
    {
        OnSignal = digitalRead(ConductorPin); // Wait for Conductor OFF (HIGH)
    }
  

}
