#include "HomeView.h";

HomeView::HomeView(){
}

void HomeView::onEnter() {
  char buttonlabels[6][9] = {"Phone", "Text", "Contacts", "Tools", "Books", "Other" };

  int buttonHeight = VIEW_HEIGHT / 3;

  buttons[0].initButton(tft, 0, VIEW_TOP, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[0], 1);
  buttons[1].initButton(tft, 120, VIEW_TOP, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[1], 1);
  
  buttons[2].initButton(tft, 0, VIEW_TOP+buttonHeight, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[2], 1);
  buttons[3].initButton(tft, 120, VIEW_TOP+buttonHeight, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[3], 1);
  
  buttons[4].initButton(tft, 0, VIEW_TOP+buttonHeight*2, 121, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[4], 1);
  buttons[5].initButton(tft, 120, VIEW_TOP+buttonHeight*2, 120, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[5], 1);

  buttons[0].drawButton();
  buttons[1].drawButton();
  buttons[2].drawButton();
  buttons[3].drawButton();
  buttons[4].drawButton();
  buttons[5].drawButton();
}

void HomeView::onExit() {
}

void HomeView::redraw() {
  
  buttons[0].drawButton();
  buttons[1].drawButton();
  buttons[2].drawButton();
  buttons[3].drawButton();
  buttons[4].drawButton();
  buttons[5].drawButton();
}

void HomeView::handleTouch(TSPoint p) {
  if(buttons[0].contains(p.x, p.y)) {
    newView = new PhoneView();
    needNewViewLoaded = true;
  }  
  if(buttons[1].contains(p.x, p.y)) {
    newView = new TextView();
    needNewViewLoaded = true;
  }
  if(buttons[4].contains(p.x, p.y)) {
    newView = new BookView();
    needNewViewLoaded = true;
  }
    
  

//  for (uint8_t b=0; b<6; b++) {
//    if (buttons[b].contains(p.x, p.y)) {
//      buttons[b].press(true);  // tell the button it is pressed
//    } else {
//      buttons[b].press(false);  // tell the button it is NOT pressed
//    }
//  }
//
//  for (uint8_t b=0; b<6; b++) {
//    if (buttons[b].justReleased()) {
//      buttons[b].drawButton();  // draw normal
//    }
//      
//    if (buttons[b].justPressed()) {
//       buttons[b].drawButton(true);
//    }
//  }
  
}

void HomeView::clearTouch() {
//  for (uint8_t b=0; b<6; b++) {
//    buttons[b].drawButton();
//  }
}

void HomeView::handleNextButton() {
}

void HomeView::handlePrevButton() {
}
