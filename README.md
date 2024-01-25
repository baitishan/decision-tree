# decision-tree
A description of the electronics of the artwork decision tree, 2024

##Arduino Breath Light Effect with Motion Detection
###Overview
This Arduino project creates a "breathing" LED light effect that responds to motion detection. When motion is detected, an LED strip cycles through seven different colors (red, orange, yellow, green, blue, purple, pink), each color representing a "breath". Each breath lasts for 6 seconds, with the LED brightness increasing to a peak and then decreasing, mimicking a breathing pattern.

###Hardware Requirements
Arduino NANO
Adafruit NeoPixel LED Strip
Microwave sensor RCWL - 0516
Connecting wires

###Circuit Setup
Connect the data input of the NeoPixel LED strip to a digital pin on the Arduino (e.g., pin A3).
Connect the power and ground lines of the LED strip and the motion sensor to the Arduino's power and ground.
Connect the output of the motion sensor to another digital pin on the Arduino (e.g., pin 2).

###Software Requirements
Arduino IDE
Adafruit NeoPixel Library (can be installed via the Arduino IDE Library Manager)
###Code Explanation
The code operates by detecting motion using a motion sensor. Upon detection, it triggers a 7-breath light cycle. Each breath changes the color and modulates the brightness of the LEDs, creating a breathing effect. The cycle goes through seven colors and lasts for a total of 42 seconds (6 seconds per breath).

###Installation
Install the Arduino IDE and Adafruit NeoPixel Library.
Connect the Arduino to your computer.
Open the provided code in the Arduino IDE.
Select the correct Arduino board and port.
Upload the code to the Arduino.
###Usage
Once the code is uploaded, the Arduino will monitor the motion sensor. When motion is detected, the LED strip will start the breathing light cycle. If no motion is detected, the lights will remain off.

Code

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


Notes

Ensure your LED strip's power requirements are met.
Adjust LED_COUNT in the code to match the number of LEDs on your strip.
The brightness and color transitions can be adjusted in the code as needed.
