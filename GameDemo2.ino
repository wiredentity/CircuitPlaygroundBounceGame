#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

#define BUTTON_PIN 4
#define MIDDLE_POSITION1 4
#define MIDDLE_POSITION2 5

int lightPosition = 0;
int speed = 200;  // Initial speed (milliseconds between each position change)
bool movingForward = true;
volatile bool buttonPressed = false;

AsyncDelay lightDelay;

void setup() {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, RISING);
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
  Serial.println("Game starting...");
  
  lightDelay.start(speed, AsyncDelay::MILLIS);
}

void loop() {
  // Update light position
  if (lightDelay.isExpired()) {
    lightDelay.restart();
    updateLightPosition();
  }

  // Check for button press
  if (buttonPressed) {
    buttonPressed = false; // Reset the flag
    Serial.println("Button pressed!");
    handleButtonPressLogic();
  }
}

void updateLightPosition() {
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(lightPosition, 0, 0, 255); // Blue light

  if (movingForward) {
    lightPosition++;
    if (lightPosition >= 9) {
      movingForward = false;
    }
  } else {
    lightPosition--;
    if (lightPosition <= 0) {
      movingForward = true;
    }
  }

  Serial.print("Light position: ");
  Serial.println(lightPosition);
}

void handleButtonPressLogic() {
  if (lightPosition == MIDDLE_POSITION1 || lightPosition == MIDDLE_POSITION2) {
    // Success: Flash white and increase speed
    Serial.println("Success! Light is in the middle.");
    playSuccessSequence();
    speed = max(speed - 20, 10); // Increase speed, minimum speed 10ms
    lightDelay.start(speed, AsyncDelay::MILLIS);
  } else {
    // Failure: Flash red and reset game
    Serial.println("Fail! Light is not in the middle.");
    playFailSequence();
    speed = 200; // Reset speed
    lightPosition = 0;
    movingForward = true;
    lightDelay.start(speed, AsyncDelay::MILLIS);
  }
}

void playSuccessSequence() {
  for (int i = 0; i < 3; i++) {
    allOn(0xFFFFFF);
    delay(100);
    CircuitPlayground.clearPixels();
    delay(100);
  }
  CircuitPlayground.playTone(1000, 200); // Play success sound
}

void playFailSequence() {
  for (int i = 0; i < 3; i++) {
    allOn(0xFF0000);
    delay(100);
    CircuitPlayground.clearPixels();
    delay(100);
  }
  CircuitPlayground.playTone(500, 200); // Play fail sound
}

void handleButtonPress() {
  delay (100);
  buttonPressed = true;
}


void allOn(int color){
for (int i = 0; i < 10; i++) {
CircuitPlayground.setPixelColor(i, color);
}
}

