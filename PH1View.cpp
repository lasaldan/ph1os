#include "PH1View.h";

PH1View::PH1View(){
  needNewViewLoaded = false;
  needOSKeyboard = false;
  title = "Home";
}

void PH1View::initialize(Adafruit_ILI9341 *ostft, Adafruit_FONA *osfona) {
  tft = ostft;
  fona = osfona;
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
//
//void PH1View::flushSerial() {
//  while (fonaSerial->available())
//    fonaSerial->read();
//}
//
//uint8_t PH1View::readline(char *buff, uint8_t maxbuff, uint16_t timeout) {
//  uint16_t buffidx = 0;
//  boolean timeoutvalid = true;
//  if (timeout == 0) timeoutvalid = false;
//
//  while (true) {
//    if (buffidx > maxbuff) {
//      //Serial.println(F("SPACE"));
//      break;
//    }
//
//    while (fonaSerial->available()) {
//      char c =  fonaSerial->read();
//
//      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);
//
//      if (c == '\r') continue;
//      if (c == 0xA) {
//        if (buffidx == 0)   // the first 0x0A is ignored
//          continue;
//
//        timeout = 0;         // the second 0x0A is the end of the line
//        timeoutvalid = true;
//        break;
//      }
//      buff[buffidx] = c;
//      buffidx++;
//    }
//
//    if (timeoutvalid && timeout == 0) {
//      //Serial.println(F("TIMEOUT"));
//      break;
//    }
//    delay(1);
//  }
//  buff[buffidx] = 0;  // null term
//  return buffidx;
//}
