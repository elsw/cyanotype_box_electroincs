#pragma once
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "static.h"

class State
{
  public:
    enum class Result
    {
      WAITING,
      SUCCESS,
      FAILURE
    };

    State(LiquidCrystal *lcd):
      lcd(lcd)
      {}
    
    //virtual void SetArguments(int argc,int *argv[]);
    virtual void Setup(){result = Result::WAITING;}
    virtual void KeyCallback(KeypadEvent key) = 0;
    virtual Result GetResult(){return result;}
    virtual int GetOutput(){return 0;}
    virtual int GetNextState() = 0;
    virtual void Update(int delta_millis){}

protected:
  LiquidCrystal *lcd;
  Result result;
};