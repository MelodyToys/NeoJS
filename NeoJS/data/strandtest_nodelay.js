/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// NeoJS Demo ~ sfranzyshen
// This is a port of strandtest_nodelay.ino to JavaScript (Elk)

let patternPrevious = 0,       // Previous Pattern Millis
    patternCurrent = 0,        // Current Pattern Number
    patternInterval = 5500,    // Pattern Interval (ms)
    pixelPrevious = 0,         // Previous Pixel Millis
    pixelInterval = 45,        // Pixel Interval (ms)
    pixelQueue = 0,            // Pixel Queue
    pixelCycle = 0,            // Pixel Cycle
    pixelCurrent = 0,          // Current Pixel Number
    pixelNumber = Pixel.numPixels(); // Number of Pixels

if (pixelNumber <= 0) {
  console.error("Error: Invalid number of pixels");
  return;
}

// colorWipe()
const colorWipe = (r, g, b, wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  Pixel.setPixelColor(pixelCurrent, r, g, b);
  Pixel.show();
  pixelCurrent = (pixelCurrent + 1) % pixelNumber;
};

// theaterChase()
const theaterChase = (r, g, b, wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i = i + 3) {
    Pixel.setPixelColor(i + pixelQueue, r, g, b);
  }
  Pixel.show();
  for (let i = 0; i < pixelNumber; i = i + 3) {
    Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
  }
  pixelQueue = (pixelQueue + 1) % 3;
};

// rainbow()
const rainbow = (wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i++) {
    let p = (i + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
  pixelCycle = (pixelCycle + 1) % 256;
};

// rainbowCycle()
const rainbowCycle = (wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i++) {
    let p = ((i * 256) / pixelNumber + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
  pixelCycle = (pixelCycle + 1) % (256 * 5);
};

// theaterChaseRainbow()
const theaterChaseRainbow = (wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i = i + 3) {
    let p = (i + pixelCycle) % 255;
    Pixel.setPixelColor(i + pixelQueue, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
  for (let i = 0; i < pixelNumber; i = i + 3) {
    Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
  }
  pixelQueue = (pixelQueue + 1) % 3;
  pixelCycle = (pixelCycle + 1) % 256;
};

// setup()
const setup = () => {
  Serial.println("strandtest_nodelay ... start");
};

// loop()
const loop = () => {
  let currentMillis = millis();

  if (currentMillis - patternPrevious >= patternInterval) {
    patternPrevious = currentMillis;
    patternCurrent++;
    if (patternCurrent >= 9) {
      patternCurrent = 0;
      Serial.println("strandtest_nodelay ... loop");
    }
  }
  if (currentMillis - pixelPrevious >= pixelInterval) {
    pixelPrevious = currentMillis;
    switch (patternCurrent) {
      case 8:
        theaterChaseRainbow(50);
        break;
      case 7:
        rainbowCycle(20);
        break;
      case 6:
        rainbow(20);
        break;
      case 5:
        theaterChase(0, 0, 127, 50); // Blue
        break;
      case 4:
        theaterChase(127, 0, 0, 50); // Red
        break;
      case 3:
        theaterChase(127, 127, 127, 50); // White
        break;
      case 2:
        colorWipe(0, 0, 255, 50); // Blue
        break;
      case 1:
        colorWipe(0, 255, 0, 50); // Green
        break;
      case 0:
        colorWipe(255, 0, 0, 50); // Red
        break;
    }
  }
};
