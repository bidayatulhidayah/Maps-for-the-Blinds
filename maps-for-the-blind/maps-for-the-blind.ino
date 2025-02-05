
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Mux.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

#define MotorX_StepPin 2
#define MotorX_DirPin  5
#define MotorY_StepPin 3
#define MotorY_DirPin  6

void MODE_A();
void MODE_B();

//Instance of AccelStepper for each motor
AccelStepper stepperX (AccelStepper::DRIVER, MotorX_StepPin, MotorX_DirPin);
AccelStepper stepperY (AccelStepper::DRIVER, MotorY_StepPin, MotorY_DirPin);

const byte enablePin = 8; //enable pin [cnc shield]
long positions[2]; //array for the desired positions
int i = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis  = 0;

//Initial coordinate
//                   
int positionX []         = {                0,   
                                            0,              0,          0,           0,   
                                           97,              0,        350,         920,  
                                         1050,              0,       1300,         780,
                                          330,            250,        810,        1550   };

int positionY []         = {                0,   
                                            0,              0,          0,           0, 
                                         2700,              0,       2600,        2580, 
                                         2200,              0,       1900,        2100, 
                                         1960,           2320,          0,        1030   };

String continent_name [] = {           "Home", 
                                         "Kl",    "Putrajaya",   "Labuan",    "Perlis", 
                                      "Kedah", "Pulau Pinang",    "Perak",  "Selangor", 
                            "Negeri Sembilan",       "Melaka",    "Johor",    "Pahang", 
                                 "Terengganu",     "Kelantan",    "Sabah",   "Sarawak"  };

//Instance of MultiSteppers
MultiStepper steppers;

//limitswitch
const byte stopLimitPin = 50;
const byte homeLimitPin = 52;
//limit switch state 
int stopLimitState = 0;
int homeLimitState = 0;

//MUltiplexer
using namespace admux;
Mux mux(Pin(22, INPUT, PinType::Digital), Pinset(30, 28, 26, 24));


//MP3 Player
SoftwareSerial mySoftwareSerial(10, 11); //RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// int button_volumeUP = ;
// int button_volumeDOWN = ;

//TRACK
//myDFPlayer.playFolder(folder,track); 1 negeri 2 explain 3 others 
  // myDFPlayer.playFolder(1, 0001);  // track_Kl
 const int track_Kl         = 1;
 const int track_Putrajaya  = 2;
 const int track_Labuan     = 3;
 const int track_Perlis     = 4;
 const int track_Kedah      = 5;
 const int track_Penang     = 6;
 const int track_Perak      = 7;
 const int track_Selangor   = 8;
 const int track_N9         = 9;
 const int track_Melaka     = 10;
 const int track_Johor      = 11;
 const int track_Pahang     = 12;
 const int track_Terengganu = 13;
 const int track_Kelantan   = 14;
 const int track_Sabah      = 15;
 const int track_Sarawak    = 16;
 // explaination 
 const int track_Kl_E         = 17;
 const int track_Putrajaya_E  = 18;
 const int track_Labuan_E     = 19;
 const int track_Perlis_E     = 20;
 const int track_Kedah_E      = 21;
 const int track_Penang_E     = 22;
 const int track_Perak_E      = 23;
 const int track_Selangor_E   = 24;
 const int track_N9_E         = 25;
 const int track_Melaka_E     = 26;
 const int track_Johor_E      = 27;
 const int track_Pahang_E     = 28;
 const int track_Terengganu_E = 29;
 const int track_Kelantan_E   = 30;
 const int track_Sabah_E      = 31;
 const int track_Sarawak_E    = 32;

 const int track_start = 34;
 const int track_intro = 33;
  
