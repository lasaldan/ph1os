#include "HomeView.h";

HomeView::HomeView(){
  
}

void HomeView::onEnter() {
  char buttonlabels[6][9] = {"Phone", "Text", "Contacts", "Tools", "Books", "Other" };

  buttons[0].initButton(tft, 0, 12, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[0], 1);
  buttons[1].initButton(tft, 120, 12, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[1], 1);
  buttons[2].initButton(tft, 0, 91, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[2], 1);
  buttons[3].initButton(tft, 120, 91, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[3], 1);
  buttons[4].initButton(tft, 0, 170, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[4], 1);
  buttons[5].initButton(tft, 120, 170, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[5], 1);

  buttons[0].drawButton();
  buttons[1].drawButton();
  buttons[2].drawButton();
  buttons[3].drawButton();
  buttons[4].drawButton();
  buttons[5].drawButton();
}

void HomeView::onExit() {
}

void HomeView::handleTouch(TSPoint p) {
  
//  for (uint8_t b=0; b<6; b++) {
//    if (buttons[b].contains(p.x, p.y)) {
//      buttons[b].press(true);  // tell the button it is pressed
//      tft.print("Pressed");
//      tft.print(buttons[b].getLabel());
//      tft.print("        ");
//    } else {
//      buttons[b].press(false);  // tell the button it is NOT pressed
//    }
//  }


//  for (uint8_t b=0; b<1; b++) {
//    if (buttons[b].justReleased()) {
//      buttons[b].drawButton();  // draw normal
//    }
//      
//    if (buttons[b].justPressed()) {
//       buttons[b].drawButton(true);
//    }
//  }
  

}

void HomeView::handleNextButton() {
}

void HomeView::handlePrevButton() {
}

char* HomeView::info() {
  return "HVThing";
}
