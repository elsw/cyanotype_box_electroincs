#include "static.h"
#include <LiquidCrystal.h>
#include <Keypad.h>
#include "state.h"
#include "time_input_state.h"
#include "power_input_state.h"
#include "user_msg_state.h"

LiquidCrystal lcd( LCDPins::pin_RS,  LCDPins::pin_EN,  LCDPins::pin_d4,  LCDPins::pin_d5,  LCDPins::pin_d6,  LCDPins::pin_d7);
Keypad keypad = Keypad(makeKeymap(KeypadPins::hexKeys), KeypadPins::rowPins, KeypadPins::colPins, KeypadPins::ROWS, KeypadPins::COLS);
State* states[TOTAL_STATES];
unsigned current_state;

String user_input;
unsigned timer_s;
unsigned power_percentage;
unsigned millis_start;

void KeyCallback(KeypadEvent key)
{
  State::Result result = states[current_state]->KeyCallback(key);

  if(result == State::Result::SUCCESS)
  {

  }
  else if(result == State::Result::FAILURE)
  {

  }
}

void setup() 
{
 Serial.begin(9600);
 lcd.begin(16, 2);
 keypad.addEventListener(KeyCallback);

 states[USER_MSG_STATE] = new UserMsgState(&lcd);
 states[TIMER_INPUT_STATE] = new TimeInputState(&lcd);
 states[POWER_INPUT_STATE] = new PowerInputState(&lcd);

 current_state = 0;
 states[USER_MSG_STATE]->Setup("Emilys Amazing","UV Control Box");
}

void loop()
{
  unsigned now = millis();

  char key = keypad.getKey();
}















