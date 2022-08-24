#include <SPI.h>

//bootTime will need tweaking

//||---------------------||---------------------||
//||  Servo Positions    || Facial Expressions  ||
//||---------------------||---------------------||
//|| 0 - no change       || 0 - no change       ||
//|| 1 - centres head    || 1 - 'Smile'         ||
//|| 2 - nods (down)     || 2 - 'Tension'       ||
//|| 3 - nods (up)       || 3 - 'RaiseEyebrows' ||
//|| 4 - looks at snare  || 4 - 'Exclamation'   ||
//|| 5 - looks at cymbal || 5 - 'inquisitive'   ||
//|| 6 - pans full left  || 6 - 'Sad'           ||
//|| 7 - pans full right || 7 - 'Elevated'      ||
//|| 8 - tilts down      || 8 - 'Frown'         ||
//|| 9 - tilts up        || 9 - 'FrownBrows'    ||

//------------------------
// Information about songs for loading
//------------------------
const int MaxNumSongs = 3;  // Number of songs to be loaded
const int NumSongs = 3;     // Number of songs to be loaded
const int DrumMax = 3;      // Max number of robots used

const int Tune1Length = 128;
const int Tune1Tempo = 96;
const int Tune1BeatDenom = 4;

const int Tune2Length = 240;
const int Tune2Tempo = 96;
const int Tune2BeatDenom = 4;

const int Tune3Length = 256;
const int Tune3Tempo = 96;
const int Tune3BeatDenom = 4;

//----------
// SONG DATA
//----------

  // 1st line - snare, 2nd line - cymbal, 3rd line - bass 
  // Part1
const unsigned int Tune1[DrumMax][Tune1Length] PROGMEM = {
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1},
  {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}}; 

  // 1st line - head position, 2nd line - facial expression (see table) 
const unsigned int Tune1Head[2][Tune1Length] PROGMEM = { 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}, 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}};

  
  // Part2 
const unsigned int Tune2[DrumMax][Tune2Length] PROGMEM = {
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0},
  {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0}}; 

const unsigned int Tune2Head[2][Tune2Length] PROGMEM = { 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0}, 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0}};


 // Part3 
const unsigned int Tune3[DrumMax][Tune3Length] PROGMEM = {
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1},
  {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}}; 

const unsigned int Tune3Head[2][Tune3Length] PROGMEM = { 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}, 
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1}};

//------------------------
// OUTPUT DEFINITIONS
//------------------------
const int On_Button = 8;           // signal from conductor, set low with output pin (White Wire)
const int ledpin = 13; // flash led
const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

//output pins for link to raspberry pi and arduino
const int piB0 = 45,piB1 = 43,piB2 = 41,piB3 = 39;
const int n0 = 9, n1 = 10, n2 = 11, n3 = 12;

//------------------------
// TIME CONSTANTS
//------------------------
const int drumTime = 30;        //solenoid 'on' time for drums (in ms)
const int bassOffset = 20;      //gives bass drum a head start
const int start_delay = 0;
const int long bootTime = 90000;     //delay to allow raspberry pi/supercollider to load before starting


//------------------------  
// Create program variables
//------------------------
int On_Signal;    // Used to track conductor
unsigned int Load_Drum[DrumMax];
unsigned int Load_Head[2];
unsigned int Load_Timing;

int BeatCount = 0; // Used to index Tune array
int DrumCount = 0; // Used to index Tune array
int SongCount = 0;

int SR_Count = 0;

// Create array to store information about songs
int Tune_Info[MaxNumSongs][4];
 
// Timing check variables

unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;
long int Beat_Time;

unsigned long part_start_time = 0;
unsigned long part_tempo = 0;
unsigned long part_stop_time = 0;
float part_time = 0;
float parttempo_beats = 0;

volatile unsigned int Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


//------------------------
// Setup Function 
//------------------------
void setup() 
{
    // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1Tempo;
    Tune_Info[0][2] =  Tune1BeatDenom;
    Tune_Info[1][0] =  Tune2Length;
    Tune_Info[1][1] =  Tune2Tempo;
    Tune_Info[1][2] =  Tune2BeatDenom;
    Tune_Info[2][0] =  Tune3Length;
    Tune_Info[2][1] =  Tune3Tempo;
    Tune_Info[2][2] =  Tune3BeatDenom;
        
    // configure I/O pins
    pinMode(ledpin, OUTPUT);
    pinMode(On_Button, INPUT_PULLUP);
   
    digitalWrite(ledpin, LOW);
    digitalWrite(On_Button, HIGH);

    pinMode(SnarePin, OUTPUT);
    pinMode(BassPin, OUTPUT);
    pinMode(CymbalPin, OUTPUT);

    digitalWrite(SnarePin,LOW);
    digitalWrite(BassPin,LOW);
    digitalWrite(CymbalPin,LOW);
  
    pinMode(piB0,OUTPUT);
    pinMode(piB1,OUTPUT);
    pinMode(piB2,OUTPUT);
    pinMode(piB3,OUTPUT);
    pinMode(n0,OUTPUT);
    pinMode(n1,OUTPUT);
    pinMode(n2,OUTPUT);
    pinMode(n3,OUTPUT);

    digitalWrite(piB0,LOW);
    digitalWrite(piB1,LOW);
    digitalWrite(piB2,LOW);
    digitalWrite(piB3,LOW);
    digitalWrite(n0,LOW);
    digitalWrite(n1,LOW);
    digitalWrite(n2,LOW);
    digitalWrite(n3,LOW);

    // Start USB Serial for monitoring
    Serial.begin(115200);   
    Serial.println("USB Working!");

    //centres head
    moveHead(1);
    
    delay(1000);
    
}


