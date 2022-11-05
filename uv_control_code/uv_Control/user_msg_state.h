#pragma once
#include "state.h"

class UserMsgState : public State
{
public:
  UserMsgState(LiquidCrystal *lcd):
    State(lcd)
  {

  }

  virtual void Setup(String top = "", String bottom = "")
  {
    lcd->clear();
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
};