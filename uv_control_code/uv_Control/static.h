#pragma once
#include "Arduino.h"

#define TOTAL_STATES 4
enum StateNames
{
  USER_MSG_STATE,
  TIMER_INPUT_STATE,
  POWER_INPUT_STATE,
  POWERED_STATE
};
#define BACK_KEY '*'
#define CONFIRM_KEY '#'

class LCDPins
{
public:
  static const int pin_RS = 8; 
  static const int pin_EN = 9; 
  static const int pin_d4 = 4;
  static const int pin_d5 = 5; 
  static const int pin_d6 = 6; 
  static const int pin_d7 = 7; 
  static const int pin_BL = 10; 
};

class KeypadPins
{
public:
  static const byte ROWS = 4;
  static const byte COLS = 3;
  static const char hexKeys[ROWS][COLS];
  static const byte rowPins[ROWS]; 
  static const byte colPins[COLS]; 

};

