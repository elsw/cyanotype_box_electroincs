#pragma once
#include "state.h"

class UserMsgState : public State
{
public:
  UserMsgState(LiquidCrystal *lcd,String top = "", String bottom = ""):
    State(lcd),
    top(top),
    bottom(bottom)
  {

  }

  virtual void Setup()
  {
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print(top.c_str());
    lcd->setCursor(0,1);
    lcd->print(bottom.c_str());
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
  String top;
  String bottom;
};