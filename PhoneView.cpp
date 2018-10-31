#include "PhoneView.h";
#include "CallView.h";
#include "HomeView.h";

PhoneView::PhoneView(){
  title = "Phone";
}

void PhoneView::onEnter() {
  
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

void PhoneView::onExit() {
}

void PhoneView::handleTouch(TSPoint p) {
  for(int i = 0; i < 5; i++) {
    if(buttons[i].contains(p.x, p.y)) {
      newView = new CallView(favoriteContactNumbers[i], favoriteContactNames[i]);
      needNewViewLoaded = true;
    }
  }
  
  if(buttons[5].contains(p.x, p.y)) {
    tft->fillRect(0, 20, tft->width(), 200, ILI9341_BLACK);
    tft->drawRect(10, 30, 220, 50, ILI9341_WHITE);
    needOSNumpad = true;
  }
}

void PhoneView::handleInput(char* input) {
  if(*input == 'D') {
    textfield[textfield_i] = 0;
    if (textfield > 0) {
      textfield_i--;
      textfield[textfield_i] = ' ';
    }
  }
  else if(*input == 'C') {
    textfield[0] = 0;
    textfield_i = 0;
    tft->fillRect(11, 31, 218, 48, ILI9341_BLACK);
  }
  else if (textfield_i < 11) {
    textfield[textfield_i] = *input;
    textfield_i++;
    textfield[textfield_i] = 0;
            
//    fona.playDTMF(input);
  }
  
  tft->setCursor(20, 44);
  tft->setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  tft->setTextSize(3);
  tft->print(textfield);
}

void PhoneView::clearTouch() {

}

void PhoneView::handleNextButton() {
}

void PhoneView::handlePrevButton() {
    newView = new HomeView();
    needNewViewLoaded = true;
}
