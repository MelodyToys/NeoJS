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
  for (uint16_t i = 0; i < Pixel.numPixels(); i++) {
    Pixel.setPixelColor(i, r, g, b);
    Pixel.show();
    delay(wait);
  }
  Pixel.clear();
}

// rainbow()
void rainbow(uint8_t wait) {
  uint16_t i, p;
  for (i = 0; i < Pixel.numPixels(); i++) {
    p = (i * 256 / Pixel.numPixels()) + millis() / wait;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < Pixel.numPixels(); i++) {
      Pixel.setPixelColor(i, WheelR((i + j) % 255), WheelG((i + j) % 255), WheelB((i + j) % 255));
    }
    Pixel.show();
    delay(wait);
  }
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < Pixel.numPixels(); j = j + 3) {
      Pixel.setPixelColor(j + i % 3, r, g, b); //turn every third pixel on
    }
    Pixel.show();
    delay(wait);
    for (int j = 0; j < Pixel.numPixels(); j = j + 3) {
      Pixel.setPixelColor(j + i % 3, 0, 0, 0); //turn every third pixel off
    }
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {    
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < Pixel.numPixels(); i = i + 3) {
        Pixel.setPixelColor(i + q, WheelR((i + j) % 255), WheelG((i + j) % 255), WheelB((i + j) % 255)); //turn every third pixel on
      }
      Pixel.show();
      delay(wait);
      
      for (int i = 0; i < Pixel.numPixels(); i = i + 3) {
        Pixel.setPixelColor(i + q, 0, 0, 0); //turn every third pixel off
      }
    }
  }
}

// Wheel()
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return Pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return Pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// setup()
void setup() {
  Serial.begin(115200);
  Pixel.begin();
  Pixel.setBrightness(50);
  Pixel.show();
  Serial.println("\nstrandtest_nodelay_improved ... start");
}

// loop()
void loop() {
  if (millis() - patternPrevious >= patternInterval) {
    patternPrevious = millis();
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
      theaterChase(0, 0, 127, pixelInterval);
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
