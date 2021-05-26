// NeoJS Demo ~ sfranzyshen
// strandtest.ino in Arduino C++

#include <Adafruit_NeoPixel.h>
#define LED_PIN   D2
#define LED_COUNT 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// colorWipe()
void colorWipe(uint32_t color, int wait) {
  int i = 0;
  
  while(i < Pixel.numPixels()) {
    Pixel.setPixelColor(i, color);
    Pixel.show();
    delay(wait);
	i++;
  }
}

// theaterChase()
void theaterChase(uint32_t color, int wait) {
  int a = 0, b, c;
  
  while(a < 10) {
	b = 0;
    while(b < 3) {
      Pixel.clear();
	  c = b;
      while(c < Pixel.numPixels()) {
        Pixel.setPixelColor(c, color);
		c += 3;
      }
      Pixel.show();
      delay(wait);
	  b++;
    }
	a++;
  }
}

// rainbow()
void rainbow(int wait) {
  long firstPixelHue = 0;
  int i, pixelHue;
  
  while(firstPixelHue < 5 * 65536) {
	i = 0;
    while(i < Pixel.numPixels()) {
      pixelHue = firstPixelHue + (i * 65536L / Pixel.numPixels());
      Pixel.setPixelColor(i, Pixel.gamma32(Pixel.ColorHSV(pixelHue)));
	  i++;
    }
    Pixel.show();
    delay(wait);
	firstPixelHue += 256;
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  int a = 0, b, c, hue;
  uint32_t color;
  
  while(a < 30) {
	b = 0;
    while(b < 3) {
      Pixel.clear();
	  c = b;
      while(c < Pixel.numPixels()) {
        hue = firstPixelHue + c * 65536L / Pixel.numPixels();
        color = Pixel.gamma32(Pixel.ColorHSV(hue));
        Pixel.setPixelColor(c, color);
		c += 3;
      }
      Pixel.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
	  b++;
    }
	a++;
  }
}

// setup()
void setup() {
  Serial.begin(115200);
  Pixel.begin();
  Pixel.setBrightness(50);
  Pixel.show();
  Serial.println("\nstrandtest ... start");
}

// loop()
void loop() {
  colorWipe(Pixel.Color(255, 0, 0), 50); // Red
  colorWipe(Pixel.Color(0, 255, 0), 50); // Green
  colorWipe(Pixel.Color(0, 0, 255), 50); // Blue

  theaterChase(Pixel.Color(127, 127, 127), 50); // White
  theaterChase(Pixel.Color(127, 0, 0), 50); // Red
  theaterChase(Pixel.Color( 0, 0, 127), 50); // Blue

  rainbow(10);
  theaterChaseRainbow(50);
  Serial.println("strandtest ... loop");
}

