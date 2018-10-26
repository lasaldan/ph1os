/*
 * Daniel Fuller
 * OS for PH1 
 */
 
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "SoftwareSerial.h"
#include "Adafruit_FONA.h"
#include "TouchScreen.h"
#include "PH1Button.h"
#include "PH1View.h"
#include "HomeView.h"


#define TFT_CS   2
#define TFT_DC   3
#define TFT_LITE 4
#define SD_CS    7

#define FONA_RX 13
#define FONA_TX 12
#define FONA_RST 11

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 10   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 310
#define TS_MINY 190
#define TS_MAXX 810
#define TS_MAXY 850

#define BUTTON_X 0
#define BUTTON_Y 12
#define BUTTON_W 120
#define BUTTON_H 80
#define BUTTON_SPACING_X 0
#define BUTTON_SPACING_Y 0
#define BUTTON_TEXTSIZE 1

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

PH1View *currentView;
HomeView homeView;

//char buttonlabels[6][9] = {"Phone", "Text", "Contacts", "Tools", "Books", "Other" };
//PH1Button buttons[6];

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int width = tft.width();
int height = tft.height();
int updateInterval = 10000;
int dimLCDAfter = 25000;
int offLCDAfter = 30000;
int toolbarUpdateAt = millis() + updateInterval;
int lastActivity = millis();

File root;

void setup() {
  SPI.begin();
  turnOnLCD();
  pinMode(SS, OUTPUT);
//  digitalWrite(SS, HIGH);
//  turnOffLCD();

  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextSize(4);
  tft.setCursor(70, 120);
  tft.setTextColor(ILI9341_RED);
  tft.println("PH-1");

  tft.setCursor(2, 200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);

  
//  tft.print("Mounting SD Card...");
//  if (!SD.begin(SD_CS)) {
//    tft.println("Mount Failed!");
//  }
//  tft.println("Done.");
//  
//  root = SD.open("/");
//  root.rewindDirectory();
//  while(true) {
//     File entry = root.openNextFile();
//     if(! entry) break;
//     tft.println(entry.name());
//     entry.close();
//  }


//  root = SD.open("ot/ps/117.csv");
//  while (root.available()) {
//      tft.println(root.read());
////      Serial.write(root.read());
//    }
//  root.close();
  
  tft.println("Communicating with Cellular Hardware...");
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    while (1);
  }
  tft.println("Done.");

  updateBatteryPercent();
  updateSignalStrength();
  updateDateAndTime();

  currentView = &homeView;
  currentView->initialize(&tft);
  currentView->onEnter();

  tft.drawLine(0,12,width,12,ILI9341_WHITE);

}

void loop() {
  
  TSPoint p;

  p = ts.getPoint(); 
  
  if(p.z < 200) 
    p.z = -1;
      
  if (p.z != -1) {
    p.x = 240 - map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = 320 + map(p.y, TS_MINY, TS_MAXY, 0, tft.height()) * -1;
    Serial.print(p.z);
  }
  
  tft.setCursor(0,300);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(1);
    
  if(millis() > toolbarUpdateAt) {
    updateBatteryPercent();
    updateSignalStrength();
    updateDateAndTime();
    toolbarUpdateAt = millis() + updateInterval;
  }  
    
  if(millis() > lastActivity + dimLCDAfter) {
    setBrightness(20);
  }
  
  if(millis() > lastActivity + offLCDAfter) {
    turnOffLCD();
  }
//  if (Serial.available())
//    fona.write(Serial.read());
//  if (fona.available())
//    Serial.write(fona.read());
}

void loadView(PH1View *newView) {
  currentView->onExit();
  newView->onEnter();
}

void updateDateAndTime() {
  
  char buffer[23];
  char month[3];
  char day[3];
  char hour[3];
  char minute[3];
  
  fona.getTime(buffer, 23);
  tft.setCursor(140, 2);
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

  tft.setCursor(210, 2);
  tft.print(F(hour));
  tft.print(F(":"));
  tft.print(F(minute));
}

void updateSignalStrength() {
  uint16_t strength;
  strength = fona.getRSSI();
  tft.setCursor(70, 2);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  
  tft.setTextSize(1);
  tft.print("Sig:");
  tft.print(strength);
  tft.print("  ");
}

void updateBatteryPercent() {
  uint16_t percent;
  fona.getBattPercent(&percent);
  tft.setCursor(2, 2);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  
  tft.setTextSize(1);
  tft.print("Bat:");
  tft.print(percent);
  tft.print("% ");
}

void turnOffLCD() {
  pinMode(TFT_LITE, INPUT);
  pinMode(TFT_LITE, OUTPUT);
  digitalWrite(TFT_LITE, LOW);
}

void turnOnLCD() {
  pinMode(TFT_LITE, OUTPUT);
  digitalWrite(TFT_LITE, HIGH);
}

void setBrightness(int percent) {
  pinMode(TFT_LITE, OUTPUT);
//  analogWrite(TFT_LITE, percent);
}
