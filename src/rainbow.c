
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