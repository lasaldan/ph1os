#include "CallView.h";
#include "PhoneView.h";

CallView::CallView( char* number,  char* destName){
  strcpy(calleeName, destName);
  strcpy(calleeNumber, number);

  title = "Calling ";

}

void CallView::onEnter() {
  
  char atString[16] = "ATD";
  strncpy(atString+3, calleeNumber, min(11, (int)strlen(calleeNumber)));
  uint8_t x = strlen(atString);
  atString[x] = ';';
  atString[x+1] = 0;

  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft->setTextSize(2);
  tft->setCursor(tft->width()/2 - (strlen(calleeName) * 3 * 2), 50);
  
  if(strlen(calleeName) > 0)
    tft->print(calleeName);
  else
    tft->print("Unknown Contact");
    
  tft->setTextSize(1);
  tft->setCursor(90, 150);
  tft->setCursor(tft->width()/2 - (strlen("Calling...") * 3 * 1), 75);
  tft->setTextColor(ILI9341_GREEN);

  tft->print("Calling...");

  tft->setTextSize(2);
  tft->setCursor(tft->width()/2 - (strlen(calleeNumber) * 3 * 2), 150);
  tft->setTextColor(ILI9341_WHITE);
  tft->print(calleeNumber);

  fonaSS->println(atString);
}

void CallView::onExit() {
}

void CallView::handleTouch(TSPoint p) {

}

void CallView::clearTouch() {

}

void CallView::handleNextButton() {
  fonaSS->println("AT+CHUP");
}

void CallView::handlePrevButton() {
  fonaSS->println("AT+CHUP");
  newView = new PhoneView();
  needNewViewLoaded = true;
}
