// NeoJS Demo ~ sfranzyshen
// strandtest_wheel.ino in Arduino C++

#include <Adafruit_NeoPixel.h>
#define LED_PIN   D2
#define LED_COUNT 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// colorWipe()
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  uint16_t i = 0;
  
  while(i < Pixel.numPixels()) {
    Pixel.setPixelColor(i, r, g, b);
    Pixel.show();
    delay(wait);
	i++;
  }
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int j = 0, q;
  uint16_t i = 0;
  
  while(j < 10) {  //do 10 cycles of chasing
    q = 0;
    while(q < 3) {
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i+q, r, g, b);    //turn every third pixel on
		i = i + 3;
      }
      Pixel.show();
      delay(wait);
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i+q, 0, 0, 0);        //turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
}

// rainbow()
void rainbow(uint8_t wait) {
  uint16_t j = 0, i;
  int p;
  
  while(j < 256) {
	i = 0;
    while(i < Pixel.numPixels()) {
	  p = (i + j) & 255;
      Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
	  i++;
    }
    Pixel.show();
    delay(wait);
	j++;
  }
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
  uint16_t j = 0, i;
  int p;
  
  while(j < 256 * 5) { // 5 cycles of all colors on wheel
    i = 0;
    while(i < Pixel.numPixels()) {
      p = ((i * 256 / Pixel.numPixels()) + j) & 255;
      Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
	  i++;
    }
    Pixel.show();
    delay(wait);
	j++;
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  int j = 0, q, p;
  uint16_t i;
  
  while(j < 256) {     // cycle all 256 colors in the wheel
    q = 0;
    while(q < 3) {
	  i = 0;
      while(i < Pixel.numPixels()) {
		p = (i + j) % 255;
        Pixel.setPixelColor(i + q, WheelR(p), WheelG(p), WheelB(p));    //turn every third pixel on
		i = i + 3;
      }
      Pixel.show();
      delay(wait);
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i+q, 0, 0, 0);        //turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
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
  Serial.println("\nstrandtest_wheel ... start");
}

// loop()
void loop() {
  colorWipe(255, 0, 0, 50); // Red
  colorWipe(0, 255, 0, 50); // Green
  colorWipe(0, 0, 255, 50); // Blue

  theaterChase(127, 127, 127, 50); // White
  theaterChase(127, 0, 0, 50); // Red
  theaterChase(0, 0, 127, 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  Serial.println("strandtest_wheel ... loop");
}