//Push Button
  const int PB_Kl         = 8;  
  const int PB_Putrajaya  = 0;
  const int PB_Labuan     = 15;
  const int PB_Perlis     = 7;
  const int PB_Kedah      = 9;
  const int PB_Penang     = 1;
  const int PB_Perak      = 14;
  const int PB_Selangor   = 6;
  const int PB_N9         = 10;
  const int PB_Melaka     = 2;
  const int PB_Johor      = 13;
  const int PB_Pahang     = 5;
  const int PB_Terengganu = 11;
  const int PB_Kelantan   = 3;
  const int PB_Sabah      = 12;
  const int PB_Sarawak    = 4;

  const int PB_Start      = 47;
  const int PB_Intro      = 49;
  const int PB_Up         = 51;
  const int PB_Down      =  53;
  
//Push Button State
  int PBstate_Kl          = 0;  
  int PBstate_Putrajaya   = 0;
  int PBstate_Labuan      = 0;
  int PBstate_Perlis      = 0;
  int PBstate_Kedah       = 0;
  int PBstate_Penang      = 0;
  int PBstate_Perak       = 0;
  int PBstate_Selangor    = 0;
  int PBstate_N9          = 0;
  int PBstate_Melaka      = 0;
  int PBstate_Johor       = 0;
  int PBstate_Pahang      = 0;
  int PBstate_Terengganu  = 0;
  int PBstate_Kelantan    = 0;
  int PBstate_Sabah       = 0;
  int PBstate_Sarawak     = 0;
  int PBstate_Start       = 0;
  int PBstate_Intro       = 0;
  int PBstate_Up          = 0;
  int PBstate_Down        = 0;

//Touch Sensor
  const int TS_Kedah      = 25;
  const int TS_Penang     = 27;
  const int TS_Perak      = 29;
  const int TS_Selangor   = 31;

  const int TS_N9         = 33;
  const int TS_Melaka     = 35;
  const int TS_Johor      = 37;
  const int TS_Pahang     = 39;

  const int TS_Terengganu = 41;
  const int TS_Kelantan   = 23;
  const int TS_Sabah      = 43;
  const int TS_Sarawak    = 45;
  

//Touch Sensor state
  int tap_Kedah       = 0;
  int tap_Penang      = 0;
  int tap_Perak       = 0;
  int tap_Selangor    = 0;
  int tap_N9          = 0;
  int tap_Melaka      = 0;
  int tap_Johor       = 0;
  int tap_Pahang      = 0;
  int tap_Terengganu  = 0;
  int tap_Kelantan    = 0;
  int tap_Sabah       = 0;
  int tap_Sarawak     = 0;

//Touch Sensor DoubleTap
  unsigned long TimeStart = 0;
  unsigned long TimeLimit = 0;
  int clicks = 0;
  int pos = 0; 

//Linear Actuator
  const int ENA_PIN = 9;
  const int IN1_PIN = 13; 
  const int IN2_PIN = 12;
//state
  int state_IN1_PIN = 0;
  int state_IN2_PIN = 0;

 int vol = 20;

//XY-gantry

void setup() {
  //Serial Monitor
  Serial.begin(115200);
  //STEPPER MOTOR
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, LOW);
    //Configuration for each stepper
    stepperX.setMaxSpeed(1000);
    stepperY.setMaxSpeed(1000);
    //MultiStepper manage
    steppers.addStepper(stepperX);
    steppers.addStepper(stepperY);
    //numSteps = sizeof(positionX) / sizeof(positionX[0]);

  //limit switch setup
   pinMode(stopLimitPin, INPUT_PULLUP);
   pinMode(homeLimitPin, INPUT_PULLUP); 


  // MP3 checking 
  mySoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  //myDFPlayer.play(track_start); //start 
  //myDFPlayer.play(34);

  //PUSH BUTTON
  pinMode(PB_Start, INPUT_PULLUP);
  pinMode(PB_Intro, INPUT_PULLUP);
  

  //TOUCH SENSOR 
  pinMode(TS_Kedah,      INPUT);
  pinMode(TS_Penang,     INPUT);
  pinMode(TS_Perak,      INPUT);
  pinMode(TS_Selangor,   INPUT);
  pinMode(TS_N9,         INPUT);
  pinMode(TS_Melaka,     INPUT);
  pinMode(TS_Johor,      INPUT);
  pinMode(TS_Pahang,     INPUT);
  pinMode(TS_Terengganu, INPUT);
  pinMode(TS_Kelantan,   INPUT);
  pinMode(TS_Sabah,      INPUT);
  pinMode(TS_Sarawak,    INPUT);

  //LINEAR ACTUATOR
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  digitalWrite(ENA_PIN, HIGH);
}

