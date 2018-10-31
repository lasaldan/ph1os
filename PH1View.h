#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "SoftwareSerial.h"
//#include "Adafruit_FONA.h"
#include "TouchScreen.h"

#ifndef PH1View_h
#define PH1View_h

#define FONA_RST 11

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

class PH1View {
  
  public:
  
    PH1View();

    void initialize(Adafruit_ILI9341*, SoftwareSerial*);

    virtual void onEnter();

    virtual void onExit();

    virtual void handleTouch(TSPoint p);
    
    virtual void handleNextButton();
    
    virtual void handlePrevButton();

    virtual void clearTouch();

    virtual void handleInput(char*);

    bool needOSKeyboard;
    bool needOSKeyboardClosed;
    bool needOSNumpad;
    bool needOSNumpadClosed;
    bool needNewViewLoaded;
    PH1View * newView;
    char* title;
    const int VIEW_TOP = 20;
    const int VIEW_BOTTOM = 284;
    const int VIEW_HEIGHT = 264;
  
    Adafruit_ILI9341* tft;
    SoftwareSerial* fonaSS;

    void flushSerial();

    uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

  
};

#endif
