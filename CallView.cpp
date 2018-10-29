#include "CallView.h";
#include "CallView.h";

CallView::CallView( char* number,  char* destName){
//  Serial.println("Constructing");
//  strcpy(calleeName, destName);
  Serial.println(number);
//  strcpy(calleeNumber, number);
  Serial.println(destName);
  title = "Calling ";
//  strcat(title, number);
//  Serial.println("Constructed");
//  flushSerial();
//  Serial.print(F("Call #"));
  //readline(number, 30);
//  Serial.println();
  //Serial.print(F("Calling ")); Serial.println(number);

//  char sendbuff[35] = "ATD";
//  strncpy(sendbuff+3, number, min(30, (int)strlen(number)));
//  uint8_t x = strlen(sendbuff);
//  sendbuff[x] = ';';
//  sendbuff[x+1] = 0;
//  Serial.println("Sending:");
//  Serial.println(sendbuff);
//  fonaSerial->println(sendbuff);
//  fona->callPhone(number);
//  Serial.println("Sent to fona");
  char numbers[12] = "18013581600";
  numbers[12] = '\0';

  if (!fona->callPhone(numbers)) {
    Serial.println("Failed");
  } else {
    Serial.println("Sent!");
  }
}

void CallView::onEnter() {
//  char number[30];
//  flushSerial();
//  Serial.print(F("Call #"));
//  readline(number, 30);
//  Serial.println();
//  Serial.print(F("Calling ")); Serial.println(number);
//  if (!fona.callPhone(number)) {
//    Serial.println(F("Failed"));
//  } else {
//    Serial.println(F("Sent!"));
//  }
}

void CallView::onExit() {
}

void CallView::handleTouch(TSPoint p) {

}

void CallView::clearTouch() {

}

void CallView::handleNextButton() {
}

void CallView::handlePrevButton() {
}
