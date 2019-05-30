#include "PH1View.h";
#include "PH1Button.h";

#ifndef TextView_h
#define TextView_h

class TextView : public PH1View {
  
  public:
  
    TextView();

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    void handleInput(char* );

    void clearTouch();

    char* info();
    
    PH1Button buttons[6];
    char favoriteContactNames[6][21] = {"Marsha Sweety", "Mom", "Dad", "Stu", "Nathan", "Numpad" };
    char favoriteContactNumbers[6][21] = {"18013581600", "18013581600", "18013581600", "18013581600", "18013581600", "" };
    char contactNumber[12];

    char textfield[160];
    uint8_t textfield_i=0;

    enum State { Favorites, Dialing, Composing };
    State state;

};

#endif
