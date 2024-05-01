// NeoPixel LED Wheel Demo ~ sfranzyshen
// Rewritten and improved by NeoAI

#include <Adafruit_NeoPixel.h>

#define LED_PIN   2   // D2 on Particle devices
#define LED_COUNT 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Pixel.begin();
  Pixel.setBrightness(50);
  Pixel.show();
  Serial.println("\nNeoPixel LED Wheel Demo ... start");
}

void loop() {
  colorWipe(Pixel, 255,   0,   0, 50); // Red
  colorWipe(Pixel,   0, 255,   0, 50); // Green
  colorWipe(Pixel,   0,   0, 255, 50); // Blue

  theaterChase(Pixel, 127, 127, 127, 50); // White
  theaterChase(Pixel, 127,   0,   0, 50); // Red
  theaterChase(Pixel,   0,   0, 127, 50); // Blue

  rainbow(Pixel, 20);
  rainbowCycle(Pixel, 20);
  theaterChaseRainbow(Pixel, 50);

  Serial.println("NeoPixel LED Wheel Demo ... loop");
}

// colorWipe()
void colorWipe(Adafruit_NeoPixel &strip, uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  uint16_t i;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b);
    strip.show();
    delay(wait);
  }
}

// theaterChase()
void theaterChase(Adafruit_NeoPixel &strip, uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int j, q;
  uint16_t i;
  for (j = 0; j < 10; j++) {
    for (q = 0; q < 3; q++) {
      i = q;
      while (i < strip.numPixels()) {
        strip.setPixelColor(i, r, g, b);
        i += 3;
      }
      strip.show();
      delay(wait);
      i = q;
      while (i < strip.numPixels()) {
        strip.setPixelColor(i, 0, 0, 0);
        i += 3;
      }
    }
  }
}

// rainbow()
void rainbow(Adafruit_NeoPixel &strip, uint8_t wait) {
  uint16_t j, i;
  int p;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      p = (i + j) & 255;
      strip.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    }
    strip.show();
    delay(wait);
  }
}

// rainbowCycle()
void rainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait) {
  uint16_t j, i;
  int p;
  for (j = 0; j < 256 * 5; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      p = (i * 256 / strip.numPixels() + j) & 255;
      strip.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    }
    strip.show();
    delay(wait);
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(Adafruit_NeoPixel &strip, uint8_t wait) {
  int j, q, p;
  uint16_t i;
  for (j = 0; j < 256; j++) {
    for (q = 0; q < 3; q++) {
      i = q;
      while (i < strip.numPixels()) {
        p = (i + j) % 255;
        strip.setPixelColor(i + q, WheelR(p), WheelG(p), WheelB(p));
        i += 3;
      }
      strip.show();
      delay(wait);
      i = q;
      while (i < strip.numPixels()) {
        strip.setPixelColor(i + q, 0, 0, 0);
        i += 3;
      }
    }
  }
}

// WheelR()
int WheelR(int Pos) {
  Pos = 255 - Pos;
  if (Pos < 85) { return 255 - Pos * 3; }
  if (Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

// WheelG()
int WheelG(int Pos) {
  Pos = 255 - Pos;
  if (Pos < 85) { return 0; }
  if (Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

// WheelB()
int WheelB(int Pos) {
  Pos = 255 - Pos;
  if (Pos < 85) { return Pos * 3; }
  if (Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}
