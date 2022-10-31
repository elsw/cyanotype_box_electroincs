#include "static.h"
#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd( LCDPins::pin_RS,  LCDPins::pin_EN,  LCDPins::pin_d4,  LCDPins::pin_d5,  LCDPins::pin_d6,  LCDPins::pin_d7);
Keypad keypad = Keypad(makeKeymap(KeypadPins::hexKeys), KeypadPins::rowPins, KeypadPins::colPins, KeypadPins::ROWS, KeypadPins::COLS);
State state;

char BACK_KEY = '*';
char CONFIRM_KEY = '#';

String user_input;
unsigned timer_s;
unsigned power_percentage;
unsignes millis_start;

void KeyCallback(char key)
{
  if(state == State::USER_MESSAGE)
  {
    TimerInputScreen();
  }
  else if(state == State::TIMER_INPUT)
  {
    if(key == BACK_KEY)
    {
      WelcomeScreen();
    }
    else if(key == CONFIRM_KEY)
    {
      state = State::TIMER_INPUT;
      PowerInputScreen();
      timer_s = user_input.toInt();
    }
    else
    {
        user_input += key;
        lcd.print(user_input.c_str());
    }
  }
  else if(state == State::POWER_INPUT)
  {
    if(key == BACK_KEY)
    {
      TimerInputScreen();
    }
    else if(key == CONFIRM_KEY)
    {
      state = State::POWERED;
      millis_start = millis();
    }
    else
    {
      user_input += key;
      lcd.print(user_input.c_str());
    }
  }
}

void WelcomeScreen()
{
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Emilys Amazing");
 lcd.setCursor(0,1);
 lcd.print("UV Light Box");
 state = State::USER_MESSAGE;
}
void TimerInputScreen()
{
  state = State::TIMER_INPUT;
  user_input = "";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input Time:");
  lcd.setCursor(0,1);
}
void PowerInputScreen()
{
  state = State::POWER_INPUT;
  user_input = "";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input Power:");
  lcd.setCursor(0,1);
}
void PoweredScreen()
{
  
}

void setup() 
{
 lcd.begin(16, 2);
 keypad.addEventListener(KeyCallback);
 WelcomeScreen();
}

void loop()
{
  unsigned now = millis();
  
  if(state == State::POWERED)
  {

  }
}















