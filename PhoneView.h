#include "PH1View.h";
#include "PH1Button.h";

#ifndef PhoneView_h
#define PhoneView_h

class PhoneView : public PH1View {
  
  public:
  
    PhoneView();

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    void clearTouch();

    bool needOSKeyboard;

    char* info();

    PH1Button buttons[6];
};

#endif
