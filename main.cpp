/*
 * Daniel Fuller
 * OS for PH1
 */

#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include "./includes/SD/SD.h"
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include "./SoftwareSerial.h"
#include "./Adafruit_FONA.h"
#include "./TouchScreen.h"
#include "PH1Button.h"
#include "PH1View.h"
#include "HomeView.h"
#include "CallView.h"


#define TFT_CS   2
#define TFT_DC   3
#define TFT_LITE 4
#define SD_CS    7

#define FONA_RX 13
#define FONA_TX 12
#define FONA_RST 11
#define FONA_KEY A1

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 10   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 310
#define TS_MINY 190
#define TS_MAXX 810
#define TS_MAXY 850

#define TOOLBAR_TOP 290
#define TOOLBAR_HEIGHT 30
#define NUMPAD_TOP 170
#define INFO_BAR_HEIGHT 10
#define TITLE_BAR_HEIGHT 10

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

PH1View *currentView;

bool numpadOpen = false;
bool keyboardOpen = false;
char numpadButtonLabels[12][4] = {"1","2","3","4","5","6","7","8","9","CLR","0","DEL"};
char keyboardButtonLabels[40][2] = {"q","w","e","r","t","y","u","i","o","p",
                                    "a","s","d","f","g","h","j","k","l",".",
                                    ",","z","x","c","v","b","n","m","!","?",
                                    "#","'","$"," "," "," "," ","-","+","^"};
enum State { Default, IncomingCall };

State state = Default;

PH1Button numpadButtons[12];
PH1Button incomingCallButtons[2];
PH1Button keyboardButtons[40];
char incomingNumber[12];
int lastRing = millis();

int appBottom = TOOLBAR_TOP;

//char buttonlabels[6][9] = {"Phone", "Text", "Contacts", "Tools", "Books", "Other" };
//PH1Button buttons[6];

char receivedChars[50];
int receivedChars_i = 0;

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
//SoftwareSerial *fonaSerial = &fonaSS;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 284);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int width = tft.width();
int height = tft.height();
int updateInterval = 10000;
int dimLCDAfter = 25000;
int offLCDAfter = 30000;
int toolbarUpdateAt = millis() + updateInterval;
int lastActivity = millis();
int lcdState;

bool validTouchDetected = false;
int noTouchCount = 0;

int touchInterval = 250;
int acceptNextTouchAt = millis();

File root;


void drawToolbar(int y) {
  tft.fillRect(1,y+1,tft.width()-2, TOOLBAR_HEIGHT-2, ILI9341_BLACK);
  tft.drawLine(0,y,width,y,ILI9341_WHITE);
  tft.drawLine(0,y+1,width,y+1,ILI9341_WHITE);
  tft.drawLine(0,y+TOOLBAR_HEIGHT-1,width,y+TOOLBAR_HEIGHT-1,ILI9341_WHITE);
  tft.drawLine(tft.width()-1,y,tft.width()-1,y+TOOLBAR_HEIGHT-1,ILI9341_WHITE);
  tft.drawLine(0,y,0,y+TOOLBAR_HEIGHT-1,ILI9341_WHITE);

  tft.drawLine(80,y,80,y + TOOLBAR_HEIGHT,ILI9341_WHITE);
  tft.drawLine(160,y,160,y + TOOLBAR_HEIGHT,ILI9341_WHITE);

  // 'Left', 15x24px
  const unsigned char left [] PROGMEM = {
    0x00, 0x1c, 0x00, 0x3e, 0x00, 0x7e, 0x00, 0xfe, 0x01, 0xfc, 0x03, 0xf8, 0x07, 0xf0, 0x0f, 0xe0,
    0x1f, 0xc0, 0x3f, 0x80, 0x7f, 0x00, 0xfe, 0x00, 0xfe, 0x00, 0x7f, 0x00, 0x3f, 0x80, 0x1f, 0xc0,
    0x0f, 0xe0, 0x07, 0xf0, 0x03, 0xf8, 0x01, 0xfc, 0x00, 0xfe, 0x00, 0x7e, 0x00, 0x3e, 0x00, 0x1c
  };
  // 'Right', 15x24px
  const unsigned char right [] PROGMEM = {
    0x70, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0x7f, 0x00, 0x3f, 0x80, 0x1f, 0xc0, 0x0f, 0xe0,
    0x07, 0xf0, 0x03, 0xf8, 0x01, 0xfc, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0xfc, 0x03, 0xf8, 0x07, 0xf0,
    0x0f, 0xe0, 0x1f, 0xc0, 0x3f, 0x80, 0x7f, 0x00, 0xfe, 0x00, 0xfc, 0x00, 0xf8, 0x00, 0x70, 0x00
  };
  // 'home', 24x24px
  const unsigned char homeicon [] PROGMEM = {
    0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xff, 0x00, 0x01, 0xff, 0x80, 0x03,
    0xff, 0xc0, 0x07, 0xff, 0xe0, 0x0f, 0xff, 0xf0, 0x1f, 0xff, 0xf8, 0x3f, 0xff, 0xfc, 0x7f, 0xff,
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xfc, 0x3f, 0xff, 0xfc, 0x3f, 0xc3, 0xfc,
    0x3f, 0xc3, 0xfc, 0x3f, 0xc3, 0xfc, 0x3f, 0xc3, 0xfc, 0x3f, 0xc3, 0xfc, 0x3f, 0xc3, 0xfc, 0x3f,
    0xc3, 0xfc, 0x3f, 0xc3, 0xfc, 0x1f, 0x81, 0xf8
  };


  tft.drawBitmap(32, y+4, left, 15, 24, ILI9341_WHITE);
  tft.drawBitmap(192, y+4, right, 15, 24, ILI9341_WHITE);
  tft.drawBitmap(108, y+4, homeicon, 24, 24, ILI9341_WHITE);

}

