/*
 * Arduino interface for the use of WS2812 strip LEDs
 * Uses Adalight protocol and is compatible with Boblight, Prismatik etc...
 * "Magic Word" for synchronisation is 'Ada' followed by LED High, Low and Checksum
 * @author: Wifsimster <wifsimster@gmail.com> 
 * @library: FastLED v3.001
 * @date: 11/22/2015
 */
#include "FastLED.h"
#define NUM_LEDS 113
#define DATA_PIN 3

// Baudrate, higher rate allows faster refresh rate and more LEDs (defined in /etc/boblight.conf)
#define serialRate 115200

// Adalight sends a "Magic Word" (defined in /etc/boblight.conf) before sending the pixel data
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;

// Configuration for the smooth breathing effect
#define BREATH_STEP 3  // How quickly to increase/decrease brightness (lower = smoother/slower)
#define BREATH_DELAY 8 // Milliseconds to pause between brightness changes

// Initialise LED-array
CRGB leds[NUM_LEDS];

void setup() {
  // Use NEOPIXEL to keep true colors
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  // // Initial RGB flash
  // LEDS.showColor(CRGB(255, 0, 0));
  // delay(500);
  // LEDS.showColor(CRGB(0, 255, 0));
  // delay(500);
  // LEDS.showColor(CRGB(0, 0, 255));
  // delay(500);
  // LEDS.showColor(CRGB(0, 0, 0));
  // Initial smooth animation sequence: Rainbow "Loading" then White Breath
  
  // --- Phase 1: Rainbow Loading Effect (Mac Beach Ball Style) ---
  // Cycle through a shifting rainbow pattern across the strip to simulate a loading indicator.
  const int loadingSteps = 90; // Controls the length of the loading animation
  for (int j = 0; j < loadingSteps; j++) {
    // Fill the entire strip with a shifting rainbow pattern based on the loop counter
    fill_rainbow(leds, NUM_LEDS, j * 3); 
    FastLED.show();
    delay(BREATH_DELAY);
  }
  
  // Clear the strip before starting the white breath
  LEDS.showColor(CRGB::Black); 
  delay(200);

  // --- Phase 2: White Breath ---
  // Fade In (0 to 255)
  for (int brightness = 0; brightness <= 255; brightness += BREATH_STEP) {
    LEDS.showColor(CRGB(brightness, brightness, brightness)); // White
    delay(BREATH_DELAY);
  }
  // Fade Out (255 to 0)
  for (int brightness = 255; brightness >= 0; brightness -= BREATH_STEP) {
    LEDS.showColor(CRGB(brightness, brightness, brightness)); // White
    delay(BREATH_DELAY);
  }
  
  Serial.begin(serialRate);
  // Send "Magic Word" string to host
  Serial.print("Ada\n");
}

void loop() { 
  // Wait for first byte of Magic Word
  for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    // Check next byte in Magic Word
    if(prefix[i] == Serial.read()) continue;
    // otherwise, start over
    i = 0;
    goto waitLoop;
  }
  
  // Hi, Lo, Checksum  
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
  
  // If checksum does not match go back to wait
  if (chk != (hi ^ lo ^ 0x55)) {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // Read the transmission data and set LED values
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  
  // Shows new values
  FastLED.show();
}
