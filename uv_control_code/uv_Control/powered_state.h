#pragma once
#include "Arduino.h"
#include "static.h"
#include "state.h"

class PoweredState : public State
{
public:
  PoweredState(LiquidCrystal *lcd,int * outputs):
    State(lcd),
    outputs(outputs)
  {

  }

  virtual void Setup()
  {
    State::Setup();
    total_seconds = outputs[STATE_TIMER_INPUT];
    power_percentage = outputs[STATE_POWER_INPUT];

    //If coming from a safety error, dont reset timer if the user presses continue
    bool reset_timer = static_cast<bool>(outputs[STATE_SAFETY_ERROR]);

    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("UV Powered");
    lcd->setCursor(0,1);

    if(reset_timer)
    {
      millis_left = total_seconds * 1000;
    }

    digitalWrite(PWR_EN_PIN,HIGH);
  }

  virtual void KeyCallback(KeypadEvent key)
  {
    if(key == BACK_KEY)
    {
      result = State::Result::FAILURE;
      next_state = STATE_WELCOME;
      output = 0;
      digitalWrite(PWR_EN_PIN,LOW);
    }
    else if(key == CONFIRM_KEY)
    {

    }
  }

  virtual int GetOutput()
  {
    return output;
  }

  virtual int GetNextState()
  {
    return next_state;
  }

  virtual void Update(int delta_millis)
  {
    millis_left -= delta_millis;
    float seconds_left = static_cast<float>(millis_left) / 1000;
    if(seconds_left != last_seconds_left)
    {
      if(seconds_left > 0)
      {
        int minutes = static_cast<int>(seconds_left) / 60;
        int seconds = static_cast<int>(seconds_left) % 60;
        String time_left = String(minutes) + ":" + String(seconds);
        lcd->setCursor(0,1);
        lcd->print(time_left);
      }
      else
      {
        lcd->setCursor(0,1);
        lcd->print("00:00 Done!");
        output = 1;
      }
    }

    //Check safety
    int safety_ok = digitalRead(SAFETY_PIN);
    if(!safety_ok)
    {
      result = State::Result::FAILURE;
      next_state = STATE_SAFETY_ERROR;
      digitalWrite(PWR_EN_PIN,LOW);
      output = 0;
    }

    last_seconds_left = seconds_left;
  }

private:
  String time_remaining;
  int next_state;
  int * outputs;
  int output;

  int total_seconds;
  int power_percentage;
  int last_seconds_left;
  unsigned millis_left;
};