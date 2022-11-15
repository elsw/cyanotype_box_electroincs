#pragma once
#include "state.h"

class UserMsgState : public State
{
public:
  UserMsgState(LiquidCrystal *lcd,String top, String bottom,int fail_state,int success_state):
    State(lcd),
    top(top),
    bottom(bottom),
    fail_state(fail_state),
    success_state(success_state),
    output(-1)
  {

  }

  virtual void Setup()
  {
    State::Setup();
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print(top.c_str());
    lcd->setCursor(0,1);
    lcd->print(bottom.c_str());
  }

  virtual void KeyCallback(KeypadEvent key)
  {
    if(key == BACK_KEY)
    {
      result = Result::FAILURE;
      next_state = fail_state;
      output = 0;
    }
    else if(key == CONFIRM_KEY)
    {
      result = Result::SUCCESS;
      next_state = success_state;
      output = 1;
    }
  }
  virtual int GetNextState()
  {
    return next_state;
  }
  virtual int GetOutput()
  {
    return output;
  }

private:
  String top;
  String bottom;
  int success_state;
  int fail_state;
  int next_state;
  int output;
};