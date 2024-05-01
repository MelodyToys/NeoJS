/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// Utility functions

/**
 * Wipes the color across the entire strip, one pixel at a time.
 *
 * @param {number} r - The red color component (0-255).
 * @param {number} g - The green color component (0-255).
 * @param {number} b - The blue color component (0-255).
 * @param {number} wait - The time to wait between each pixel update (in milliseconds).
 */
const colorWipe = (r, g, b, wait) => {
  for (let i = 0; i < Pixel.numPixels(); i++) {
    Pixel.setPixelColor(i, r, g, b);
    Pixel.show();
    delay(wait);
  }
};

/**
 * Performs a theater-style chase animation across the strip.
 *
 * @param {number} r - The red color component (0-255).
 * @param {number} g - The green color component (0-255).
 * @param {number} b - The blue color component (0-255).
 * @param {number} wait - The time to wait between each pixel update (in milliseconds).
 */
const theaterChase = (r, g, b, wait) => {
  for (let j = 0; j < 10; j++) {
    for (let q = 0; q < 3; q++) {
      for (let i = 0; i < Pixel.numPixels(); i += 3) {
        Pixel.setPixelColor(i + q, r, g, b);
        Pixel.show();
        delay(wait);
        Pixel.setPixelColor(i + q, 0, 0, 0);
      }
    }
  }
};

/**
 * Displays a rainbow cycle animation across the strip.
 *
 * @param {number} wait - The time to wait between each pixel update (in milliseconds).
 */
const rainbow = (wait) => {
  for (let j = 0; j < 256; j++) {
    for (let i = 0; i < Pixel.numPixels(); i++) {
      const p = ((i * 256 / Pixel.numPixels()) + j) & 255;
      Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    }
    Pixel.show();
    delay(wait);
  }
};

/**
 * Displays a rainbow cycle animation across the strip, with continuous color changes.
 *
 * @param {number} wait - The time to wait between each pixel update (in milliseconds).
 */
const rainbowCycle = (wait) => {
  for (let j = 0; j < 256 * 5; j++) {
    for (let i = 0; i < Pixel.numPixels(); i++) {
      const p = ((i * 256 / Pixel.numPixels()) + j) & 255;
      Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
    }
    Pixel.show();
    delay(wait);
  }
};

/**
 * Performs a theater-style chase animation across the strip, with rainbow color changes.
 *
 * @param {number} wait - The time to wait between each pixel update (in milliseconds).
 */
const theaterChaseRainbow = (wait) => {
  for (let j = 0; j < 256; j++) {
    for (let q = 0; q < 3; q++) {
      for (let i = 0; i < Pixel.numPixels(); i += 3) {
        const p = (i + j) % 255;
        Pixel.setPixelColor(i + q, WheelR(p), WheelG(p), WheelB(p));
        Pixel.show();
        delay(wait);
        Pixel.setPixelColor(i + q, 0, 0, 0);
      }
    }
  }
};

// Main functions

/**
 * Initializes the required settings and resources.
 */
const setup = () => {
  Serial.println("strandtest_wheel ... start");
};

/**
 * The main loop function that contains the sequence of animations.
 */
const loop = () => {
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
};

