#include "PhoneView.h";

PhoneView::PhoneView(){
  
}

void PhoneView::onEnter() {
  
  tft->fillRect(20,20,50,50, ILI9341_RED);
//  char buttonlabels[6][9] = {"1", "2", "3", "4", "5", "6" };
//
//  buttons[0].initButton(tft, 0, 12, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[0], 1);
//  buttons[1].initButton(tft, 120, 12, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[1], 1);
//  buttons[2].initButton(tft, 0, 91, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[2], 1);
//  buttons[3].initButton(tft, 120, 91, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[3], 1);
//  buttons[4].initButton(tft, 0, 170, 121, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[4], 1);
//  buttons[5].initButton(tft, 120, 170, 120, 80, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, buttonlabels[5], 1);
//
//  buttons[0].drawButton();
//  buttons[1].drawButton();
//  buttons[2].drawButton();
//  buttons[3].drawButton();
//  buttons[4].drawButton();
//  buttons[5].drawButton();
}

void PhoneView::onExit() {
}

void PhoneView::handleTouch(TSPoint p) {
  
}

void PhoneView::clearTouch() {

}

void PhoneView::handleNextButton() {
}

void PhoneView::handlePrevButton() {
}
