/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// Define the delay for COLOR_WIPE and THEATER_CHASE effects
const COLOR_WIPE_DELAY = 50;
const THEATER_CHASE_DELAY = 50;

// Define the delay for RAINBOW and THEATER_CHASE_RAINBOW effects
const RAINBOW_DELAY = 10;
const THEATER_CHASE_RAINBOW_DELAY = 50;

// The colorWipe function wipes a single color across the LED strip with a specified delay
function colorWipe(color, wait) {
  // Iterate through each pixel on the LED strip
  for (let i = 0; i < Pixel.numPixels(); i++) {
    // Set the current pixel to the specified color
    Pixel.setPixelColor32(i, color);
    // Refresh the LED strip to show the new color
    Pixel.show();
    // Wait for the specified delay
    delay(wait);
  }
}

// The theaterChase function creates a chase effect with a specified color and delay
function theaterChase(color, wait) {
  // Execute the chase effect 10 times
  for (let a = 0; a < 10; a++) {
    // Execute the chase effect in groups of 3 LEDs
    for (let b = 0; b < 3; b++) {
      // Clear the LED strip
      Pixel.clear();
      // Iterate through the LED strip, lighting up every 3rd LED in the current group
      for (let c = b; c < Pixel.numPixels(); c += 3) {
        // Set the current pixel to the specified color
        Pixel.setPixelColor32(c, color);
      }
      // Refresh the LED strip to show the new pattern
      Pixel.show();
      // Wait for the specified delay
      delay(wait);
    }
  }
}

// The rainbow function generates a rainbow pattern with a specified delay
function rainbow(wait) {
  // Initialize the first pixel's hue value
  let firstPixelHue = 0;
  // Iterate through each pixel on the LED strip
  for (let i = 0; i < Pixel.numPixels(); i++) {
    // Calculate the hue value for the current pixel
    let pixelHue = firstPixelHue + (i * 65536 / Pixel.numPixels());
    // Set the current pixel to the calculated hue value
    Pixel.setPixelColor32(i, Pixel.gamma32(Pixel.ColorHSV(pixelHue)));
  }
  // Refresh the LED strip to show the new pattern
  Pixel.show();
  // Wait for the specified delay
  delay(wait);
  // Increment the first pixel's hue value for the next iteration
  firstPixelHue += 256;
}

// The theaterChaseRainbow function creates a chase effect with a rainbow pattern and a specified delay
function theaterChaseRainbow(wait) {
  // Initialize the first pixel's hue value
  let firstPixelHue = 0;
  // Execute the chase effect 30 times
  for (let a = 0; a < 30; a++) {
    // Execute the chase effect in groups of 3 LEDs
    for (let b = 0; b < 3; b++) {
      // Clear the LED strip
      Pixel.clear();
      // Iterate through the LED strip, lighting up every 3rd LED in the current group with a hue value
      for (let c = b; c < Pixel.numPixels(); c += 3) {
        // Calculate the hue value for the current pixel
        let hue = firstPixelHue + c * 65536 / Pixel.numPixels();
        // Set the current pixel to the calculated hue value
        let color = Pixel.gamma32(Pixel.ColorHSV(hue));
        Pixel.setPixelColor32(c, color);
      }
      // Refresh the LED strip to show the new pattern
      Pixel.show();
      // Wait for the specified delay
      delay(wait);
      // Increment the first pixel's hue value for the next iteration
      firstPixelHue += 65536 / 90;
    }
  }
}

// The setup function initializes the serial communication and prints a message
function setup() {
  Serial.println("strandtest ... start");
}

// The loop function runs the defined lighting patterns repeatedly
function loop() {
  // Run the colorWipe function with red, green, and blue colors
  colorWipe(Pixel.Color(255, 0, 0), COLOR_WIPE_DELAY); // Red
  colorWipe(Pixel.Color(0, 255, 0), COLOR_WIPE_DELAY); // Green
  colorWipe(Pixel.Color(0, 0, 255), COLOR_WIPE_DELAY); // Blue

  // Run the theaterChase function with white, red, and blue colors
  theaterChase(Pixel.Color(127, 127, 127), THEATER_CHASE_DELAY); // White
  theaterChase(Pixel.Color(127, 0, 0), THEATER_CHASE_DELAY); // Red
  theaterChase(Pixel.Color(0, 0, 127), THEATER_CHASE_DELAY); // Blue

  // Run the rainbow function
  rainbow(RAINBOW_DELAY);

  // Run the theaterChaseRainbow function
  theaterChaseRainbow(THEATER_CHASE_RAINBOW_DELAY);

  // Print a message to the serial monitor
  Serial.println("strandtest ... loop");
}

