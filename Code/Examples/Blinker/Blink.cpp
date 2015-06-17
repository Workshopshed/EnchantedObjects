#include "Blink.h"

Blinker::Blinker(unsigned int onLevel, unsigned int offLevel) {
    _onLevel = onLevel;
    _offLevel = offLevel;
    _state = 0;
}

unsigned long Blinker::Level(void)
{
  if (_offDuration == 0) { return _onLevel;}

  if (iTimeout < millis()) {
    if (_state == 0) {
     iTimeout = millis() + _onDuration;
    }
    else
    {
     iTimeout = millis() + _offDuration;
    }
    _state = !_state; 
  }
  
  if (_state = 0) { return _offLevel; }
  return _onLevel;
   
}

void Blinker::Blink(uint8_t Mode)
{
  switch (Mode) {
    case Short_Blink:
        _onDuration = 250;
        _offDuration = 250;
        break;
    case Long_Blink:
        _onDuration = 1000;
        _offDuration = 2000;
      break;
    default: //Solid_Blink
        _offDuration = 0;
  }   
}
