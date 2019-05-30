
#include <Adafruit_GFX.h>
#include "PH1Button.h";

PH1Button::PH1Button(void) {
  _gfx = 0;
}

void PH1Button::initButton( Adafruit_GFX *gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h, uint16_t outline, uint16_t fill, uint16_t textcolor, char *label, uint8_t textsize ) {
  _x1 = x1;
  _y1 = y1;
  _w = w;
  _h = h;
  _outlinecolor = outline;
  _fillcolor = fill;
  _textcolor = textcolor;
  _textsize = textsize;
  _gfx = gfx;
  strncpy(_label, label, 29);
}

void PH1Button::drawButton(boolean inverted) {
  uint16_t fill, outline, text;

  if(!inverted) {
    fill    = _fillcolor;
    outline = _outlinecolor;
    text    = _textcolor;
  } else {
    fill    = _textcolor;
    outline = _outlinecolor;
    text    = _fillcolor;
  }

  _gfx->fillRect(_x1, _y1, _w, _h, fill);
  _gfx->drawRect(_x1, _y1, _w, _h, outline);

  _gfx->setCursor(_x1 + (_w/2) - (strlen(_label) * 3 * _textsize),
    _y1 + (_h/2) - (4 * _textsize));
  _gfx->setTextColor(text);
  _gfx->setTextSize(_textsize);
  _gfx->print(_label);
}

char* PH1Button::getLabel() { return _label; }

boolean PH1Button::contains(int16_t x, int16_t y) {
  return ((x >= _x1) && (x < (int16_t) (_x1 + _w)) &&
          (y >= _y1) && (y < (int16_t) (_y1 + _h)));
}

void PH1Button::press(boolean p) {
  laststate = currstate;
  currstate = p;
}

boolean PH1Button::isPressed() { return currstate; }

boolean PH1Button::justPressed() { return (currstate && !laststate); }

boolean PH1Button::justReleased() { return (!currstate && laststate); }
