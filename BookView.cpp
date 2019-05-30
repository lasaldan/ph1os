#include "BookView.h";
#include "HomeView.h";

BookView::BookView(){
  title = "Books";
  state = VolumeSelect;
}

void BookView::onEnter() {

  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);  
  tft->setCursor(0,25);
  tft->setTextSize(2);

  tft->println("18. Behold, we go");
  tft->println("up to Jerusalem;");
  tft->println("and the Son of man");
  tft->println("shall be betrayed");
  tft->println("unto the chief");
  tft->println("priests and unto");
  tft->println("the scribes, and");
  tft->println("they shall condemn");
  tft->println("him to death,");
  tft->println("19. And shall");
  tft->println("deliver him to the");
  tft->println("Gentiles to mock,");
  tft->println("and to scourge, and");
  tft->println("to crucify him: and-");
  tft->println("the third day he");
  tft->println("shall rise again.");



//  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);  
//  tft->setCursor(0,25);
//  tft->setTextSize(1);
//
//  tft->println("1. I, Nephi, having been born of goodly");
//  tft->println("parents, therefore I was taught");
//  tft->println("somewhat in all the learning of my");
//  tft->println("father; and having seen many");
//  tft->println("afflictions in the course of my days,");
//  tft->println("nevertheless, having been highly");
//  tft->println("favored of the Lord in all my days;");
//  tft->println("yea, having had a great knowledge of");
//  tft->println("the goodness and the mysteries of God,");
//  tft->println("therefore I make a record of my");
//  tft->println("proceedings in my days.");
  
  

//  int buttonHeight = 30;
//
//  for(int i = 0; i < 5; i++) {
//    volumeButtons[i].initButton(tft-> 0, VIEW_TOP-i + i*buttonHeight, 240, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, volumeNames[i], 1);
//    volumeButtons[i].drawButton();
//  }
}

void BookView::onExit() {
}

void BookView::handleTouch(TSPoint p) {
  if(state == VolumeSelect) {
    for(int i = 0; i < 5; i++) {
      if(volumeButtons[i].contains(p.x, p.y)) {
//        state = BookSelect;
        volumePath[2] = '\0';
        volumePath[3] = '\0';
        strcpy(volumePath, volumePaths[i]);
        tft->setCursor(200,0);
        tft->println(volumePath);
      }
    }
  }
}

void BookView::handleInput(char* input) {

}

void BookView::clearTouch() {

}

void BookView::handleNextButton() {

}

void BookView::handlePrevButton() {

}
