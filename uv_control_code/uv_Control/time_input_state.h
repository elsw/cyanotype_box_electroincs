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
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Input Time:");
    lcd->setCursor(0,1);
    time = "0000";
  }

  virtual Result KeyCallback(KeypadEvent key)
  {
    if(key == BACK_KEY)
    {
      result = Result::FAILURE;
    }
    else if(key == CONFIRM_KEY)
    {
      result = Result::SUCCESS;
    }
    else
    {
      //Add number to the end of the string, pushing the rest to the left
      time = time.substring(1,3);
      time += key;
      lcd->setCursor(0,1);
      lcd->print(time.substring(0,1) + ":" + time.substring(2,3));
    }
  }

  virtual int GetOutput()
  {
    int seconds = time.substring(2,3).toInt();
    int minutes = time.substring(0,1).toInt();
  }
private:
  String time;
};