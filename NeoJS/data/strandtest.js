// NeoJS Demo ~ sfranzyshen
// This is a port of strandtest_nodelay.ino to JavaScript (Elk)

let patPrev = 0,         // Previous Pattern Millis
    patCurr = 0;         // Current Pattern Number
let patInte = 5500,      // Pattern Interval (ms)
    pixPrev = 0,         // Previous Pixel Millis
    pixInte = 45,        // Pixel Interval (ms)
    pixQueu = 0,         // Pixel Queue
    pixCycl = 0,         // Pixel Cycle
    pixCurr = 0,         // Current Pixel Number
    pixNum = numPixels();// Number of Pixels

// colorWipe(r , g, b)
let clrWp = /*test*/function(r, g, b) {
    setPixelColor(pixCurr, r, g, b);
    show();
    pixCurr++;
    if(pixCurr >= pixNum) {
        pixCurr = 0;
        clear();
    }
};

/* this is a block test */
// rainbow()
let rnbw = function() {
    let i = 0,
        p;
    while(i < pixNum) {
        p = (i + pixCycl) & 255;
        setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
        i++;
    }
    show();
    pixCycl++;
    if(pixCycl >= 256) pixCycl = 0;
};
/*
 Here is another one
*/

// rainbowCycle()
let rnbwCyc = function() {
    let i = 0,
        p;
    while(i < pixNum) {
        p = ((i * 256 / pixNum) + pixCycl) & 255;
        setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
        i++;
    }
    show();
    pixCycl++;
    if(pixCycl >= 256 * 5) pixCycl = 0;
};

// theaterChase(r, g, b)
let thtrChs = function(r, g, b) {
    let i = 0;
    while(i < pixNum) {
        setPixelColor(i + pixQueu, r, g, b);
        i = i + 3;
    }
    show();
    i = 0;
    while(i < pixNum) {
        setPixelColor(i + pixQueu, 0, 0, 0);
        i = i + 3;
    }
    pixQueu++;
    if(pixQueu >= 3) pixQueu = 0;
};

// theaterChaseRainbow()
let thtrChsRnbw = function() {
    let i = 0,
        p;
    while(i < pixNum) {
        p = (i + pixCycl) % 255;
        setPixelColor(i + pixQueu, WheelR(p), WheelG(p), WheelB(p));
        i = i + 3;
    }
    show();
    i = 0;
    while(i < pixNum) {
        setPixelColor(i + pixQueu, 0, 0, 0);
        i = i + 3;
    }
    pixQueu++;
    pixCycl++;
    if(pixQueu >= 3) pixQueu = 0;
    if(pixCycl >= 256) pixCycl = 0;
};

// loop()
let loop = function() {
    let curMill = millis();
    if(curMill - patPrev >= patInte) {
        patPrev = curMill;
        patCurr++;
        if(patCurr >= 9) patCurr = 0;
    }
    if(curMill - pixPrev >= pixInte) {
        pixPrev = curMill;
        if(patCurr === 8) thtrChsRnbw();
        if(patCurr === 7) rnbwCyc();
        if(patCurr === 6) rnbw();
        if(patCurr === 5) thtrChs(0, 0, 127);    // Blue
        if(patCurr === 4) thtrChs(127, 0, 0);    // Red
        if(patCurr === 3) thtrChs(127, 127, 127);// White
        if(patCurr === 2) clrWp(0, 0, 255);      // Blue
        if(patCurr === 1) clrWp(0, 255, 0);      // Green
        if(patCurr === 0) clrWp(255, 0, 0);      // Red
    }
};


