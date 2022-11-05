#include "static.h"
#include "Arduino.h"

const char KeypadPins::hexKeys[KeypadPins::ROWS][KeypadPins::COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
  };

const byte KeypadPins::rowPins[KeypadPins::ROWS] = {11, A1 ,A2 , 13}; 
const byte KeypadPins::colPins[KeypadPins::COLS] = {12, A4, A3}; 