#include "TextView.h";
//#include "CallView.h";
#include "HomeView.h";

TextView::TextView(){
  title = "Text";
  state = Favorites;
}

void TextView::onEnter() {
  
  int buttonHeight = VIEW_HEIGHT / 3;

  buttons[0].initButton(tft, 0, VIEW_TOP, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[0], 1);
  buttons[1].initButton(tft, 120, VIEW_TOP, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[1], 1);
  
  buttons[2].initButton(tft, 0, VIEW_TOP+buttonHeight, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[2], 1);
  buttons[3].initButton(tft, 120, VIEW_TOP+buttonHeight, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[3], 1);
  
  buttons[4].initButton(tft, 0, VIEW_TOP+buttonHeight*2, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[4], 1);
  buttons[5].initButton(tft, 120, VIEW_TOP+buttonHeight*2, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, favoriteContactNames[5], 1);

  for(int i = 0; i < 6; i++) {
    buttons[i].drawButton();
  }
}

void TextView::onExit() {
}

void TextView::handleTouch(TSPoint p) {
  if(state == Favorites) {
    for(int i = 0; i < 6; i++) {
      if(buttons[i].contains(p.x, p.y)) {
        tft->fillRect(0, 20, tft->width(), 200, ILI9341_BLACK);
//        tft->drawRect(10, 30, 220, 100, ILI9341_WHITE);
        needOSKeyboard = true;
        state = Composing;
        strcpy(contactNumber, favoriteContactNumbers[i]);
      }
    }
  }
}

void TextView::handleInput(char* input) {
  if(state == Composing) {
    if (textfield_i < 159) {
      textfield[textfield_i] = *input;
      textfield_i++;
      textfield[textfield_i] = 0;
    }
    
    tft->setCursor(0, 24);
    tft->setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    tft->setTextSize(2);
    tft->print(textfield);
  }
  else if(state == Composing) {
    
  }
}

void TextView::clearTouch() {

}

void TextView::handleNextButton() {

}

void TextView::handlePrevButton() {
  if(state == Dialing) {
    needOSNumpad = false;
    textfield[0] = 0;
    textfield_i = 0;
    onEnter();
    state = Favorites;
  }
  else {
    newView = new HomeView();
    needNewViewLoaded = true;
  }
}
