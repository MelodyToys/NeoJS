// NeoJS Demo ~ sfranzyshen
// strandtest_nodelay.ino in Arduino C++

#include <Adafruit_NeoPixel.h>
#define LED_PIN   D2
#define LED_COUNT 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long patternPrevious = 0;             // Previous Pattern Millis
int           patternCurrent = 0;              // Current Pattern Number
int           patternInterval = 5500;          // Pattern Interval (ms)
unsigned long pixelPrevious = 0;               // Previous Pixel Millis
uint8_t       pixelInterval = 50;              // Pixel Interval (ms)
int           pixelQueue = 0;                  // Pixel Queue
int           pixelCycle = 0;                  // Pixel Cycle
uint16_t      pixelCurrent = 0;                // Current Pixel Number
uint16_t      pixelNumber = Pixel.numPixels(); // Number of Pixels

// colorWipe()
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  if(pixelInterval != wait) pixelInterval = wait;
  Pixel.setPixelColor(pixelCurrent, r, g, b);
  Pixel.show();
  pixelCurrent++;
  if(pixelCurrent >= pixelNumber) {
    pixelCurrent = 0;
    Pixel.clear();
  }
}

// rainbow()
void rainbow(uint8_t wait) {
  if(pixelInterval != wait) pixelInterval = wait;
  uint16_t i = 0;
  int p = 0;
  while(i < pixelNumber) {
    p = (i + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    i++;
  }
  Pixel.show();
  pixelCycle++;
  if(pixelCycle >= 256) pixelCycle = 0;
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
  if(pixelInterval != wait) pixelInterval = wait;
  uint16_t i = 0;
  int p = 0;
  while( i < pixelNumber) {
    p = ((i * 256 / pixelNumber) + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    i++;
  }
  Pixel.show();
  pixelCycle++;
  if(pixelCycle >= 256 * 5) pixelCycle = 0;
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  if(pixelInterval != wait) pixelInterval = wait;
  int i = 0;
  while(i < pixelNumber) {
    Pixel.setPixelColor(i + pixelQueue, r, g, b);
    i = i + 3;
  }
  Pixel.show();
  i = 0;
  while(i < pixelNumber) {
    Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
    i = i + 3;
  }
  pixelQueue++;
  if(pixelQueue >= 3) pixelQueue = 0;
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  if(pixelInterval != wait) pixelInterval = wait;
  int i = 0;
  int p = 0;
  while(i < pixelNumber) {
    p = (i + pixelCycle) % 255;
    Pixel.setPixelColor(i + pixelQueue, WheelR(p), WheelG(p), WheelB(p));
    i = i + 3;
  }
  Pixel.show();
  i = 0;
  while( i < pixelNumber) {
    Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
    i = i + 3;
  }      
  pixelQueue++;
  pixelCycle++;
  if(pixelQueue >= 3) pixelQueue = 0;
  if(pixelCycle >= 256) pixelCycle = 0;
}

// WheelR()
int WheelR(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

// WheelG()
int WheelG(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

// WheelB()
int WheelB(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}
// setup()
void setup() {
  Serial.begin(115200);
  Pixel.begin();
  Pixel.setBrightness(50);
  Pixel.show();
  Serial.println("\nstrandtest_nodelay ... start");
}

// loop()
void loop() {
  unsigned long currentMillis = millis();
  if((currentMillis - patternPrevious) >= patternInterval) {
    patternPrevious = currentMillis ;
    patternCurrent++;
    if(patternCurrent >= 8) {
      patternCurrent = 0;
      Serial.println("strandtest_nodelay ... loop");
    }
  }  
  if(currentMillis - pixelPrevious >= pixelInterval) {
    pixelPrevious = currentMillis;
    if(patternCurrent == 8) theaterChaseRainbow(50);
    else if(patternCurrent == 7) rainbowCycle(20);
    else if(patternCurrent == 6) rainbow(20);
    else if(patternCurrent == 5) theaterChase(0, 0, 127, 50);     // Blue
    else if(patternCurrent == 4) theaterChase(127, 0, 0, 50);     // Red
    else if(patternCurrent == 3) theaterChase(127, 127, 127, 50); // White
    else if(patternCurrent == 2) colorWipe(0, 0, 255, 50);        // Blue
    else if(patternCurrent == 1) colorWipe(0, 255, 0, 50);        // Green
    else if(patternCurrent == 0) colorWipe(255, 0, 0, 50);        // Red
  }    
}