// --------------------------------------------------------------------------------------
//------------------------
//Loop Function
//------------------------
void loop() 
{
      
        for(SongCount = 0; SongCount < NumSongs; SongCount++)
        {                             
              On_Signal = 1;
              while (On_Signal > 0)
              {
                  On_Signal = digitalRead(On_Button); // Wait for Graphene ON (LOW)
              }
    
              part_start_time = micros();
              delay(start_delay);
   
              Beat_Time = (1/(Tune_Info[SongCount][1]/60.0))/Tune_Info[SongCount][2]*1000000.0;
              Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
              Start_Beat_Timer(); // Start Timer 1
    
              for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
              {
                    // Load Song Beats
                    for (DrumCount=0; DrumCount < DrumMax; DrumCount++)
                    {  
                          if(SongCount == 0)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune1[DrumCount][BeatCount]);
                          }
                          if(SongCount == 1)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune2[DrumCount][BeatCount]);                                  
                          }
                          if(SongCount == 2)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune3[DrumCount][BeatCount]);
                          }
                    }

                    // Load Head/Face Movement
                    if(SongCount == 0)
                    { 
                        Load_Head[0] = pgm_read_byte(&Tune1Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune1Head[1][BeatCount]);
                    }
                    if(SongCount == 1)
                    {
                        Load_Head[0] = pgm_read_byte(&Tune2Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune2Head[1][BeatCount]);                                  
                    }
                    if(SongCount == 2)
                    {
                        Load_Head[0] = pgm_read_byte(&Tune3Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune3Head[1][BeatCount]);
                    }
                    
                    Play_Beat();                                

                    moveHead(Load_Head[0]);
                    changeFace(Load_Head[1]);                                             
                        
                    while (Next_Beat < 1)
                    {
                      // Waitfor Beat Timer 
                    } 
                    Next_Beat = 0;
              }
    
              while (On_Signal < 1)
              {
                  On_Signal = digitalRead(On_Button); //  Wait for Graphene signal OFF (HIGH)
              }
              
              digitalWrite(ledpin,LOW); 
              part_stop_time = micros();
            
              // calculate tempo                                  
              part_time = (part_stop_time-part_start_time)/1000000.0; 
              part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][2])/part_time)*60.0;
           
        }
                   
}

// --------------------------------------------------------------------------------------

// Play drums functions

void Play_Beat() 
{
 
      if(Load_Drum[2] == 1)
      {
          digitalWrite(BassPin,HIGH);
      }

      delay(bassOffset);
      
      if(Load_Drum[0] == 1)
      {
          digitalWrite(SnarePin,HIGH);
      }
      if(Load_Drum[1] == 1)
      {
          digitalWrite(CymbalPin,HIGH);
      }
      
      delay(drumTime);

      if(Load_Drum[0] == 1)
      {
          digitalWrite(SnarePin,LOW);
      }
      if(Load_Drum[1] == 1)
      {
          digitalWrite(CymbalPin,LOW);
      }
      if(Load_Drum[2] == 1)
      {
          delay(bassOffset);
          digitalWrite(BassPin,LOW);
      }
}

//==============================
// Functions for Head and Face
//==============================

void  moveHead(int headInput)
{
    digitalWrite(n0,!bitRead(headInput,0));
    digitalWrite(n1,!bitRead(headInput,1));
    digitalWrite(n2,!bitRead(headInput,2));
    digitalWrite(n3,!bitRead(headInput,3)); 
}

void  changeFace(int faceInput)
{
    digitalWrite(piB0,bitRead(faceInput,0));
    digitalWrite(piB1,bitRead(faceInput,1));
    digitalWrite(piB2,bitRead(faceInput,2));
    digitalWrite(piB3,bitRead(faceInput,3)); 
}
  

//==============================
// Functions for interrupt timer
//==============================

void Start_Beat_Timer() 
{
  //Serial.println(Beat_Time);
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  TCNT1 = Timer1_Beat_Count;   // preload timer
  TCCR1B |= (1 << CS12);    // Sets 256 prescaler 16 uSec counts
  Timer1_Beat_Count = (65536 -(Beat_Time/16));   // preload timer 65536-(416666/16) = 39494
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = Timer1_Beat_Count;   // Reload timer1 with beacount
  Next_Beat= 1;
}