void updateTitleBar(char*title) {
  tft.setTextSize(1);
  tft.setCursor(tft.width()/2 - (strlen(title) * 3), INFO_BAR_HEIGHT+1);
  tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
  tft.print(title);
}


void turnOffLCD() {
  pinMode(TFT_LITE, INPUT);
  pinMode(TFT_LITE, OUTPUT);
  digitalWrite(TFT_LITE, LOW);
  lcdState = 0;
}

void turnOnLCD() {
  pinMode(TFT_LITE, OUTPUT);
  digitalWrite(TFT_LITE, HIGH);
  lcdState = 1;
}

void setBrightness(int percent) {
  pinMode(TFT_LITE, OUTPUT);
  lcdState = 2;
  analogWrite(TFT_LITE, percent);
}

void hideIncomingModal() {
  currentView->redraw();
  state = Default;
}

void showIncomingModal() {
  state = IncomingCall;
  tft.fillRect(30, 100, 180, 120, ILI9341_BLACK);
  tft.drawRect(30, 100, 180, 120, ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(43, 110);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("Incoming Call");

  incomingCallButtons[0].initButton(&tft, 30, 190, 90, 30, COLOR_WHITE, COLOR_BLACK, ILI9341_GREEN, "Answer", 1);
  incomingCallButtons[1].initButton(&tft, 120, 190, 90, 30, COLOR_WHITE, COLOR_BLACK, ILI9341_RED, "Ignore", 1);
  incomingCallButtons[0].drawButton();
  incomingCallButtons[1].drawButton();

}
void parseSerialInput() {
  if(receivedChars[0] == 'R' && receivedChars[1] == 'I' && receivedChars[2] == 'N' && receivedChars[3] == 'G' && state != IncomingCall) {
    if(state != IncomingCall)
      showIncomingModal();
    lastRing = millis();
  }
  if(receivedChars[0] == '+' && receivedChars[1] == 'C' && receivedChars[2] == 'L' && receivedChars[3] == 'I' && receivedChars[4] == 'P') {
    strncpy ( incomingNumber, receivedChars+9, 11 );
    incomingNumber[12] = '\0';
    if(state == IncomingCall) {
      tft.setCursor(55, 150);
      tft.setTextSize(2);
      tft.setTextColor(ILI9341_YELLOW);
      tft.print(incomingNumber);
    }
  }
  receivedChars[0] = '\0';
  receivedChars_i = 0;
}

void disableNumpad() {
  appBottom = TOOLBAR_TOP;
  numpadOpen = false;
  drawToolbar(TOOLBAR_TOP);
}

void enableNumpad() {

  int buttonHeight = 30;
  int numpadTop = tft.height() - buttonHeight * 4;

  for(int i = 0; i < 12; i++) {
    int row = i / 3;
    int col = i % 3;
    numpadButtons[i].initButton(&tft, 80*col, numpadTop+buttonHeight*row, 80, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, numpadButtonLabels[i], 1);
    numpadButtons[i].drawButton();
  }

  numpadOpen = true;

  appBottom = NUMPAD_TOP;
  drawToolbar(NUMPAD_TOP);
}

void disableKeyboard() {
  appBottom = TOOLBAR_TOP;
  keyboardOpen = false;

  drawToolbar(TOOLBAR_TOP);
}

void enableKeyboard() {

  int buttonHeight = 30;
  int keypadTop = tft.height() - buttonHeight * 4;
  int buttonWidth = tft.width() / 10;

  for(int i = 0; i < 40; i++) {
    int row = i / 10;
    int col = i % 10;
    keyboardButtons[i].initButton(&tft, buttonWidth*col, keypadTop+buttonHeight*row, buttonWidth, buttonHeight, COLOR_WHITE, COLOR_BLACK, COLOR_WHITE, keyboardButtonLabels[i], 1);
    keyboardButtons[i].drawButton();
  }

  keyboardOpen = true;

  appBottom = NUMPAD_TOP;
  drawToolbar(NUMPAD_TOP);
  Serial.println("keyboard open");
}

void setupTFT() {
  tft.begin();
  yield();
  turnOnLCD();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
}

void drawLogo() {
  tft.setTextSize(4);
  tft.setCursor(70, 120);
  tft.setTextColor(ILI9341_RED);
  tft.println("PH-1");
}

void clearLayout() {
  tft.fillRect(0,INFO_BAR_HEIGHT+TITLE_BAR_HEIGHT,tft.width(),TOOLBAR_TOP-INFO_BAR_HEIGHT-TITLE_BAR_HEIGHT-1, ILI9341_BLACK);
  tft.fillRect(0,INFO_BAR_HEIGHT,tft.width(),TITLE_BAR_HEIGHT,ILI9341_WHITE);
}


void loadView(PH1View *newView) {
  currentView->onExit();
  delete currentView;
  clearLayout();
  newView->initialize(&tft, &fonaSS);
  updateTitleBar(newView->title);
  drawToolbar(TOOLBAR_TOP);
  newView->onEnter();
  newView->needNewViewLoaded = false;
  currentView = newView;

  appBottom = TOOLBAR_TOP;
  numpadOpen = false;
}

void updateDateAndTime() {

  char buffer[23];
  char month[3];
  char day[3];
  char hour[3];
  char minute[3];

  fona.getTime(buffer, 23);
  tft.setCursor(140, 1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(1);

  month[0] = buffer[4];
  month[1] = buffer[5];
  month[2] = '\0';
  day[0] = buffer[7];
  day[1] = buffer[8];
  day[2] = '\0';

  hour[0] = buffer[10];
  hour[1] = buffer[11];
  hour[2] = '\0';
  minute[0] = buffer[13];
  minute[1] = buffer[14];
  minute[2] = '\0';

  tft.print(F(month));
  tft.print(F("/"));
  tft.print(F(day));

  tft.setCursor(210, 1);
  tft.print(F(hour));
  tft.print(F(":"));
  tft.print(F(minute));
}


void updateSignalStrength() {
  uint16_t strength;
  strength = fona.getRSSI();
  tft.setCursor(70, 1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.print("Sig:");
  tft.print(strength);
  tft.print("  ");
}

void updateBatteryPercent() {
  uint16_t percent;
  fona.getBattPercent(&percent);
  if(percent > 100)
    percent = 100;
  tft.setCursor(2, 1);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.print("Bat:");
  tft.print(percent);
  tft.print("%  ");
}





void setup() {
//  delay(3000);
//  while (!Serial);
//  Serial.begin(115200);
  SPI.begin();
  pinMode(SS, OUTPUT);

  setupTFT();
  drawLogo();

  tft.setCursor(2, 200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);


  tft.print("Mounting SD Card...");
  if (!SD.begin(SD_CS)) {
    tft.println("Mount Failed!");
  }
  tft.println("Done.");

  root = SD.open("/");
  root.rewindDirectory();
  while(true) {
     File entry = root.openNextFile();
     if(! entry) break;
     tft.println(entry.name());
     entry.close();
  }


  root = SD.open("ot/ps/117.csv");
  while (root.available()) {
      tft.print((char) root.read());
//      Serial.write(root.read());
    }
  root.close();

//  turnOffLCD();
  tft.println("Communicating with Cellular Hardware...");


//  fona.setTFT(&tft);
//  tft.println("tryingn 115200");
//  fonaSS.begin(115200);
//  fona.begin(fonaSS);

  // send the command to reset the baud rate to 4800
//  fona.setBaudrate(4800);
  // restart with 4800 baud
//  fonaSS.begin(4800);



  fonaSS.begin(2400);
  fona.setTFT(&tft);
//  fona.begin(fonaSS);
  bool booted = false;
  bool success = false;
  while(!booted) {
    success = fona.begin(fonaSS);
    if (! success) {
      tft.println("No Response. Rebooting SIM and trying again.");
      analogWrite(FONA_KEY, 0);
      delay(2000);
      analogWrite(FONA_KEY, 100);
    }
    else {
      booted = true;
    }
  }
  tft.println("Done.");
//  turnOnLCD();

  fona.setAudio(FONA_EXTAUDIO);

  //Request CallerID when incoming call
  fona.println("AT+CLIP=1");

  // Set microphone gain volumes
  fona.println("AT+CMIC=0,10");
  fona.println("AT+CMIC=1,10");
  fona.println("AT+CMIC=2,10");
  fona.println("AT+CMIC=3,10");
//    fona.println("AT+IPREX=2400");
//    fona.println("AT&W");

  updateBatteryPercent();
  updateSignalStrength();
  updateDateAndTime();

  currentView = new HomeView();
  clearLayout();
  updateTitleBar(currentView->title);
  currentView->initialize(&tft, &fonaSS);
  currentView->onEnter();

  tft.drawLine(0,INFO_BAR_HEIGHT,width,INFO_BAR_HEIGHT,ILI9341_WHITE);
  drawToolbar(TOOLBAR_TOP);
  lastActivity = millis();


}

void loop() {

  TSPoint p;

  p = ts.getPoint();

  if(p.x > 0 && p.y > 0 && p.z > 300) {
    // Touch Detected - Scale to screen coordinate space
    p.x = 240 - map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = 320 + map(p.y, TS_MINY, TS_MAXY, 0, tft.height()) * -1;

    if(p.x < tft.width() && p.x > 0 && p.y < tft.height() && p.y > 0) {
      // Valid Touchscreen Point Detected


      if(millis() > acceptNextTouchAt) {
        acceptNextTouchAt = millis() + touchInterval;
        lastActivity = millis();
        validTouchDetected = true;
        noTouchCount = 0;
        PH1View * newView;

        if(state == IncomingCall) {
          // A call is incoming, so handle all touch events in the modal

          if(incomingCallButtons[0].contains(p.x, p.y)) {
            fona.println("ATA");
            PH1View *newView = new CallView(incomingNumber, "Caller Name");
            loadView(newView);
          }
          else if(incomingCallButtons[1].contains(p.x, p.y)) {
            fona.println("AT+CHUP");
            hideIncomingModal();
          }
        }

        else {
          // No incoming call, so handle touch events normally

          if(numpadOpen) {
            for(int i = 0; i < 12; i ++) {
              if(numpadButtons[i].contains(p.x, p.y)) {
                currentView->handleInput(numpadButtonLabels[i]);
              }
            }
          }
          else if(keyboardOpen) {
            for(int i = 0; i < 40; i ++) {
              if(keyboardButtons[i].contains(p.x, p.y)) {
                currentView->handleInput(keyboardButtonLabels[i]);
              }
            }
          }

          if(p.y > INFO_BAR_HEIGHT + TITLE_BAR_HEIGHT && p.y < appBottom) {
            // Touch point was in the App Area - pass it along
            currentView->handleTouch(p);
          }
          else if(p.y > appBottom && p.y < appBottom + 30) {
            if(p.x < 80) {
              currentView->handlePrevButton();
            }
            else if(p.x > 160) {
              currentView->handleNextButton();
            }
            else {
              currentView->newView = new HomeView();
              currentView->needNewViewLoaded = true;
            }
          }
        }
      }
    }
  }


  if(state == IncomingCall && lastRing + 5000 < millis()) {
    hideIncomingModal();
  }


  if(millis() > toolbarUpdateAt && lcdState != 0) {
    updateBatteryPercent();
    updateSignalStrength();
    updateDateAndTime();
    toolbarUpdateAt = millis() + updateInterval;
  }

  if(millis() > lastActivity + dimLCDAfter && lcdState == 1)
    setBrightness(20);

  else if(millis() > lastActivity + offLCDAfter && lcdState == 2)
    turnOffLCD();

  if(validTouchDetected && lcdState != 1)
    turnOnLCD();

  if(!(currentView->needOSNumpad) && numpadOpen) {
    disableNumpad();
  }

  if(!(currentView->needOSKeyboard) && keyboardOpen) {
    disableKeyboard();
  }

  if((currentView->needOSNumpad) && !numpadOpen) {
    enableNumpad();
  }

  if((currentView->needOSKeyboard) && !keyboardOpen) {
    enableKeyboard();
  }


  if(currentView->needNewViewLoaded) {
    loadView(currentView->newView);
  }

//  if (fona.available())
//    Serial.write(fona.read());

  char c;

  while (fona.available()) {
    // we have pending communication, read what's coming
    c = fona.read();
    if (c != -1) { // -1 means error
      if (c == '\n' || c == '\r') {
        parseSerialInput();
      }
      else {
        receivedChars[receivedChars_i] = c;
        receivedChars_i ++;
        receivedChars[receivedChars_i] = '\0';
      }
    }
  }




//  if (Serial.available())
//    fona.write(Serial.read());
//  if (fona.available())
//    Serial.write(fona.read());

   validTouchDetected = false;
}
