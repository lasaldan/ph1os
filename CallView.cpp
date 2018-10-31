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
//  tft->setCursor(30, 50);
  
  if(strlen(calleeName) > 0)
    tft->print(calleeName);
  else
    tft->print("Unknown Contact");
    
  tft->setTextSize(2);
  tft->setCursor(30, 150);
  tft->print("Dialing...");

  
  fonaSS->println(atString);
  
  
}

void CallView::onExit() {
}

void CallView::handleTouch(TSPoint p) {

}

void CallView::clearTouch() {

}

void CallView::handleNextButton() {
  fonaSS->println("ATH");
}

void CallView::handlePrevButton() {
  fonaSS->println("ATH");
  newView = new PhoneView();
  needNewViewLoaded = true;
}
