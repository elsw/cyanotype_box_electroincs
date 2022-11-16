#include "static.h"
#include <LiquidCrystal.h>
#include <Keypad.h>
#include "state.h"
#include "time_input_state.h"
#include "power_input_state.h"
#include "user_msg_state.h"
#include "powered_state.h"

LiquidCrystal lcd( LCDPins::pin_RS,  LCDPins::pin_EN,  LCDPins::pin_d4,  LCDPins::pin_d5,  LCDPins::pin_d6,  LCDPins::pin_d7);
Keypad keypad = Keypad(makeKeymap(KeypadPins::hexKeys), KeypadPins::rowPins, KeypadPins::colPins, KeypadPins::ROWS, KeypadPins::COLS);
State* states[TOTAL_STATES];
int outputs[TOTAL_STATES];
unsigned current_state;

String user_input;
unsigned timer_s;
unsigned power_percentage;
unsigned last_millis;

void InternalError()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Internal Error");
  lcd.setCursor(0,1);
  lcd.print("State : ");
  lcd.print(current_state);
  delay(1000);
}

void KeyCallback(KeypadEvent key)
{
  //Only trigger on rising edge
  if(keypad.getState() == PRESSED)
  {
    states[current_state]->KeyCallback(key);
  }
}

void setup() 
{
 Serial.begin(9600);
 lcd.begin(16, 2);
 pinMode(PWR_EN_PIN,OUTPUT);
 pinMode(SAFETY_PIN,INPUT);
 //pinMode(STATUS_LED_PIN,OUTPUT);
 pinMode(SAFETY_LED_PIN,OUTPUT);
 keypad.addEventListener(KeyCallback);

 states[STATE_WELCOME] = new UserMsgState(&lcd,"Emilys Amazing","UV Control Box",STATE_WELCOME,STATE_TIMER_INPUT);
 states[STATE_TIMER_INPUT] = new TimeInputState(&lcd);
 states[STATE_POWER_INPUT] = new PowerInputState(&lcd);
 states[STATE_POWERED] = new PoweredState(&lcd,&outputs[0]);
 states[STATE_SAFETY_ERROR] = new UserMsgState(&lcd,"Safety Error!","Continue?",STATE_WELCOME,STATE_POWERED);

 current_state = 0;
 states[current_state]->Setup();
 last_millis = millis();
}

void loop()
{
  unsigned now = millis();
  int delta_millis = now - last_millis;
  last_millis = now;
  //Must call keypad update for the event listener to trigger
  keypad.getKey();

  int safety_ok = digitalRead(SAFETY_PIN);
  digitalWrite(SAFETY_LED_PIN,safety_ok);

  if(current_state < TOTAL_STATES)
  { 
    states[current_state]->Update(delta_millis);

    State::Result result = states[current_state]->GetResult();
    if(result != State::Result::WAITING)
    {
      String print = String("Got Result") + String(static_cast<int>(result));
      Serial.write(print.c_str());
      if(result == State::Result::SUCCESS)
      {
        outputs[current_state] = states[current_state]->GetOutput();
      }
      current_state = states[current_state]->GetNextState();
      if(current_state < TOTAL_STATES)
      {
        states[current_state]->Setup();
      }
      else 
      { 
        InternalError(); 
      }
    }  
  }
  else
  { 
    InternalError(); 
  }
}















