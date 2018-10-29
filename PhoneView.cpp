#include "PhoneView.h";
#include "CallView.h";
#include "HomeView.h";

PhoneView::PhoneView(){
  title = "Phone";
}

void PhoneView::onEnter() {
  
  char buttonlabels[6][9] = {"Marsha", "Mom", "Dad", "Stu", "Nathan", "Keypad" };

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

void PhoneView::onExit() {
}

void PhoneView::handleTouch(TSPoint p) {
  if(buttons[0].contains(p.x, p.y)) {
    newView = new CallView("18013581600", "Marsha");
    needNewViewLoaded = true;
  }
}

void PhoneView::clearTouch() {

}

void PhoneView::handleNextButton() {
}

void PhoneView::handlePrevButton() {
    newView = new HomeView();
    needNewViewLoaded = true;
}
