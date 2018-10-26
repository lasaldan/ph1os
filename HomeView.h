#include "PH1View.h";
#include "PH1Button.h";
#include "PhoneView.h";

#ifndef HomeView_h
#define HomeView_h

class HomeView : public PH1View {
  
  public:
  
    HomeView();
    PhoneView phoneView;

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    void clearTouch();


    PH1Button buttons[6];
};

#endif
