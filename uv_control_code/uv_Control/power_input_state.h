#include "static.h"
#pragma once
#include "state.h"

class PowerInputState : public State
{
public:
  PowerInputState(LiquidCrystal *lcd):
    State(lcd)
  {

  }

  virtual void Setup()
  {
    State::Setup();
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Input Power:");
    lcd->setCursor(0,1);
    power = "";
  }

  virtual void KeyCallback(KeypadEvent key)
  {
    if(key == BACK_KEY)
    {
      if(power == "")
      {
        result = Result::FAILURE;
        next_state = STATE_TIMER_INPUT;
      }
      else
      {
        Setup();
      }
    }
    else if(key == CONFIRM_KEY)
    {
      result = Result::SUCCESS;
      next_state = STATE_POWERED;
    }
    else
    {
      //Add key to power number
      power += key;
      lcd->setCursor(0,1);
      lcd->print(power);
    }
  }

  virtual int GetOutput()
  {
    return power.toInt();
  }

  virtual int GetNextState()
  {
    return next_state;
  }

private:
  String power;
  int next_state;
};