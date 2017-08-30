#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// CONSTANTS
const int buttonNextPin = 3;
const int buttonPrevPin = 2;

const int potMeasurementsCount = 15;
const int pot1Pin = 0;
const int pot2Pin = 1;
const int pot3Pin = 2;
const int pot4Pin = 3;

const int pot1CC = 85;
const int pot2CC = 86;
const int pot3CC = 87;
const int pot4CC = 88;

// GLOBAL VARIABLES
int buttonPrevState = 0;
int buttonNextState = 0;
int buttonPrevCurrentState = 0;
int buttonNextCurrentState = 0;

int potsCount = 0;

int pot1State = 0;
int pot2State = 0;
int pot3State = 0;
int pot4State = 0;

int pot1Values[potMeasurementsCount];
int pot2Values[potMeasurementsCount];
int pot3Values[potMeasurementsCount];
int pot4Values[potMeasurementsCount];

void setup() {
  MIDI.begin();
}

void loop() {
  // Writing current states
  buttonPrevCurrentState = digitalRead(buttonPrevPin);
  buttonNextCurrentState = digitalRead(buttonNextPin);

  pot1Values[potsCount] = analogRead(pot1Pin) / 8;
  pot2Values[potsCount] = analogRead(pot2Pin) / 8;
  pot3Values[potsCount] = analogRead(pot3Pin) / 8;
  pot4Values[potsCount] = analogRead(pot4Pin) / 8;

  potsCount++;

  // Comparison block
  if (buttonPrevState != buttonPrevCurrentState) {
    switch (buttonPrevCurrentState) {
      case 1:
        MIDI.sendNoteOn(1,127, 1);
        break;
      case 0:
        MIDI.sendNoteOff(1, 127, 1);
        break;
    }   
    buttonPrevState = buttonPrevCurrentState;
  }
  if (buttonNextState != buttonNextCurrentState) {
    switch (buttonPrevCurrentState) {
      case 1:
        MIDI.sendNoteOn(2,127, 1);
        break;
      case 0:
        MIDI.sendNoteOff(2, 127, 1);
        break;
    }   
    buttonNextState = buttonNextCurrentState;
  }

  if (potsCount == potMeasurementsCount) {
    int pot1CurrentState = 0;
    for (int i = 0; i < potsCount; i++) {
      pot1CurrentState = pot1CurrentState + pot1Values[i];  
    }
    pot1CurrentState = pot1CurrentState / potMeasurementsCount;
    
    if (pot1State != pot1CurrentState) {
      MIDI.sendControlChange(pot1CC, pot1CurrentState, 1);
      pot1State = pot1CurrentState;
    }
    
    int pot2CurrentState = 0;
    for (int i = 0; i < potsCount; i++) {
      pot2CurrentState = pot2CurrentState + pot2Values[i];  
    }
    pot2CurrentState = pot2CurrentState / potMeasurementsCount;
    
    if (pot2State != pot2CurrentState) {
      MIDI.sendControlChange(pot2CC, pot2CurrentState, 1);
      pot2State = pot2CurrentState;
    }
    
    int pot3CurrentState = 0;
    for (int i = 0; i < potsCount; i++) {
      pot3CurrentState = pot3CurrentState + pot3Values[i];  
    }
    pot3CurrentState = pot3CurrentState / potMeasurementsCount;
    
    if (pot3State != pot3CurrentState) {
      MIDI.sendControlChange(pot3CC, pot3CurrentState, 1);
      pot3State = pot3CurrentState;
    }

    int pot4CurrentState = 0;
    for (int i = 0; i < potsCount; i++) {
      pot4CurrentState = pot4CurrentState + pot4Values[i];  
    }
    pot4CurrentState = pot4CurrentState / potMeasurementsCount;
    
    if (pot4State != pot4CurrentState) {
      MIDI.sendControlChange(pot4CC, pot4CurrentState, 1);
      pot4State = pot4CurrentState;
    }
    potsCount = 0;  
  }
  
  delay(1);
}
