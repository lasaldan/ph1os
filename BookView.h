#include "PH1View.h";
#include "PH1Button.h";

#ifndef BookView_h
#define BookView_h

class BookView : public PH1View {
  
  public:
  
    BookView();

    void onEnter();

    void onExit();

    void handleTouch(TSPoint p);
    
    void handleNextButton();
    
    void handlePrevButton();

    void handleInput(char* );

    void clearTouch();

    char* info();
    
    PH1Button volumeButtons[5];
    char volumeNames[5][23] = {"Old Testament", "New Testament", "Book of Mormon", "Doctrine and Covenants", "Pearl of Great Price" };
    char volumePaths[5][4] = {"ot", "nt", "bm", "dc", "pgp"};

    char volumePath[4];

    enum State { VolumeSelect, BookSelect, ChapterSelect };
    State state;

};

#endif
