// NeoJS Demo ~ sfranzyshen
// strandtest_nodelay_improved.ino in Arduino C++

#include <Adafruit_NeoPixel.h>
#define LED_PIN   D2
#define LED_COUNT 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const unsigned long patternInterval = 5500;          // Pattern Interval (ms)
const uint8_t pixelInterval = 50;              // Pixel Interval (ms)

// colorWipe()
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  Pixel.setBrightness(50);
  for (int i = 0; i < Pixel.numPixels(); i++) {
    Pixel.setPixelColor(i, r, g, b);
    Pixel.show();
    delay(wait);
  }
  Pixel.clear();
}

// rainbow()
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < Pixel.numPixels(); i++) {
      Pixel.setPixelColor(i, WheelR(i + j), WheelG(i + j), WheelB(i + j));
    }
    Pixel.show();
    delay(wait);
  }
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
  int j;
  for (j = 0; j < 256 * 5; j++) {
    for (int i = 0; i < Pixel.numPixels(); i++) {
      Pixel.setPixelColor(i, WheelR(((i * 256 / Pixel.numPixels()) + j) & 255), WheelG(((i * 256 / Pixel.numPixels()) + j) & 255), WheelB(((i * 256 / Pixel.numPixels()) + j) & 255));
    }
    Pixel.show();
    delay(wait);
  }
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int i;
  for (i = 0; i < 10; i++) {
    for (int j = 0; j < Pixel.numPixels(); j = j + 3) {
      Pixel.setPixelColor(j + i % 3, r, g, b);
    }
    Pixel.show();
    delay(wait);
    for (int j = 0; j < Pixel.numPixels(); j = j + 3) {
      Pixel.setPixelColor(j + i % 3, 0, 0, 0);
    }
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  int i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < 10; i++) {
      for (int k = 0; k < Pixel.numPixels(); k = k + 3) {
        Pixel.setPixelColor(k + i % 3, WheelR((i + j) % 255), WheelG((i + j) % 255), WheelB((i + j) % 255));
      }
      Pixel.show();
      delay(wait);
      for (int k = 0; k < Pixel.numPixels(); k = k + 3) {
        Pixel.setPixelColor(k + i % 3, 0, 0, 0);
      }
    }
  }
}

// WheelR()
uint8_t WheelR(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return 255 - WheelPos * 3;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return WheelPos * 3;
  }
  return 0;
}

// WheelG()
uint8_t WheelG(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return 0;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return WheelPos * 3;
  }
  return 255 - WheelPos * 3;
}

// WheelB()
uint8_t WheelB(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return WheelPos * 3;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return 255 - WheelPos * 3;
  }
  return 0;
}

// setup()
void setup() {
  Pixel.begin();
  Serial.begin(115200);
  Serial.println("\nstrandtest_nodelay_improved ... start");
}

// loop()
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - patternPrevious >= patternInterval) {
    patternPrevious = currentMillis;
    patternCurrent++;
    if (patternCurrent >= 8) {
      patternCurrent = 0;
      Serial.println("strandtest_nodelay_improved ... loop");
    }
  }
  switch (patternCurrent) {
    case 0:
      colorWipe(255, 0, 0, pixelInterval);
      break;
    case 1:
      colorWipe(0, 255, 0, pixelInterval);
      break;
    case 2:
      colorWipe(0, 0, 255, pixelInterval);
      break;
    case 3:
      theaterChase(127, 127, 127, pixelInterval);
      break;
    case 4:
      theaterChase(127, 0, 0, pixelInterval);
      break;
    case 5:
      theaterChase(0, 127, 0, pixelInterval);
      break;
    case 6:
      rainbow(pixelInterval);
      break;
    case 7:
      rainbowCycle(pixelInterval);
      break;
    case 8:
      theaterChaseRainbow(pixelInterval);
      break;
  }
}
