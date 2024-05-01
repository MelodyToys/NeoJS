/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

const COLOR_WIPE_DELAY = 50;
const THEATER_CHASE_DELAY = 50;
const RAINBOW_DELAY = 10;
const THEATER_CHASE_RAINBOW_DELAY = 50;

function colorWipe(color, wait) {
  for (let i = 0; i < Pixel.numPixels(); i++) {
    Pixel.setPixelColor32(i, color);
    Pixel.show();
    delay(wait);
  }
}

function theaterChase(color, wait) {
  for (let a = 0; a < 10; a++) {
    for (let b = 0; b < 3; b++) {
      Pixel.clear();
      for (let c = b; c < Pixel.numPixels(); c += 3) {
        Pixel.setPixelColor32(c, color);
      }
      Pixel.show();
      delay(wait);
    }
  }
}

function rainbow(wait) {
  let firstPixelHue = 0;
  for (let i = 0; i < Pixel.numPixels(); i++) {
    let pixelHue = firstPixelHue + (i * 65536 / Pixel.numPixels());
    Pixel.setPixelColor32(i, Pixel.gamma32(Pixel.ColorHSV(pixelHue)));
  }
  Pixel.show();
  delay(wait);
  firstPixelHue += 256;
}

function theaterChaseRainbow(wait) {
  let firstPixelHue = 0;
  for (let a = 0; a < 30; a++) {
    for (let b = 0; b < 3; b++) {
      Pixel.clear();
      for (let c = b; c < Pixel.numPixels(); c += 3) {
        let hue = firstPixelHue + c * 65536 / Pixel.numPixels();
        let color = Pixel.gamma32(Pixel.ColorHSV(hue));
        Pixel.setPixelColor32(c, color);
      }
      Pixel.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}

function setup() {
  Serial.println("strandtest ... start");
}

function loop() {
  colorWipe(Pixel.Color(255, 0, 0), COLOR_WIPE_DELAY); // Red
  colorWipe(Pixel.Color(0, 255, 0), COLOR_WIPE_DELAY); // Green
  colorWipe(Pixel.Color(0, 0, 255), COLOR_WIPE_DELAY); // Blue

  theaterChase(Pixel.Color(127, 127, 127), THEATER_CHASE_DELAY); // White
  theaterChase(Pixel.Color(127, 0, 0), THEATER_CHASE_DELAY); // Red
  theaterChase(Pixel.Color(0, 0, 127), THEATER_CHASE_DELAY); // Blue

  rainbow(RAINBOW_DELAY);
  theaterChaseRainbow(THEATER_CHASE_RAINBOW_DELAY);

  Serial.println("strandtest ... loop");
}
