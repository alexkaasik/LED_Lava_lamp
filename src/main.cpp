#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN   0
#define NUM_LEDS  32


CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop(){
  for ( int i = 0; i < NUM_LEDS; i++ ){
    leds[i] = CRGB(255, 255, 0);
    FastLED.show();
  }
}