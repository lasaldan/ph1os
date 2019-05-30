#include "PH1View.h";
#include "PH1Button.h";
#include "PhoneView.h";
#include "TextView.h";
#include "BookView.h";

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

    void clearTouch();

    void redraw();

    PH1Button buttons[6];
};

#endif
