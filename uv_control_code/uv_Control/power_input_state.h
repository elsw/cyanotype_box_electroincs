#pragma once
#include "state.h"

class PowerInputState : public State
{
public:
  PowerInputState(LiquidCrystal *lcd):
    State(lcd)
  {

  }

  virtual void Setup(String top = "", String bottom = "")
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
      
    }
  }

  virtual int GetOutput()
  {

  }

private:
  String time;
};