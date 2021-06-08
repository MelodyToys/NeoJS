/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// NeoJS Demo ~ sfranzyshen
// This is a port of strandtest_wheel.ino to JavaScript (Elk)

// colorWipe()
let colorWipe = function(r, g, b, wait) {
  let i = 0;
  
  while(i < Pixel.numPixels()) {
    Pixel.setPixelColor(i, r, g, b);
    Pixel.show();
    delay(wait);
	i++;
  }
};

// theaterChase()
let theaterChase = function(r, g, b, wait) {
  let j = 0, q = 0, i = 0;
  
  while(j < 10) { // do 10 cycles of chasing
    q = 0;
    while(q < 3) {
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i + q, r, g, b); // turn every third pixel on
		i = i + 3;
      }
      Pixel.show();
      delay(wait);
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i + q, 0, 0, 0); // turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
};

// rainbow()
let rainbow = function(wait) {
  let j = 0, i = 0, p = 0;
  
  while(j < 256) {
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
};

// rainbowCycle()
let rainbowCycle = function(wait) {
  let j = 0, i = 0, p = 0;
  
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
};

// theaterChaseRainbow()
let theaterChaseRainbow = function(wait) {
  let j = 0, q = 0, p = 0, i = 0;
  
  while(j < 256) { // cycle all 256 colors in the wheel
    q = 0;
    while(q < 3) {
	  i = 0;
	  while(i < Pixel.numPixels()) {
		p = (i + j) % 255;
        Pixel.setPixelColor(i + q, WheelR(p), WheelG(p), WheelB(p)); //turn every third pixel on
		i = i + 3;
      }
      Pixel.show();
      delay(wait);
	  i = 0;
      while(i < Pixel.numPixels()) {
        Pixel.setPixelColor(i + q, 0, 0, 0); // turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
};

// setup()
let setup = function() {
  Serial.println("strandtest_wheel ... start");
};

// loop()
let loop = function() {
  colorWipe(255, 0, 0, 50); // Red
  colorWipe(0, 255, 0, 50); // Green
  colorWipe(0, 0, 255, 50); // Blue

  theaterChase(127, 127, 127, 50); // White
  theaterChase(127, 0, 0, 50);     // Red
  theaterChase(0, 0, 127, 50);     // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  Serial.println("strandtest_wheel ... loop");
};
