#include "Blink.h"

Blinker::Blinker(unsigned int onLevel, unsigned int offLevel) {
    _onLevel = onLevel;
    _offLevel = offLevel;
    _state = 0;
    _mode = Blink_Off;
}

unsigned long Blinker::Level(void)
{
  if (_offDuration == 0) { return _onLevel;}
  if (_onDuration == 0)  { return _offLevel;}

  if (_iTimeout < millis()) {
    if (_state == 0) {
     _iTimeout = millis() + _onDuration;
    }
    else {
     _iTimeout = millis() + _offDuration;
    }
    _state = !_state; 
  }
  
  if (_state == 0) { return _offLevel; }
  return _onLevel;
   
}

void Blinker::Blink(uint8_t Mode)
{
  _mode = Mode;
  switch (Mode) {
    case Blink_Short:
        _onDuration = 250;
        _offDuration = 250;
        break;
    case Blink_Long:
        _onDuration = 1000;
        _offDuration = 2000;
      break;
    case Blink_Off:
        _onDuration = 0;  
        _offDuration = 1000;  // Time does not matter for this but need to be > 0
        break;
    default: //Solid_Blink + 
        _offDuration = 0;
        _onDuration = 1000;  // Time used to determine the colour cycle frequency
  }   
}

void Blinker::SetColour(uint8_t Colour)
//Uses the colours from infineorgb.h
{
  _colour = Colour;
}

uint8_t Blinker::GetColour(void){
  if (_mode != Blink_Cycle) {  return _colour;}
  
  if (_iTimeout < millis()) {
    _colour = (_colour + 1) % (ColourMax+1);
    _iTimeout = millis() + _onDuration;
  }

  return _colour;    
}

