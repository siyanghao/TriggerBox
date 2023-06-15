// Camera library
// Buzzer library (tone generator)
//#include <toneAC.h>
/*  TriggerBox_2.5, 
    Trigger HSV;
    Flash LED and buzzer;
    with push trigger and/or motion triggering from TTL;

    Periodic flash and beep for machine vision cams to sync;
    Cam output shrinked 
    cooperate with PTUX
    
    Siyang Hao
    20230612
    Brown, PVD
 v3.01
 
*/
// Pin Mapping
const int buttonPin = 2;   // the number of the Pushbutton pin
const int TTLPin =3;       // TTL trigger input pin, from motion
const int SLCPin =5;       // input from SCL 
const int ledPin =  9;     // the number of the LED pin
const int buzzerPin = 6;   // the number of the Buzzer (Speaker) pin
const int cameraPin = 10;  // the number of the Camera pin, should be 10
const int gatePin = 8;     // Gate pin, should be 8, but Q&D test set to 10
const int PTUPin =7;     // PTU input pin
// Variables
int buttonState ;         // variable for reading the pushbutton status
int TTLState;
int previous;
int stateLED;
int PTUState;
int SLCState;
long time = 0;
long debounce = 200;
int i;
int arm =0;
unsigned long previousMillis = 0;        // will store last time servo was updated
unsigned long currentMillis ;
const long interval = 5000;           // interval at which to run (milliseconds)

void setup() {
 int buttonState = LOW;         // variable for reading the pushbutton status
 int TTLState = LOW;         // variable for reading the TTL status
 int previous= LOW;
 int stateLED = LOW;
 int PTUState = LOW;
 int SLCState = LOW;
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize the Pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(TTLPin, INPUT);
  pinMode(SLCPin, INPUT);
  pinMode(PTUPin, INPUT);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the Buzzer pin as an output:
  pinMode(buzzerPin, OUTPUT);
  // initialize the CAMERA as an output:
  pinMode(cameraPin, OUTPUT);

  pinMode(gatePin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  TTLState = digitalRead(TTLPin);
  stateLED = LOW;
  SLCState = LOW;
  PTUState = LOW;
  PTUState = digitalRead(PTUPin);
  
  digitalWrite(ledPin, stateLED);
     // Trigger button& motion trigger logic
    if(buttonState == HIGH||TTLState ==HIGH) { //system armed for recording
      stateLED = HIGH; 
      digitalWrite(ledPin, stateLED);  // turn on the LED
      digitalWrite(cameraPin, HIGH); // sets the cameraPin on
      delay(1);
      digitalWrite(cameraPin, LOW); // sets the cameraPin off
      // 3 Buzzer sounds
      tone(buzzerPin, 2000, 200);
      delay(100);
      
      
      //Serial.print("trigger pushed \n"); // for debuging comment out for faster scanning loop
 
      tone(buzzerPin, 2200, 200);
      delay(100);
      tone(buzzerPin, 2600, 200);
      delay(100);
      tone(buzzerPin, 2400, 200);
      delay(100);
      tone(buzzerPin, 2200, 200);
      delay(100);
      stateLED = LOW;
      digitalWrite(ledPin, stateLED);
      delay (500);
      if (arm ==0){
      arm =1;
      } else {
      arm =0; // disarm the routine beeping
      }
    }

    buttonState = LOW; // set button state back to low
    //SLC logic: disarm the sys when triggered
    SLCState = digitalRead(SLCPin);
    if (SLCState == HIGH){
      Serial.print("SLC Triggered \n");
      if( arm == 1){//disarm and make a beep
        arm = 0;
        tone(buzzerPin, 2400, 200);
        delay(100);
        tone(buzzerPin, 2200, 200);
      }
    }

    // routine perodic beeping
    currentMillis = millis();
    if (arm ==1){
      if (PTUState==HIGH){
      digitalWrite(gatePin, HIGH);
      }else{
        digitalWrite(gatePin, LOW);
      }
      if ( currentMillis - previousMillis >= interval) {
         previousMillis = currentMillis; // reset clock
         digitalWrite(ledPin, HIGH);
         tone(buzzerPin, 2200, 200);
         delay(100);
         tone(buzzerPin, 7200, 200);
         digitalWrite(ledPin, LOW);
         }
     } else {
       digitalWrite(gatePin, LOW);  
     }
    
}
