// Information about songs for loading
const int NumSongs = 1;     // Number of songs to be loaded

const int Tune1Length = 8;
const int Tune1NoteMax = 2;
const int Tune1Tempo = 95;
const int Tune1BeatDenom = 4;

const unsigned int Tune1[Tune1NoteMax][Tune1Length] PROGMEM = {
  {1,1,1,1,1,1,1,1},
  {1,0,1,0,1,0,1,1},
//  {1,0,0,0,1,0,0,0}
  };

const int start_delay = 0;

// Create program variables
int On_Signal;    // Used to track conductor
unsigned int Load_Note[3];  // Used to load drums to be played on the current beat

int NoteCount;  // Used to count through the different drums, max 3
int BeatCount;
int SongCount;
int ArrayCount; 

// Create array to store information about songs
int Tune_Info[NumSongs][4];  

// Define I/O pins
const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

const int ConductorPin = 8;

const int DrumTime = 50;
const int DelayTime = 100;

int OnSignal = 1;

// Variable for measuring time of part and calculating tempo
unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;
long int Beat_Time;

unsigned long part_start_time = 0;
unsigned long part_stop_time = 0;
float part_time = 0;
int part_tempo = 0;

volatile unsigned int Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo
volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


void setup() 
{
    // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1NoteMax;
    Tune_Info[0][2] =  Tune1Tempo;
    Tune_Info[0][3] =  Tune1BeatDenom;

    // Begin USB Serial
    Serial.begin(9600);

    // Configure I/O pins
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
    for(SongCount = 0; SongCount < NumSongs; SongCount++)
    {    
          Serial.print("Number of Notes: ");
          Serial.println(Tune_Info[SongCount][0]);
          Serial.print("Max Notes: ");
          Serial.println(Tune_Info[SongCount][1]);
          Serial.print("Tempo(Bpm): ");
          Serial.println(Tune_Info[SongCount][2]);
          Serial.print("Beat Denomination: ");
          Serial.println(Tune_Info[SongCount][3]);
          
          Serial.println("Ready to play, waiting for On Signal");
          
          On_Signal = 1;
          while (On_Signal > 0)
          {
              On_Signal = digitalRead(ConductorPin); // Wait for Graphene ON (LOW)
          }
          //On_Signal = 1;
          
          part_start_time = micros();
          delay(start_delay);
          Serial.println("Song Start");

          Beat_Time = (1/(Tune_Info[SongCount][2]/60.0))/Tune_Info[SongCount][3]*1000000.0;
          Serial.print("Beat Time (s): ");
          Serial.println(Beat_Time/1000000.0);
          Serial.println();
          
          Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timer 1
          ArrayCount=0;
          
          for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
          {
                Serial.print("Beat: ");
                Serial.println(BeatCount);
                          
                for (NoteCount=0; NoteCount < Tune_Info[SongCount][1]; NoteCount++)
                { 
                      
                    Load_Note[NoteCount] = pgm_read_byte(&Tune1[1][ArrayCount]);
                    Serial.print("Note: ");
                    Serial.println(Load_Note[NoteCount]);
                }                                       
                
                Serial.println();  
                Play_Beat();
                Next_Beat = 0;                
                while (Next_Beat < 1)
                {
                  // Waitfor Beat Timer 
                }
                Next_Beat = 0; 

                On_Signal = digitalRead(ConductorPin);
                Serial.print("On_Signal: ");
                Serial.println(On_Signal);
                if (On_Signal > 0)
                {
                    break;
                }
                  
          }
          part_stop_time = micros();

          //-----------------
          // calculate tempo
          
          
          part_time = (part_stop_time-part_start_time)/1000000.0; 
          part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][3])/part_time)*60.0;

          // display results   
          Serial.print("Part Time (s): ");
          Serial.println(part_time);
          Serial.print("Part Tempo (bpm): ");
          Serial.println(part_tempo);
          
          Serial.print("Shift Register Load Time: ");  
          Serial.println(sr_stop_time-sr_start_time);
          
          Serial.println("------------------------------------------------");
          Serial.println();
          
          Serial.println("-----------------------------------------------------------------");

    } 
    
      
}

  // Play drum functions
void Play_Beat() 
{
    if(Load_Note[0] == 1)
    {
        digitalWrite(SnarePin,HIGH);
    }
    if(Load_Note[1] == 1)
    {
        digitalWrite(CymbalPin,HIGH);
    }
    if(Load_Note[2] == 1)
    {
        digitalWrite(BassPin,HIGH);
    }

    delay(DrumTime);

    if(Load_Note[0] == 1)
    {
        digitalWrite(SnarePin,LOW);
    }
    if(Load_Note[1] == 1)
    {
        digitalWrite(CymbalPin,LOW);
    }
    if(Load_Note[2] == 1)
    {
        digitalWrite(BassPin,LOW);
    }
}

// Functions for interrupt timer
void Start_Beat_Timer() 
{
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
  
