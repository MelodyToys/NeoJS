/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// NeoJS Demo ~ sfranzyshen
// This is a port of strandtest_nodelay.ino to JavaScript (Elk)

// Variables
// ---------

// patternPrevious: Millis (ms) of the previous pattern change
let patternPrevious = 0;      

// patternCurrent: Current pattern number
let patternCurrent = 0;       

// patternInterval: Pattern interval (ms)
let patternInterval = 5500;   

// pixelPrevious: Millis (ms) of the previous pixel change
let pixelPrevious = 0;        

// pixelInterval: Pixel interval (ms)
let pixelInterval = 45;       

// pixelQueue: Pixel queue
let pixelQueue = 0;           

// pixelCycle: Pixel cycle
let pixelCycle = 0;           

// pixelCurrent: Current pixel number
let pixelCurrent = 0;         

// pixelNumber: Number of pixels
let pixelNumber = Pixel.numPixels(); 

// Function: colorWipe()
// Parameters: r, g, b (red, green, blue values), wait (interval in ms)
// Description: Wipes the color across the NeoPixel strip
const colorWipe = (r, g, b, wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  Pixel.setPixelColor(pixelCurrent, r, g, b);
  Pixel.show();
  pixelCurrent = (pixelCurrent + 1) % pixelNumber;
};

// Function: theaterChase()
// Parameters: r, g, b (red, green, blue values), wait (interval in ms)
// Description: Chases the specified color along the NeoPixel strip
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

// Function: rainbow()
// Parameters: wait (interval in ms)
// Description: Displays a rainbow pattern on the NeoPixel strip
const rainbow = (wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i++) {
    let p = (i + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
  pixelCycle = (pixelCycle + 1) % 256;
};

// Function: rainbowCycle()
// Parameters: wait (interval in ms)
// Description: Displays a rainbow cycle pattern on the NeoPixel strip
const rainbowCycle = (wait) => {
  if (pixelInterval !== wait) pixelInterval = wait;
  for (let i = 0; i < pixelNumber; i++) {
    let p = ((i * 256) / pixelNumber + pixelCycle) & 255;
    Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
  }
  Pixel.show();
  pixelCycle = (pixelCycle + 1) % (256 * 5);
};

// Function: theaterChaseRainbow()
// Parameters: wait (interval in ms)
// Description: Chases a rainbow pattern along the NeoPixel strip
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

// Function: setup()
// Description: Initializes the NeoPixel library and sets up the serial communication
const setup = () => {
  Serial.println("strandtest_nodelay ... start");
};

// Function: loop()
// Description: Main loop that runs the different patterns based on the patternCurrent variable
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
