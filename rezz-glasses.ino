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

#define BRIGHTNESS 50

#define NUM_LOOPS_COLORWIPE 1
#define NUM_LOOPS_RAINBOW 1
#define NUM_LOOPS_EXPAND 1
#define NUM_LOOPS_PUMPKIN 1
#define NUM_LOOPS_STRIPES 2

#define EXPAND_CYCLES 2
#define STRIPES_CYCLES 10

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
