#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN   8
#define NUM_LEDS  112

#define Nmode 7
#define Pmode 6
#define next 5
#define prev 4

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
int SR;
int set;

int aba = 0;
int count = 0;
int colm = 8;
int row = 14;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(Nmode, INPUT);
  pinMode(Pmode, INPUT);
  pinMode(prev, INPUT);
  pinMode(next, INPUT);
  //Serial.begin(9600);
}


int rainbowfade(){  
  for (int x = 0; x < len1; x++){ 
    for (int y = 0; y < 256; y=y+4){
      rbg_1[x] = y;
      // Changes color of rows of led's
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB(rbg_1[0], rbg_1[1], rbg_1[2]);
        FastLED.show();
        if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
          FastLED.clear();
          return 0;
        } 
      }
    }   
    
    t = x - 1;
    if ( t < 0 ){
      t = len1 - 1;
    }

    if ( rbg_1[t] != 0 ){
      for (int y = 255; y >= 0; y=y-4){
        rbg_1[t] = y;
        // Changes color of rows of led's
        for ( int i = 0; i < NUM_LEDS; i++ ) {
          leds[i] = CRGB(rbg_1[0], rbg_1[1], rbg_1[2]);
          FastLED.show();
                  if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
          FastLED.clear();
          return 0;
        } 
        }
      }
    }
    delay(100);
  }
  return 0;
}

void counter(){
  if (digitalRead(next) == 1 ){
    count++;
    if ( count >= len0 ){ count = 0;}
  }

  if (digitalRead(prev) == 1 ){
    count--; 
    if ( count < 0 ){ count = len0-1;}
  }
}

int blick(){

  fill_solid( leds, NUM_LEDS, CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]) );
  FastLED.show();
  
  if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1) { 
    FastLED.clear();
    return 0;
  }

  counter();

  return 0;
}

int bick(){
  for (int x = 0; x < len0; x++){
    fill_solid( leds, NUM_LEDS, CRGB(rbg_0[x][0], rbg_0[x][1], rbg_0[x][2]) );
    FastLED.show();
    delay(1000);
    if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
      FastLED.clear();
      return 0;
    } 
  }
  return 0;
}

// raname
int hline1() {
  for (int x = 0; x < len0; x++){
    for ( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB(rbg_0[x][0], rbg_0[x][1], rbg_0[x][2]);
      FastLED.show();
      if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
        FastLED.clear();
        return 0;
      } 
    }
    delay(500);
    FastLED.clear();
  }

  return 0;
}

// raname
int hline( char isRev ) {
  
  if ( isRev == 'n' ){
    set = 0;
    for (int i = 0; i < colm; i++) {
      for ( int j = set; j < set+row; j++ ) { 
        leds[j] = CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]);
        FastLED.show();
        if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
          FastLED.clear();
          return 0;
        } 
      }
      delay(200);
      set = set+row;

      counter();
      FastLED.clear();
    }
  } 
  else if ( isRev == 'y' ) {
    set = row*colm;
    for (int i = colm-1; i >= 0; i--) {
      for ( int j = set-1; j >= set-row; j-- ) { 
        leds[j] = CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]);
        FastLED.show();
        if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){
          FastLED.clear();
          return 0;
        } 
      }
      
      delay(200);
      set = set-row;

      counter();
      FastLED.clear();
    }
  }
  return 0;
}

int blick1() {
  
  if ( digitalRead(next) == 1 ){
    count++;
    delay(200);
    if ( count > len0 ){ count = len0; }
  }

  if (count == len0) { 
    blick();
    return 0;
  }
  
  for ( int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]);
    FastLED.show();

    if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){ return 0; }
  }

  delay(200);
  return 0;
}

// Ring up or/and down  animation DONE
int ring( char isRev ) {
  
  int start = 0;
  int end = row;
  int i;
  
  if ( isRev == 'n' ){
      i = start;
  }
  else if ( isRev = 'y') {
      i = end-1;
  }

  while ( start < end ) { 
    set = 0;
    for (int j = 0; j < colm; j++){
      if ( j % 2 == 0 ){ SR = i+set; }
      else { SR = (set+row)-(i+1); }
          
      leds[SR] = CRGB(rbg_0[count][0], rbg_0[count][1], rbg_0[count][2]);
      set = set+row;
      FastLED.show();
      if (digitalRead(Nmode) == 1 or digitalRead(Pmode) == 1){ 
        FastLED.clear(); 
        return 0;
      }
      counter();
    }

    delay(200);

    FastLED.clear();
    
    if ( isRev = 'n') { i++; }
    else if ( isRev = 'y') { i--; }
    start++;
  }
  return 0;
}

void loop() {

  if (digitalRead(Nmode) == 1) { aba++; }
  else if (digitalRead(Pmode) == 1) { aba--; }
  /*
  Serial.println(digitalRead(Nmode));
  Serial.println(digitalRead(Pmode));
  Serial.println(digitalRead(next));
  Serial.println(digitalRead(prev));
  Serial.println(count);
  Serial.println(aba);
  Serial.println();
  */

  delay(100);
  
  switch (aba) {
    case 0: // blink
      blick();
      break;
    case 1: // ring
      ring('n');
      break;
    case 2: // ring
      ring('y');
      break;
    case 3: // ring
      ring('y');
      ring('n');
      break;
    case 4:
      hline('n');
      break;
    case 5:
      hline('y');
      break;
    case 6:
      rainbowfade();
      break;
    default:
      break;
  }
  
  if ( aba > 6 ){ aba = 0; }
  else if ( aba < 0 ) { aba = 6; }

}