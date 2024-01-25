#include <Adafruit_NeoPixel.h>

#define LED_COUNT 60
#define LED_PIN   A3  

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int breathDuration = 6000; // 6 seconds for one breath
const uint32_t colors[] = {
  strip.Color(255, 0, 0),     // Red
  strip.Color(255, 165, 0),   // Orange
  strip.Color(255, 255, 0),   // Yellow
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 0, 255),     // Blue
  strip.Color(128, 0, 128),   // Purple
  strip.Color(255, 192, 203)  // Pink
};

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  static unsigned long cycleStartTime = millis();
  unsigned long currentTime = millis();
  long timeElapsed = currentTime - cycleStartTime;

  int breathNumber = timeElapsed / breathDuration;
  long breathCycleTimeElapsed = timeElapsed % breathDuration;
  float breathProgress = (float)breathCycleTimeElapsed / breathDuration;

  // Brightness increases to the peak and then decreases
  int brightness;
  if (breathProgress < 0.5) {
    brightness = (sin(breathProgress * PI) * 255);
  } else {
    brightness = (sin((1 - breathProgress) * PI) * 255);
  }

  uint32_t color = colors[breathNumber % 7];

  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }

  strip.setBrightness(brightness);
  strip.show();

  // Restart the cycle after completing all colors
  if (breathNumber >= 7) {
    cycleStartTime = currentTime;
  }
}




