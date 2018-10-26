
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "TouchScreen.h"

#ifndef PH1View_h
#define PH1View_h

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

class PH1View {
  
  public:
  
    PH1View();

    void initialize(Adafruit_ILI9341*);

    virtual void onEnter();

    virtual void onExit();

    virtual void handleTouch(TSPoint p);
    
    virtual void handleNextButton();
    
    virtual void handlePrevButton();

    virtual char* info();

    bool needOSKeyboard;
  
    Adafruit_ILI9341* tft;
    
};

#endif
