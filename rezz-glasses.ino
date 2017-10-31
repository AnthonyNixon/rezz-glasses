#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINLEFT 15
#define PINRIGHT 13

#define OUTSIDE_START 0
#define OUTSIDE_END 23
#define MIDDLE_START 24
#define MIDDLE_END 39
#define INNER_START 40
#define INNER_END 43
#define NUM_PIXELS 44

#define BRIGHTNESS 25

#define NUM_LOOPS_COLORWIPE 2
#define NUM_LOOPS_RAINBOW 1
#define NUM_LOOPS_EXPAND 1
#define NUM_LOOPS_PUMPKIN 2
#define NUM_LOOPS_STRIPES 1
#define NUM_LOOPS_STRIPEWIPE 3
#define NUM_LOOPS_EYEROLL 2
#define NUM_LOOPS_ROTATE_EYES 3
#define NUM_LOOPS_ROTATE_EYES2 0

#define EXPAND_CYCLES 2
#define STRIPES_CYCLES 10
#define ROTATE_EYES_CYCLES 4

#define DELAY 50


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel left = Adafruit_NeoPixel(44, PINLEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right = Adafruit_NeoPixel(44, PINRIGHT, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  left.begin();
  right.begin();
  showStrips();
}

void loop() {
  for (uint16_t i=0; i<NUM_LOOPS_COLORWIPE; i++) {
    colorWipe(left.Color(BRIGHTNESS, 0, 0)); // Red
    colorWipe(left.Color(0, BRIGHTNESS, 0)); // Green
    colorWipe(left.Color(0, 0, BRIGHTNESS)); // Blue
  }

  for (uint16_t i=0; i<NUM_LOOPS_RAINBOW; i++) {
    rainbow(); // Red
  }

  for (uint16_t i=0; i<NUM_LOOPS_EXPAND; i++) {
    expand();
  }

  for (uint16_t i=0; i<NUM_LOOPS_PUMPKIN; i++) {
    pumpkin();
  }

  for (uint16_t i=0; i<NUM_LOOPS_STRIPES; i++) {
    stripes();
  }

  for (uint16_t i=0; i<NUM_LOOPS_STRIPEWIPE; i++){
    stripeWipe();
  }

  for (uint16_t i=0; i<NUM_LOOPS_EYEROLL; i++){
    eyeRoll();
  }

  for (uint16_t i=0; i<NUM_LOOPS_ROTATE_EYES; i++){
    rotateEyes();
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  // OUTSIDE
  for(uint16_t i=0; i<NUM_PIXELS; i++) {
    left.setPixelColor(i, c);
    right.setPixelColor(getRight(i), c);
    left.show();
    right.show();
    delay(DELAY);
  }
}

void rainbow() {
  for (uint16_t i=0; i<BRIGHTNESS; i++) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(i, 0, 0));
    }
    showStrips();
    delay(DELAY);
  }

  for (uint16_t i=0; i<BRIGHTNESS; i++) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(BRIGHTNESS, i, 0));
    }
    showStrips();
    delay(DELAY);
  }

  for (uint16_t i=BRIGHTNESS; i>0; i--) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(i, BRIGHTNESS, 0));
    }
    showStrips();
    delay(DELAY);
  }

  for (uint16_t i=0; i<BRIGHTNESS; i++) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(0, BRIGHTNESS, i));
    }
    showStrips();
    delay(DELAY);
  }

  for (uint16_t i=BRIGHTNESS; i>0; i--) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(0, i, BRIGHTNESS));
    }
    showStrips();
    delay(DELAY);
  }

    for (uint16_t i=BRIGHTNESS; i>0; i--) {
    for (uint8_t j=0; j<NUM_PIXELS; j++) {
      setPixelColors(j, left.Color(0, 0, i));
    }
    showStrips();
    delay(DELAY);
  }
}

