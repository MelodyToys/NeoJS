// NeoJS Demo ~ sfranzyshen
// strandtest_nodelay.ino in Arduino C++

#include <Adafruit_NeoPixel.h>

#define PIN   D2
#define NUM   8

Adafruit_NeoPixel pixs = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

unsigned long pixPrev = 0;              // Previous Pixel Millis
unsigned long patPrev = 0;              // Previous Pattern Millis
int           patCurr = 0;              // Current Pattern Number
int           patInte = 5500;           // Pattern Interval (ms)
int           pixInte = 55;             // Pixel Interval (ms)
int           pixQueu = 0;              // Pixel Queue
int           pixCycl = 0;              // Pixel Cycle
uint16_t      pixCurr = 0;              // Current Pixel Number
uint16_t      pixNum = pixs.numPixels();// Number of Pixels

// setup()
void setup() {
  pixs.begin();
  pixs.show();
  pixs.setBrightness(50);
}

// loop()
void loop() {
  unsigned long curMill = millis();
  if((curMill - patPrev) >= patInte) {
    patPrev = curMill;
    patCurr++;
    if(patCurr >= 8) patCurr = 0;
  }  
  if(curMill - pixPrev >= pixInte) {
    pixPrev = curMill;
    if(patCurr == 8) thtrChsRnbw();
    else if(patCurr == 7) rnbwCyc();
    else if(patCurr == 6) rnbw();
    else if(patCurr == 5) thtrChs(0, 0, 127);    // Blue
    else if(patCurr == 4) thtrChs(127, 0, 0);    // Red
    else if(patCurr == 3) thtrChs(127, 127, 127);// White
    else if(patCurr == 2) clrWp(0, 0, 255);      // Blue
    else if(patCurr == 1) clrWp(0, 255, 0);      // Green
    else if(patCurr == 0) clrWp(255, 0, 0);      // Red
  }    
}

// colorWipe(r , g, b)
void clrWp(uint8_t r, uint8_t g, uint8_t b){
  pixs.setPixelColor(pixCurr, r, g, b);
  pixs.show();
  pixCurr++;
  if(pixCurr >= pixNum) {
    pixCurr = 0;
    pixs.clear();
  }
}

// rainbow()
void rnbw() {
  uint16_t i = 0;
  int p = 0;
  while(i < pixNum) {
    p = (i + pixCycl) & 255;
    pixs.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    i++;
  }
  pixs.show();
  pixCycl++;
  if(pixCycl >= 256) pixCycl = 0;
}

// rainbowCycle()
void rnbwCyc() {
  uint16_t i = 0;
  int p = 0;
  while( i < pixNum) {
    p = ((i * 256 / pixNum) + pixCycl) & 255;
    pixs.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    i++;
  }
  pixs.show();
  pixCycl++;
  if(pixCycl >= 256 * 5) pixCycl = 0;
}

// theaterChase(r, g, b)
void thtrChs(uint8_t r, uint8_t g, uint8_t b) {
  int i = 0;
  while(i < pixNum) {
    pixs.setPixelColor(i + pixQueu, r, g, b);
    i = i + 3;
  }
  pixs.show();
  i = 0;
  while(i < pixNum) {
    pixs.setPixelColor(i + pixQueu, 0, 0, 0);
    i = i + 3;
  }
  pixQueu++;
  if(pixQueu >= 3) pixQueu = 0;
}

// theaterChaseRainbow()
void thtrChsRnbw() {
  int i = 0;
  int p = 0;
  while(i < pixNum) {
    p = (i + pixCycl) % 255;
    pixs.setPixelColor(i + pixQueu, WheelR(p), WheelG(p), WheelB(p));
    i = i + 3;
  }
  pixs.show();
  i = 0;
  while( i < pixNum) {
    pixs.setPixelColor(i + pixQueu, 0, 0, 0);
    i = i + 3;
  }      
  pixQueu++;
  pixCycl++;
  if(pixQueu >= 3) pixQueu = 0;
  if(pixCycl >= 256) pixCycl = 0;
}

// WheelR(Pos)
int WheelR(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

// WheelG(Pos)
int WheelG(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

// WheelB(Pos)
int WheelB(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}
