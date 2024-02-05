#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    60

#define FADE_PIN    7
#define BLINK_PIN    6
#define next         5

int rbg_0[][3] = { 
  {255,   000,    000}, // Red
  {255,   128,    000}, // Orange
  {255,   255,    000}, // YelHIGH
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
int rbg_1[] = {0,0,0};

int len0 = sizeof(rbg_0)/sizeof(rbg_0[0]);
int len1 = sizeof(rbg_1)/sizeof(rbg_1[0]);

int t;
int aba =99;
int count = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(FADE_PIN, INPUT);
  pinMode(BLINK_PIN, INPUT);
  Serial.begin(9600);
}

int rainbowfade(){

  for (int x = 0; x < len1; x++){ 
    for (int y = 0; y < 256; y++){
      rbg_1[x] = y;
      // Changes color of rows of led's
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB(rbg_1[0], rbg_1[1], rbg_1[2]);
        FastLED.show();
        if (digitalRead(BLINK_PIN) == 0){ return 0; }
      }
      
    }   
    
    t = x - 1;
    if ( t < 0 ){
      t = len1 - 1;
    }

    if ( rbg_1[t] != 0 ){
      for (int y = 255; y >= 0; y--){
        rbg_1[t] = y;
        // Changes color of rows of led's
        for ( int i = 0; i < NUM_LEDS; i++ ) {
          leds[i] = CRGB(rbg_1[0], rbg_1[1], rbg_1[2]);
          FastLED.show();
          if (digitalRead(BLINK_PIN) == 0){ return 0; }
        }
      }
    }
    delay(100);
  }
  return 0;
}

int blick() {
  for (int x = 0; x < len0; x++){
    for ( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB(rbg_0[x][0], rbg_0[x][1], rbg_0[x][2]);
      FastLED.show();
      if (digitalRead(FADE_PIN) == 0){ return 0; }
    }
    delay(1000);
  }
  return 0;
}

int blick1() {
  for ( int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]);
    FastLED.show();
    if (digitalRead(FADE_PIN) == 0){ return 0; }
  }
  delay(200);
  if ( digitalRead(next) == 0 ){
    count++;
    if ( count >= len0 ){      
      count = 0;
    }
  }
  return 0;
}


void loop() {
  delay(1000);

  if (digitalRead(BLINK_PIN) == 0) {
    aba = 0;
  }
  else if (digitalRead(FADE_PIN) == 0) {
    aba = 1;
  }
  else{}

  //Serial.println(digitalRead(BLINK_PIN));

  switch (aba){
    case 0: // BLINK
      blick();
      break;
  
    case 1: // FADE
      rainbowfade();
      break;

    default:
      break;
  }
}