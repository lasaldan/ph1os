#include "PH1View.h";
#include "PH1Button.h";

#ifndef CallView_h
#define CallView_h

class CallView : public PH1View {
  
  public:
  
    CallView( char*,  char*);

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    void clearTouch();

    bool needOSKeyboard;

    char* info();

    char calleeName[31];
    char calleeNumber[12];

};

#endif
