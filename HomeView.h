#include "PH1View.h";
#include "PH1Button.h";

#ifndef HomeView_h
#define HomeView_h

class HomeView : public PH1View {
  
  public:
  
    HomeView();

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    bool needOSKeyboard;

    char* info();

    PH1Button buttons[6];
};

#endif
