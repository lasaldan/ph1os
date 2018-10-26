#include "PH1View.h";

PH1View::PH1View(){
  needNewViewLoaded = false;
  needOSKeyboard = false;
}

void PH1View::initialize(Adafruit_ILI9341 *ostft) {
  Serial.print("Initializing New View");
  tft = ostft;
}

void PH1View::onEnter(){
  
}

void PH1View::onExit(){
  
}

void PH1View::handleTouch(TSPoint p){
  
}

void PH1View::handleNextButton(){
  
}

void PH1View::handlePrevButton(){
  
}

void PH1View::clearTouch(){
  
}
