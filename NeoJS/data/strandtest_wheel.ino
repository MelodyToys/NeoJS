// NeoJS Demo ~ sfranzyshen
// strandtest_wheel.ino in Arduino C++

#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library

#define LED_PIN   D2   // Define the LED pin as D2
#define LED_COUNT 8    // Define the number of LEDs in the strip as 8

Adafruit_NeoPixel Pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Initialize the NeoPixel strip with the defined pin and number of LEDs

// colorWipe()
// Input: r - Red component of the color (0-255)
//        g - Green component of the color (0-255)
//        b - Blue component of the color (0-255)
//        wait - Delay between each LED update (in milliseconds)
// Function: Wipes the color across the NeoPixel strip
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  uint16_t i = 0;
  
  while(i < Pixel.numPixels()) { // Loop through each LED in the strip
    Pixel.setPixelColor(i, r, g, b); // Set the color of the current LED
    Pixel.show(); // Update the NeoPixel strip
    delay(wait); // Wait for the specified delay
	i++; // Move to the next LED
  }
}

// theaterChase()
// Input: r - Red component of the color (0-255)
//        g - Green component of the color (0-255)
//        b - Blue component of the color (0-255)
//        wait - Delay between each update (in milliseconds)
// Function: Displays a chasing light pattern on the NeoPixel strip
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
// Input: wait - Delay between each update (in milliseconds)
// Function: Displays a rainbow pattern on the NeoPixel strip
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
// Input: wait - Delay between each update (in milliseconds)
// Function: Displays a rainbow pattern that cycles through the colors
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
// Input: wait - Delay between each update (in milliseconds)
// Function: Displays a chasing rainbow pattern on the NeoPixel strip
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
// Input: Pos - Position on the color wheel (0-255)
// Output: Red component of the color
// Function: Generates the Red component of a color based on the position on the color wheel
int WheelR(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

// WheelG()
// Input: Pos - Position on the color wheel (0-255)
// Output: Green component of the color
// Function: Generates the Green component of a color based on the position on the color wheel
int WheelG(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

// WheelB()
// Input: Pos - Position on the color wheel (0-255)
// Output: Blue component of the color
// Function: Generates the Blue component of a color based on the position on the color wheel
int WheelB(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}

// setup()
// Function: Initializes the NeoPixel strip and sets the brightness
void setup() {
  Serial.begin(115200); // Initialize serial communication
  Pixel.begin(); // Initialize the NeoPixel strip
  Pixel.setBrightness(50); // Set the brightness of the NeoPixel strip
  Pixel.show(); // Update the NeoPixel strip
  Serial.println("\nstrandtest_wheel ... start"); // Print a message to the serial monitor
}

// loop()
// Function: Displays various light patterns on the NeoPixel strip
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
  Serial.println("strandtest_wheel ... loop"); // Print a message to the serial monitor
}
