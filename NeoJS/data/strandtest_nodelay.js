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

// colorWipe()
let colorWipe = function(r, g, b, wait) {
    if(pixelInterval !== wait)
		pixelInterval = wait;
    Pixel.setPixelColor(pixelCurrent, r, g, b);
    Pixel.show();
    pixelCurrent++;
    if(pixelCurrent >= pixelNumber) {
        pixelCurrent = 0;
        Pixel.clear();
    }
};

// theaterChase()
let theaterChase = function(r, g, b, wait) {
    let i = 0;
	
    if(pixelInterval !== wait)
		pixelInterval = wait;
    while(i < pixelNumber) {
        Pixel.setPixelColor(i + pixelQueue, r, g, b);
        i = i + 3;
    }
    Pixel.show();
    i = 0;
    while(i < pixelNumber) {
        Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
        i = i + 3;
    }
    pixelQueue++;
    if(pixelQueue >= 3) pixelQueue = 0;
};

// rainbow()
let rainbow = function(wait) {
    let i = 0, p;
	
    if(pixelInterval !== wait)
		pixelInterval = wait;
    while(i < pixelNumber) {
        p = (i + pixelCycle) & 255;
        Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
        i++;
    }
    Pixel.show();
    pixelCycle++;
    if(pixelCycle >= 256) pixelCycle = 0;
};

// rainbowCycle()
let rainbowCycle = function(wait) {
    let i = 0, p;
	
    if(pixelInterval !== wait)
		pixelInterval = wait;
    while(i < pixelNumber) {
        p = ((i * 256 / pixelNumber) + pixelCycle) & 255;
        Pixel.setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
        i++;
    }
    Pixel.show();
    pixelCycle++;
    if(pixelCycle >= 256 * 5) pixelCycle = 0;
};

// theaterChaseRainbow()
let theaterChaseRainbow = function(wait) {
	let i = 0, p;
	
    if(pixelInterval !== wait)
		pixelInterval = wait;
    while(i < pixelNumber) {
        p = (i + pixelCycle) % 255;
        Pixel.setPixelColor(i + pixelQueue, WheelR(p), WheelG(p), WheelB(p));
        i = i + 3;
    }
    Pixel.show();
    i = 0;
    while(i < pixelNumber) {
        Pixel.setPixelColor(i + pixelQueue, 0, 0, 0);
        i = i + 3;
    }
    pixelQueue++;
    pixelCycle++;
    if(pixelQueue >= 3) pixelQueue = 0;
    if(pixelCycle >= 256) pixelCycle = 0;
};

// setup()
let setup = function() {
  Serial.println("strandtest_nodelay ... start");
};

// loop()
let loop = function() {
    let currentMillis = millis();
	
    if(currentMillis - patternPrevious >= patternInterval) {
        patternPrevious = currentMillis;
        patternCurrent++;
        if(patternCurrent >= 9) {
			patternCurrent = 0;
			Serial.println("strandtest_nodelay ... loop");
		}
    }
    if(currentMillis - pixelPrevious >= pixelInterval) {
        pixelPrevious = currentMillis;
        if(patternCurrent === 8) theaterChaseRainbow(50);
        else if(patternCurrent === 7) rainbowCycle(20);
        else if(patternCurrent === 6) rainbow(20);
        else if(patternCurrent === 5) theaterChase(0, 0, 127, 50);    // Blue
        else if(patternCurrent === 4) theaterChase(127, 0, 0, 50);    // Red
        else if(patternCurrent === 3) theaterChase(127, 127, 127, 50);// White
        else if(patternCurrent === 2) colorWipe(0, 0, 255, 50);       // Blue
        else if(patternCurrent === 1) colorWipe(0, 255, 0, 50);       // Green
        else if(patternCurrent === 0) colorWipe(255, 0, 0, 50);       // Red
    }
};
