#pragma once
#include "Arduino.h"
#include "static.h"
#include "state.h"

class TimeInputState : public State
{
public:
  TimeInputState(LiquidCrystal *lcd):
    State(lcd)
  {

  }

  virtual void Setup()
  {
    State::Setup();
    time = "0000";
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Input Time:");
    lcd->setCursor(0,1);
    lcd->print(time.substring(0,2) + ":" + time.substring(2,4));
  }

  virtual void KeyCallback(KeypadEvent key)
  {
    if(key == BACK_KEY)
    {
      if(time == "0000")
      {
        result = Result::FAILURE;
        next_state = STATE_WELCOME;
      }
      else
      {
        Setup();
      }
    }
    else if(key == CONFIRM_KEY)
    {
      result = Result::SUCCESS;
      next_state = STATE_POWER_INPUT;
    }
    else
    {
      //Add number to the end of the string, pushing the rest to the left
      Serial.println(time.c_str());
      time = time.substring(1,4);
      Serial.println(time.c_str());
      time += String(key);
      Serial.println(time.c_str());
      lcd->setCursor(0,1);
      lcd->print(time.substring(0,2) + ":" + time.substring(2,4));
    }
  }

  virtual int GetOutput()
  {
    int seconds = time.substring(2,2).toInt();
    int minutes = time.substring(0,2).toInt();
    return (minutes * 60) + seconds;
  }

  virtual int GetNextState()
  {
    return next_state;
  }

private:
  String time;
  int next_state;
};