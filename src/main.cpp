#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    30

int Iarray[][3] = { 
  {255,   000,    000}, // Red
  {255,   128,    000}, // Orange
  {255,   255,    000}, // Yellow
  {128,   255,    000}, // Lime
  {000,   255,    000}, // Green
  {000,   255,    128}, // Light Green
  {000,   255,    255}, // Cyan
  {000,   128,    255}, // Aqua
  {000,   000,    255}, // Blue
  {128,   000,    255}, // Purple
  {255,   000,    255}, // Pink
  {255,   000,    128}, // Magenta
  {255,   255,    255}  // White 
};
int len = sizeof(Iarray)/sizeof(Iarray[0]);


int rbg[] = {0,0,0};

int len1 = sizeof(rbg)/sizeof(rbg[0]);

int t;



CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  
  for (int x = 0; x < len; x++){
    for ( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB(Iarray[x][0], Iarray[x][1], Iarray[x][2]);
      FastLED.show();
    }
    delay(2000);
  }
  
  /*
  for (int x = 0; x < len1; x++){ 
    for (int y = 0; y < 256; y++){
      rbg[x] = y;
      // Changes color of rows of led's
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB(rbg[0], rbg[1], rbg[2]);
        FastLED.show();
      }
    }
    
    t = x - 1;
    if ( t < 0 ){
      t = len1 - 1;
    }

    if ( rbg[t] != 0 ){
      for (int y = 255; y >= 0; y--){
        rbg[t] = y;
        // Changes color of rows of led's
        for ( int i = 0; i < NUM_LEDS; i++ ) {
          leds[i] = CRGB(rbg[0], rbg[1], rbg[2]);
          FastLED.show();
        }
      }
    }
    delay(100);
  }
  */
}