void expand() {
  expandHelper(left.Color(BRIGHTNESS, 0, 0), left.Color(0, BRIGHTNESS, 0));
  expandHelper(left.Color(BRIGHTNESS, 0, 0), left.Color(0, 0, BRIGHTNESS));
  expandHelper(left.Color(0, BRIGHTNESS, 0), left.Color(BRIGHTNESS, 0, 0));
  expandHelper(left.Color(0, BRIGHTNESS, 0), left.Color(0, 0, BRIGHTNESS));
  expandHelper(left.Color(0, 0, BRIGHTNESS), left.Color(BRIGHTNESS, 0, 0));
  expandHelper(left.Color(0, 0, BRIGHTNESS), left.Color(0, BRIGHTNESS, 0));
}

void expandHelper(uint32_t background, uint32_t ring) {
  for (uint8_t loops=0; loops<EXPAND_CYCLES; loops++) {
    for (uint8_t i=0; i<3; i++){
    for (uint8_t i=0; i<NUM_PIXELS; i++){
      setPixelColors(i, background);
    }
    if (i==0) {
      for (uint8_t i=INNER_START; i<=INNER_END; i++){
        setPixelColors(i, ring);
      }
    } else if (i==1) {
      for (uint8_t i=MIDDLE_START; i<=MIDDLE_END; i++){
        setPixelColors(i, ring);
      }
    } else {
      for (uint8_t i=OUTSIDE_START; i<=OUTSIDE_END; i++){
        setPixelColors(i, ring);
      }
    }
    showStrips();
    delay(DELAY*10);
  }
  }
}

void pumpkin() {
  for (uint8_t i=MIDDLE_START; i<=INNER_END; i++){
    setPixelColors(i, left.Color(BRIGHTNESS, BRIGHTNESS*.4, 0));
  }
  for (uint8_t i=OUTSIDE_START; i<=OUTSIDE_END; i++) {
    setPixelColors(i, left.Color(0, 0, 0));
  }
  for (uint8_t i=OUTSIDE_START; i<OUTSIDE_END; i++){
    setPixelColors(i, left.Color(0, BRIGHTNESS, 0));
    setPixelColors(i+1, left.Color(0, BRIGHTNESS, 0));
    showStrips();
    delay(DELAY);
    setPixelColors(i, left.Color(0, 0, 0));
  }
}

void stripes() {
  stripesHelper(left.Color(BRIGHTNESS, 0, 0), left.Color(0, BRIGHTNESS, 0));
  stripesHelper(left.Color(0, BRIGHTNESS, 0), left.Color(0, 0, BRIGHTNESS));
  stripesHelper(left.Color(0, 0, BRIGHTNESS), left.Color(BRIGHTNESS, 0, 0));
}

void stripesHelper(uint32_t background, uint32_t stripe) {
  for (uint8_t loops=0; loops<STRIPES_CYCLES; loops++){
    for (uint8_t i=0; i<4; i++){
      for (uint16_t j=0; j<NUM_PIXELS; j++){
        if ((j % 4) == i) {
          setPixelColors(j, stripe);
        } else {
          setPixelColors(j, background);
        }
      }
      showStrips();
      delay(DELAY);
    }
  }
}

void stripeWipe() {
  stripeWipeHelper(left.Color(BRIGHTNESS, 0, 0));
  stripeWipeHelper(left.Color(0, BRIGHTNESS, 0));
  stripeWipeHelper(left.Color(0, 0, BRIGHTNESS));
}

