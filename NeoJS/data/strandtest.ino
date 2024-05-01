// NeoPixel LED Strip Demo for NeoJS by sfranzyshen
// Modified by Mayank for better readability and error handling

#include <Adafruit_NeoPixel.h>

// Define the LED pin and count
#define LED_PIN     D2
#define LED_COUNT   8

// Create a NeoPixel object with the given LED count and pin
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Function to initialize the LED strip
void setupLedStrip() {
  if (!ledStrip.begin()) {
    Serial.println("Error: LED strip initialization failed!");
    // Infinite loop in case of initialization failure
    while (1) {
    }
  }
  ledStrip.setBrightness(50);
  ledStrip.show();
  Serial.println("LED strip initialized.");
}

// Function to fill the strip with a single color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < ledStrip.numPixels(); i++) {
    ledStrip.setPixelColor(i, color);
    ledStrip.show();
    delay(wait);
  }
}

// Function for theater-style chasing lights
void theaterChase(uint32_t color, int wait) {
  int a = 0;
  while (a < 10) {
    for (int b = 0; b < 3; b++) {
      ledStrip.clear();
      for (int c = b; c < ledStrip.numPixels(); c += 3) {
        ledStrip.setPixelColor(c, color);
      }
      ledStrip.show();
      delay(wait);
    }
    a++;
  }
}

// Function to cycle through all rainbow colors
void rainbow(int wait) {
  long firstPixelHue = 0;
  while (firstPixelHue < 5 * 65536) {
    for (int i = 0; i < ledStrip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / ledStrip.numPixels());
      ledStrip.setPixelColor(i, ledStrip.gamma32(ledStrip.ColorHSV(pixelHue)));
    }
    ledStrip.show();
    delay(wait);
    firstPixelHue += 256;
  }
}

// Function for theater-style chasing rainbow colors
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  while (firstPixelHue < 5 * 65536) {
    for (int a = 0; a < 30; a++) {
      for (int b = 0; b < 3; b++) {
        ledStrip.clear();
        for (int c = b; c < ledStrip.numPixels(); c += 3) {
          int hue = firstPixelHue + c * 65536L / ledStrip.numPixels();
          uint32_t color = ledStrip.gamma32(ledStrip.ColorHSV(hue));
          ledStrip.setPixelColor(c, color);
        }
        ledStrip.show();
        delay(wait);
        firstPixelHue += 65536 / 90;
      }
    }
  }
}

// Main setup function
void setup() {
  Serial.begin(115200);
  setupLedStrip();
  Serial.println("strandtest ... start");
}

// Main loop function
void loop() {
  // Wipe the strip with different colors
  colorWipe(ledStrip.Color(255, 0, 0), 50); // Red
  colorWipe(ledStrip.Color(0, 255, 0), 50); // Green
  colorWipe(ledStrip.Color(0, 0, 255), 50); // Blue

  // Perform theater-style chasing lights with different colors
  theaterChase(ledStrip.Color(127, 127, 127), 50); // White
  theaterChase(ledStrip.Color(127, 0, 0), 50); // Red
  theaterChase(ledStrip.Color(0, 0, 127), 50); // Blue

  // Cycle through all rainbow colors
  rainbow(10);

  // Perform theater-style chasing rainbow colors
  theaterChaseRainbow(50);

  // Print a message to the serial monitor
  Serial.println("strandtest ... loop");
}
