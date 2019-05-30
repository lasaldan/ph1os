
#ifndef PH1Button_h
#define PH1Button_h

class PH1Button {

  public:
  
    PH1Button(void);
    
    void initButton(Adafruit_GFX *gfx, int16_t x, int16_t y,
      uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
      uint16_t textcolor, char *label, uint8_t textsize);
     
    void drawButton(boolean pressedState = false);
    
    boolean contains(int16_t x, int16_t y);
    
    void press(boolean p);
    
    boolean isPressed();
    
    boolean justPressed();
    
    boolean justReleased();

    char* getLabel();
    
  private:
    Adafruit_GFX *_gfx;
    int16_t       _x1, _y1; // Coordinates of top-left corner
    uint16_t      _w, _h;
    uint8_t       _textsize;
    uint16_t      _outlinecolor, _fillcolor, _textcolor;
    char          _label[30];
    
    boolean currstate, laststate;
};

#endif
