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

    void handleInput(char* );

    void clearTouch();

    bool needOSKeyboard;

    char* info();
    
    PH1Button buttons[6];
    char favoriteContactNames[6][21] = {"Marsha Sweety", "Mom", "Dad", "Stu", "Nathan", "Keypad" };
    char favoriteContactNumbers[6][21] = {"18013581600", "18013581600", "18013581600", "18013581600", "18013581600", "" };

    char textfield[12];
    uint8_t textfield_i=0;

};

#endif
