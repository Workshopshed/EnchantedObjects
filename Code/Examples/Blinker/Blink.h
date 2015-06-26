#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#if not defined(INFINEONRGB_H)
  typedef enum{
  	White, Silver, Gray, Black, Red, Orange, Maroon, Yellow, Olive, Lime, Green, Aqua, Teal, Blue, Navy, Fuchsia, Purple
  	}Colours;
#endif

typedef enum{
  Off, Solid_Blink, Short_Blink, Long_Blink, Colour_Cycle	
  } BlinkMode;

class Blinker {
    unsigned long _onDuration;
    unsigned long _offDuration;
    unsigned int _onLevel;
    unsigned int _offLevel;
    unsigned long iTimeout;
    boolean _state;
    uint8_t _colour;
    static const uint8_t cycle_count = 16;
    uint8_t colour_cycle[cycle_count] = {   White,Silver,Gray,Black,Red,Maroon,Yellow,Olive,Lime,Green,Aqua,Teal,Blue,Navy,Fuchsia,Purple };
  public:
    Blinker(unsigned int onLevel, unsigned int offLevel);
    unsigned long Level(void);
    void Blink(uint8_t Mode);
    void SetColour(uint8_t Colour);  //Uses the colour from infineorgb.h
    uint8_t GetColour(void);
};

