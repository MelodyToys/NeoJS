/* jshint undef: true, unused: false, bitwise: false */
/* globals Pixel, millis, delay, Serial, WheelR, WheelG, WheelB */

// NeoJS Demo ~ sfranzyshen
// This is a port of strandtest.ino to JavaScript (Elk)

// colorWipe()
let colorWipe = function(color, wait) {
  let i = 0;
  
  while(i < Pixel.numPixels()) {
    Pixel.setPixelColor32(i, color);
    Pixel.show();
    delay(wait);
	i++;
  }
};

// theaterChase()
let theaterChase = function(color, wait) {
  let a = 0, b = 0, c = 0;
  
  while(a < 10) {
	b = 0;
    while(b < 3) {
      Pixel.clear();
	  c = b;
      while(c < Pixel.numPixels()) {
        Pixel.setPixelColor32(c, color);
		c += 3;
      }
      Pixel.show();
      delay(wait);
	  b++;
    }
	a++;
  }
};

// rainbow()
let rainbow = function(wait) {
  let firstPixelHue = 0, i = 0, pixelHue = 0;
  
  while(firstPixelHue < 5 * 65536) {
	i = 0;
    while(i < Pixel.numPixels()) {
      pixelHue = firstPixelHue + (i * 65536 / Pixel.numPixels());
      Pixel.setPixelColor32(i, Pixel.gamma32(Pixel.ColorHSV(pixelHue)));
	  i++;
    }
    Pixel.show();
    delay(wait);
	firstPixelHue += 256;
  }
};

// theaterChaseRainbow()
let theaterChaseRainbow = function(wait) {
  let firstPixelHue = 0, a = 0, b = 0, c = 0, hue = 0, color = 0;
  
  while(a < 30) {
	b = 0;
    while(b < 3) {
      Pixel.clear();
	  c = b;
      while(c < Pixel.numPixels()) {
        hue = firstPixelHue + c * 65536 / Pixel.numPixels();
        color = Pixel.gamma32(Pixel.ColorHSV(hue));
        Pixel.setPixelColor32(c, color);
		c += 3;
      }
      Pixel.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
	  b++;
    }
	a++;
  }
};

// setup()
let setup = function() {
  Serial.println("strandtest ... start");
};

// loop()
let loop = function() {
  colorWipe(Pixel.Color(255, 0, 0), 50); // Red
  colorWipe(Pixel.Color(0, 255, 0), 50); // Green
  colorWipe(Pixel.Color(0, 0, 255), 50); // Blue

  theaterChase(Pixel.Color(127, 127, 127), 50); // White
  theaterChase(Pixel.Color(127, 0, 0), 50); // Red
  theaterChase(Pixel.Color( 0, 0, 127), 50); // Blue

  rainbow(10);
  theaterChaseRainbow(50);
  Serial.println("strandtest ... loop");
};