void stripeWipeHelper(uint32_t color){
  for (uint16_t i=0; i<16; i++){
    switch (i) {
    case 0:
      setPixelColors(0, color);
      setPixelColors(24, color);
      break;
    case 1:
      setPixelColors(1, color);
      setPixelColors(2, color);
      setPixelColors(25, color);
      break;
    case 2:
      setPixelColors(3, color);
      setPixelColors(26, color);
      setPixelColors(40, color);;
      break;
    case 3:
      setPixelColors(4, color);
      setPixelColors(5, color);
      setPixelColors(27, color);
      break;
    case 4:
      setPixelColors(6, color);
      setPixelColors(28, color);
      break;
    case 5:
      setPixelColors(7, color);
      setPixelColors(8, color);
      setPixelColors(29, color);
      break;
    case 6:
      setPixelColors(9, color);
      setPixelColors(30, color);
      setPixelColors(41, color);
      break;
    case 7:
      setPixelColors(10, color);
      setPixelColors(11, color);
      setPixelColors(31, color);
      break;
    case 8:
      setPixelColors(12, color);
      setPixelColors(32, color);
      break;
    case 9:
      setPixelColors(13, color);
      setPixelColors(14, color);
      setPixelColors(33, color);
      break;
    case 10:
      setPixelColors(15, color);
      setPixelColors(34, color);
      setPixelColors(42, color);
      break;
    case 11:
      setPixelColors(16, color);
      setPixelColors(17, color);
      setPixelColors(35, color);
      break;
    case 12:
      setPixelColors(18, color);
      setPixelColors(36, color);
      break;
    case 13:
      setPixelColors(19, color);
      setPixelColors(20, color);
      setPixelColors(37, color);
      break;
    case 14:
      setPixelColors(21, color);
      setPixelColors(38, color);
      setPixelColors(43, color);
      break;
    case 15:
      setPixelColors(22, color);
      setPixelColors(23, color);
      setPixelColors(39, color);
      break;
    }
    showStrips();
    delay(DELAY);
  }
}

void eyeRoll(){
  for (uint16_t i=0; i<NUM_PIXELS; i++){
    setPixelColors(i, left.Color(0,0,0));
  }

  for (uint16_t i=OUTSIDE_START; i<=OUTSIDE_END; i++){
    setPixelColors(i, left.Color(0, BRIGHTNESS, 0));
  }

  for (uint16_t i=MIDDLE_START; i<=MIDDLE_END; i++){
    left.setPixelColor(i, left.Color(BRIGHTNESS, 0, 0));
    right.setPixelColor(i, left.Color(BRIGHTNESS, 0, 0));

    showStrips();
    delay(DELAY*2);    
    left.setPixelColor(i, left.Color(0, 0, 0));
    right.setPixelColor(i, left.Color(0, 0, 0));
  }
  
  showStrips();
}

void rotateEyes() {
  for (uint8_t i=INNER_START; i<=INNER_END; i++){
    setPixelColors(i, left.Color(BRIGHTNESS, 0, 0));
  }
  
  for (uint8_t i=0; i<6; i++){
    for (uint8_t j=OUTSIDE_START; j<=OUTSIDE_END; j++){
      setPixelColors(j, left.Color(0, 0, 0));
    }

    setPixelColors(i, left.Color(0, BRIGHTNESS, 0));
    setPixelColors(i+6, left.Color(0, BRIGHTNESS, 0));
    setPixelColors(i+12, left.Color(0, BRIGHTNESS, 0));
    setPixelColors(i+18, left.Color(0, BRIGHTNESS, 0));
    showStrips();
    delay(DELAY);
  }
}

void rotateEyes2() {
  for (uint16_t j=OUTSIDE_START; j<=INNER_END; j++){
    setPixelColors(j, left.Color(0,0,0));
  }

  
}


uint16_t getRight(uint16_t left) {
  if (left <= OUTSIDE_END) {
    return OUTSIDE_END-left;
  } else if (left <= MIDDLE_END) {
    return (MIDDLE_END-left)+MIDDLE_START;
  } else {
    return (INNER_END-left)+INNER_START;
  }
}

void setPixelColors(uint8_t i, uint32_t color){
  left.setPixelColor(i, color);
  right.setPixelColor(getRight(i), color);
}

void showStrips() {
  left.show();
  right.show();
}