void loop() {
  //Serial Monitor
  //Serial.print(PBstate_Sabah);
  //Serial.println(PBstate_Sarawak);

  //PUSH BUTTON STATE
  PBstate_Kl         = mux.read(PB_Kl);
  PBstate_Putrajaya  = mux.read(PB_Putrajaya);
  PBstate_Labuan     = mux.read(PB_Labuan);
  PBstate_Perlis     = mux.read(PB_Perlis);
  PBstate_Kedah      = mux.read(PB_Kedah);
  PBstate_Penang     = mux.read(PB_Penang);
  PBstate_Perak      = mux.read(PB_Perak);
  PBstate_Selangor   = mux.read(PB_Selangor);
  PBstate_N9         = mux.read(PB_N9);
  PBstate_Melaka     = mux.read(PB_Melaka);
  PBstate_Johor      = mux.read(PB_Johor);
  PBstate_Pahang     = mux.read(PB_Pahang);
  PBstate_Terengganu = mux.read(PB_Terengganu);
  PBstate_Kelantan   = mux.read(PB_Kelantan);
  PBstate_Sabah      = mux.read(PB_Sabah);
  PBstate_Sarawak    = mux.read(PB_Sarawak);

  PBstate_Start   = digitalRead(PB_Start);
  PBstate_Intro   = digitalRead(PB_Intro);
    
  //TOUCH SENSOR STATE
    tap_Kedah      = 0;
  tap_Penang     = digitalRead(TS_Penang);
  // tap_Penang     = 0;
  tap_Perak      = digitalRead(TS_Perak);
  // tap_Perak      = 0;
  tap_Selangor   = digitalRead(TS_Selangor);
  // tap_Selangor   = 0;
  //tap_N9         = digitalRead(TS_N9);
  tap_N9         = 0 ;
  //tap_Melaka     = digitalRead(TS_Melaka);
  tap_Melaka     = 0 ;
  tap_Johor      = digitalRead(TS_Johor);
  tap_Pahang     = digitalRead(TS_Pahang);
  //tap_Terengganu = digitalRead(TS_Terengganu);
  //tap_Kelantan   = digitalRead(TS_Kelantan); 
  // tap_Johor      = 0;
  // tap_Pahang     = 0;
 tap_Terengganu = 0;
  tap_Kelantan   = 0; 
  tap_Sabah      = digitalRead(TS_Sabah);
  tap_Sarawak    = digitalRead(TS_Sarawak);

  //limit switch
  // xLimitState = digitalRead(xLimitPin);
  //yLimitState = digitalRead(yLimitPin);

  // linear actuator state
  state_IN1_PIN = digitalRead(IN1_PIN);
  state_IN2_PIN = digitalRead(IN2_PIN);

    while (digitalRead(stopLimitPin) == 0){
      //Serial.println("stop limit switch pressed");
    }

    if (PBstate_Start == HIGH) {
        myDFPlayer.play(34);
    }

    if (PBstate_Intro == HIGH) {
        myDFPlayer.play(33);
    }
    //HOME
    if ((PBstate_Start == HIGH && state_IN1_PIN == LOW && state_IN2_PIN == HIGH)|| (PBstate_Kl == LOW &&  PBstate_Putrajaya == LOW &&  PBstate_Labuan == LOW 
        &&  PBstate_Perlis == LOW &&  PBstate_Kedah == LOW &&  PBstate_Penang == LOW &&  PBstate_Perak == LOW && PBstate_Selangor == LOW &&  PBstate_N9 == LOW 
        &&  PBstate_Melaka == LOW &&  PBstate_Johor == LOW &&  PBstate_Pahang== LOW &&  PBstate_Terengganu == LOW && PBstate_Kelantan == LOW
        && PBstate_Sabah == LOW && PBstate_Sarawak == LOW && state_IN1_PIN == LOW && state_IN2_PIN == HIGH &&
        tap_Kedah == LOW && tap_Penang == LOW && tap_Perak == LOW && tap_Selangor == LOW && tap_N9 == LOW && tap_Melaka == LOW 
      && tap_Johor == LOW && tap_Pahang== LOW && tap_Terengganu == LOW && tap_Sabah == LOW && tap_Sarawak == LOW) ){
      currentMillis = millis();
    if (currentMillis - previousMillis >= 10000) {
      previousMillis = currentMillis;
        Serial.println("HOME");
        if (steppers.run() == 0){
            positions[0] = positionX[0];
            positions[1] = positionY[0];
            steppers.moveTo(positions);
        }  
        while (steppers.run()){
        }
    }
  }
      
  //MODE A: Push Button will move xy-gantry
    MODE_A ();
  //MODE B : ONE TAP AUDIO ON 
    MODE_B ();
// int volumeLevel;
  //VOLUME CONTROL
  if (digitalRead(PB_Up) == HIGH){
    myDFPlayer.volumeUp();
    // myDFPlayer.volume(volumeLevel);
    // vol++;
    // Serial.println(vol);
    Serial.print("volume Up   ");
    Serial.println(myDFPlayer.readVolume());
  }

  if (digitalRead(PB_Down) == HIGH){
    myDFPlayer.volumeDown();
    // Serial.println("volume Down");
    // vol--;
    // Serial.println(vol);
    Serial.print("volume Down  ");
    Serial.println(myDFPlayer.readVolume());
  }
  //MP3 Player Error and status
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void MODE_A(){

  //PUSH Button Kl
  if (PBstate_Kl == HIGH){
    //State name
    myDFPlayer.play(track_Kl);

    //xy gantry
    i = 1;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Kl_E);
        delay(500);

        currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Putrajaya
  if (PBstate_Putrajaya == HIGH){
    //State name
    myDFPlayer.play(track_Putrajaya);
    //xy gantry
    i = 2;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
         myDFPlayer.play(track_Putrajaya_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Labuan
  if (PBstate_Labuan == HIGH){
    //State name
    myDFPlayer.play(track_Labuan);

    //xy gantry
    i = 3;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Labuan_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Perlis
  if (PBstate_Perlis == HIGH){
    //State name
    myDFPlayer.play(track_Perlis);

    //xy gantry
    i = 4;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Perlis_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Kedah
  if (PBstate_Kedah == HIGH){
    //State name
    myDFPlayer.play(track_Kedah);

    //xy gantry
    i = 5;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Kedah_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }
  
  //PUSH Button Penang
  if (PBstate_Penang == HIGH){
    //State name
   myDFPlayer.play(track_Penang);

    //xy gantry
    i = 6;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Penang_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Perak
  if (PBstate_Perak == HIGH){
    //State name
    myDFPlayer.play(track_Perak);

    //xy gantry
    i = 7;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Perak_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Selangor
  if (PBstate_Selangor == HIGH){
    //State name
    myDFPlayer.play(track_Selangor);

    //xy gantry
    i = 8;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Selangor_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

//PUSH Button N9
  if (PBstate_N9 == HIGH){
    //State name
    myDFPlayer.play(track_N9);

    //xy gantry
    i = 9;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_N9_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Melaka
  if (PBstate_Melaka == HIGH){
    //State name
    myDFPlayer.play(track_Melaka);

    //xy gantry
    i = 10;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        // digitalWrite(IN1_PIN, HIGH);
        // digitalWrite(IN2_PIN, LOW);
        // delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Melaka_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Johor
  if (PBstate_Johor == HIGH){
    //State name
    myDFPlayer.play(track_Johor);

    //xy gantry
    i = 11;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Johor_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Pahang
  if (PBstate_Pahang == HIGH){
        //State name
    myDFPlayer.play(track_Pahang);

    //xy gantry
    i = 12;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Pahang_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }
  
  //PUSH Button Terengganu
  if (PBstate_Terengganu == HIGH){
    //State name
    myDFPlayer.play(track_Terengganu);

    //xy gantry
    i = 13;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(400);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Terengganu_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Kelantan
  if (PBstate_Kelantan == HIGH){
        //State name
    myDFPlayer.play(track_Kelantan);

    //xy gantry
    i = 14;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Kelantan_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Sabah 
  if (PBstate_Sabah == HIGH){
        //State name
    myDFPlayer.play(track_Sabah);

    //xy gantry
    i = 15;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        //delay(4000);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Sabah_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;
  }

  //PUSH Button Sarawak
  if (PBstate_Sarawak == HIGH){
        //State name
    myDFPlayer.play(track_Sarawak);

    //xy gantry
    i = 16;
    Serial.println("Button " + continent_name[i] + " is pushed" );
    if (steppers.run() == 0){
      positions[0] = positionX[i];
      positions[1] = positionY[i];
      steppers.moveTo(positions);
    } 
    while (steppers.run()){
    }
    
    //linear actuator
        digitalWrite(IN1_PIN, HIGH);
        digitalWrite(IN2_PIN, LOW);
        delay(400);
        //MP3 play
         Serial.println("Playing " + continent_name[i]);
        myDFPlayer.play(track_Sarawak_E);
        delay(500);

         currentMillis = millis();
        previousMillis = currentMillis;

      //   currentMillis = millis();
      // previousMillis = currentMillis;
  }

//PUT DOWN ACTUATOR : Double Tap  
  if ( tap_Kedah == HIGH || tap_Penang == HIGH || tap_Perak == HIGH || tap_Selangor == HIGH || tap_N9 == HIGH || tap_Melaka == HIGH 
      || tap_Johor == HIGH || tap_Pahang== HIGH || tap_Terengganu == HIGH || tap_Sabah == HIGH || tap_Sarawak == HIGH){
    
    delay(200);
    
    if (clicks == 0){
      TimeStart = millis();
      TimeLimit = TimeStart + 225;
      clicks =1;
    }
  
    else if (clicks == 1 && millis() < TimeLimit){
      Serial.println("Double tap");
      myDFPlayer.stop();
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);

      currentMillis = millis();
      previousMillis = currentMillis;
        
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }
  }

  // if (xLimitState == LOW){
  //     if (steppers.run() == 0){
  //           positions[0] = positionX[0];
  //           positions[1] = positionY[0];
  //           steppers.moveTo(positions);
  //       }  
  //       while (steppers.run()){
  //      }

  // }

}

void MODE_B(){
    // if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
    //     &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
    //     && tap_Sabah == LOW && tap_Sarawak == LOW){   

    //   Serial.println("Button Pressed Once TS_Kl");
      
    //   //MP3 play
    //   myDFPlayer.play(track_Kl);
    //   delay (500);
    //   myDFPlayer.play(track_Kl_E);
    //   delay(500);
      
    //   TimeStart = 0;
    //   TimeLimit = 0;
    //   clicks = 0; 
    // }

    // if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit  &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
    //     &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang == LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
    //     && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
    //   Serial.println("Button Pressed Once TS_Putrajaya");
    
    //   //MP3 play
    //   myDFPlayer.play(track_Putrajaya);
    //   delay (500);
    //   myDFPlayer.play(track_Putrajaya_E);
    //   delay(500);
      
    //   TimeStart = 0;
    //   TimeLimit = 0;
    //   clicks = 0; 
    // }

    // if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
    //     &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
    //     && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
    //   Serial.println("Button Pressed Once TS_Labuan");
    
    //   //MP3 play
    //   myDFPlayer.play(track_Labuan);
    //   delay (500);
    //   myDFPlayer.play(track_Labuan_E);
    //   delay(500);
      
    //   TimeStart = 0;
    //   TimeLimit = 0;
    //   clicks = 0; 
    // }

    // if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit  &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
    //     &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
    //     && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
    //   Serial.println("Button Pressed Once TS_Perlis");
    
    //   //MP3 play
    //   myDFPlayer.play(track_Perlis);
    //   delay (500);
    //   myDFPlayer.play(track_Perlis_E);
    //   delay(500);
      
    //   TimeStart = 0;
    //   TimeLimit = 0;
    //   clicks = 0; 
    // }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit && tap_Kedah == HIGH && tap_Penang == LOW && tap_Perak == LOW && tap_Selangor == LOW && tap_N9 == LOW 
    &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Kedah");
      
      //MP3 play
      myDFPlayer.play(track_Kedah);
      // delay (500);
      // myDFPlayer.play(track_Kedah_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == HIGH &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Penang");
    
      //MP3 play
      myDFPlayer.play(track_Penang);
      // delay (500);
      // myDFPlayer.play(track_Penang_E);
      delay (500);

      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == HIGH && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
      Serial.println("Button Pressed Once TS_Perak");
    
      //MP3 play
       myDFPlayer.play(track_Perak);
      // delay (500);
      // myDFPlayer.play(track_Perak_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == HIGH &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
      Serial.println("Button Pressed Once TS_Selangor");
    
      //MP3 play
      myDFPlayer.play(track_Selangor);
      // delay (500);
      // myDFPlayer.play(track_Selangor_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == HIGH 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_N9");
    
      //MP3 play
      myDFPlayer.play(track_N9);
      // delay (500);
      // myDFPlayer.play(track_N9_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == HIGH &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Melaka");
    
      //MP3 play
      myDFPlayer.play(track_Melaka);
      // delay (500);
      // myDFPlayer.play(track_Melaka_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit && tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == HIGH &&  tap_Pahang == LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){   
          
      Serial.println("Button Pressed Once TS_Johor");
    
      //MP3 play
      myDFPlayer.play(track_Johor);
      // delay (500);
      // myDFPlayer.play(track_Johor_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang == HIGH &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Pahang");
      
      //MP3 play
     myDFPlayer.play(track_Pahang);
      // delay (500);
      // myDFPlayer.play(track_Pahang_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == HIGH && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Terengganu");
    
      //MP3 play
      myDFPlayer.play(track_Terengganu);
      // delay (500);
      // myDFPlayer.play(track_Terengganu_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == HIGH
        && tap_Sabah == LOW && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Kelantan");
    
      //MP3 play
       myDFPlayer.play(track_Kelantan);
      // delay (500);
      // myDFPlayer.play(track_Kelantan_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit && tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == HIGH && tap_Sarawak == LOW){  
          
      Serial.println("Button Pressed Once TS_Sabah");
    
      //MP3 play
      myDFPlayer.play(track_Sabah);
     
      //myDFPlayer.play(track_Sabah_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }

    if (clicks == 1 && TimeLimit!= 0 && millis() > TimeLimit &&  tap_Kedah == LOW &&  tap_Penang == LOW &&  tap_Perak == LOW && tap_Selangor == LOW &&  tap_N9 == LOW 
        &&  tap_Melaka == LOW &&  tap_Johor == LOW &&  tap_Pahang== LOW &&  tap_Terengganu == LOW && tap_Kelantan == LOW
        && tap_Sabah == LOW && tap_Sarawak == HIGH){  
          
      Serial.println("Button Pressed Once TS_Sarawak");
    
      //MP3 play
      myDFPlayer.play(track_Sarawak);
      //delay (500);
      //myDFPlayer.play(track_Sarawak_E);
      delay(500);
      
      TimeStart = 0;
      TimeLimit = 0;
      clicks = 0; 
    }  
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

