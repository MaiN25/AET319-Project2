#include "Servo.h"

// Servos Declaration
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Switches Declaration
int switch1Pin = 2;  // Switch connected to digital pin 2
int switch2Pin = 3;  // Switch connected to digital pin 3
int switch3Pin = 4;   // Switch connected to digital pin 4

// LEDs Pin Declaration
int LED1Pin = 13;
int LED2Pin = 8;

//Variable to track the stage of the enclosure
int stage = 0;


// Constant time durations
unsigned long TwoMinutes = 3000;
int InitialPosServo1,InitialPosServo2,InitialPosServo3,InitialPosServo4;

// Constant time durations
unsigned long LEDTimer = 7000;

// Specific variables for the reveal character method
int prevState = 0;  // Variable to save the switch 3 state
bool canMove = true;
int elapsedTime; // Variable to store the elapsed time

void setup() {
  Serial.begin(9600);

  // Configure switch pins as inputs
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);

  // Attach servos to pins
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);

  // Configure LED pin as output
  pinMode(LED1Pin, OUTPUT);
  pinMode(LED2Pin, OUTPUT);

  initialization();
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
        turnOnLED(true);
        reset();
      }
      break;
    case 3:
      swanMoving();
      stage++;
      reset();
      break;
    case 4:
      if (digitalRead(switch3Pin) == HIGH) {
        RevealCharacter();
        reset();
      }else if(canMove){
        swanMoving();
        reset();
      }
      break;
    default:
      reset();
      break;
  }
}
void initialization(){
  InitialPosServo1 = 15;
  InitialPosServo2 = 145;
  InitialPosServo3 = 0;
  InitialPosServo4 = 0;
  reset();

}
void reset() {
  servo1.write(InitialPosServo1);
  servo2.write(InitialPosServo2);
  servo3.write(InitialPosServo3);
  servo4.write(InitialPosServo4);
  digitalWrite(LED1Pin, LOW);
  digitalWrite(LED2Pin, LOW);

  if(stage >4){
    stage = 0;
    initialization();
  }
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
  for (int pos = InitialPosServo2; pos >= 55; pos -= 1) {
    servo2.write(pos);
    delay(5);
  }
  InitialPosServo2 = 55;
  stage++;
}
void turnOnLED(bool state) {
  if (state) {
    Serial.println("LED On");
    digitalWrite(LED1Pin, HIGH);
  } else {
    Serial.println("LED On");
    digitalWrite(LED1Pin, LOW);
  }
  delay(TwoMinutes); // delay for 2 minutes
  stage++;
}
void swanMoving() {
  servo3.write(InitialPosServo3);
  for (float pos = 0; pos <= 45; pos += 0.4) {  // goes from 0 degrees to 45 degrees
    // in steps of 1 degree
    servo3.write(pos);  // tell servo to go to position in variable 'pos'
    delay(5);           // waits 5 ms for the servo to reach the position
  }
  for (float pos = 45; pos >= 0; pos -= 0.4) {  // goes from 45 degrees to 0 degrees
    servo3.write(pos);                          // tell servo to go to position in variable 'pos'
    delay(5);                                   // waits 5 ms for the servo to reach the position
  }
}

void RevealCharacter() {
  unsigned long startTime = millis();
  elapsedTime = millis() - startTime;  // Calculate elapsed time

  if (canMove) {
    // Wobble the servo for 10 seconds
    while (elapsedTime < 10000) {
      elapsedTime = millis() - startTime;  // Update elapsed time
      if (prevState == 0) {
        InitialPosServo4 += 6;  // Increase servo position
        prevState++;
      } else {
        InitialPosServo4 -= 6;  // Decrease servo position
        prevState--;
      }
      digitalWrite(LED2Pin, HIGH);
      servo4.write(InitialPosServo4);  // Move the servo to the new positio
    }

    if (canMove) {
      InitialPosServo4 = 0;
      servo4.write(InitialPosServo4);
      canMove = false;
       stage++;
       reset();
    }
  }
}