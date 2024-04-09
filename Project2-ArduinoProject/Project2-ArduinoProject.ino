#include "Servo.h"

// Servos Declaration
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Switches Declaration
int switch1Pin = 2;  // Switch connected to digital pin 2
int switch2Pin = 3;  // Switch connected to digital pin 3
int switch3Pin = 4;  // Switch connected to digital pin 4
int switch4Pin = 5;  // Switch connected to digital pin 5

// LEDs Pin Declaration
int LEDPin = 13;

//Variable to track the stage of the enclosure
int stage = 0;


// Variable to store the initial position of each servo
int InitialPosServo1 = 15;
int InitialPosServo2 = 90;

void setup() {
  Serial.begin(9600);

  // Configure switch pins as inputs
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);

  // Attach servos to pins
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);

  // Configure LED pin as output
  pinMode(LEDPin, OUTPUT);
  reset();
}

void loop() {

  switch (stage) {
    case 0:
      if (digitalRead(switch1Pin) == HIGH) {
        HatchingEggs();
        reset();
      }
      break;
    case 1:
      if (digitalRead(switch2Pin) == HIGH) {
        ShowSpeechBubble();
        servo1.detach();
        reset();
      }
      break;
    case 2:
      if (digitalRead(switch2Pin) == LOW) {
        Serial.println("im in stage 3");
        turnOnLED(true);
        reset();
      }
      break;
    default:
      reset();
      break;
  }
}

void reset() {
  servo1.write(InitialPosServo1);
  servo2.write(InitialPosServo2);
  servo3.write(90);
  servo4.write(0);
  digitalWrite(LEDPin, LOW);
}

// This function simulate the hatching egg process by gradually moving the upper part of the egg
// from its initial position to a position where it appears to have 'fallen off'
// and remains in that position, demonstrating a cracked egg.
void HatchingEggs() {
  servo1.write(InitialPosServo1);
  for (int pos = InitialPosServo1; pos <= 90; pos += 1) {
    servo1.write(pos);
    delay(5);
  }
  InitialPosServo1 = 90;
  stage++;
}

// This function flips the attached Speech Bubble perpendicular by moving the servo
void ShowSpeechBubble() {
  servo2.write(InitialPosServo2);
  for (int pos = 90; pos >= 0; pos -= 1) {
    servo2.write(pos);
    delay(5);
  }
  InitialPosServo2 = 0;
  stage++;
}
void turnOnLED(bool state) {
  if (state) {
    Serial.println("LED On");
    digitalWrite(LEDPin, HIGH);
  } else {
    Serial.println("LED On");
    digitalWrite(LEDPin, LOW);
  }
  delay(TwoMinutes);  // delay for 2 minutes
  stage++;
}
