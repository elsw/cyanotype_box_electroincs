#include "static.h"

const char KeypadPins::hexKeys[KeypadPins::ROWS][KeypadPins::COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
  };

const byte KeypadPins::rowPins[KeypadPins::ROWS] = {9, 8, 7, 6}; 
const byte KeypadPins::colPins[KeypadPins::COLS] = {5, 4, 3}; 