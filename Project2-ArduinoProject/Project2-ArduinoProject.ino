#include "Servo.h"

// Servos Declaration
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Switches Declaration
int switch1Pin = 2;   // Switch connected to digital pin 2
int switch2Pin = 3;   // Switch connected to digital pin 3
int switch3Pin = 4;   // Switch connected to digital pin 4
int switch4Pin = 5;   // Switch connected to digital pin 5

//LEDs Pin Declaration
int LEDPin = 13;

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);

  pinMode(switch1Pin, INPUT); // Set the switch pin as input with internal pull-up resistor
  pinMode(switch2Pin, INPUT); // Set the switch pin as input with internal pull-up resistor
  pinMode(switch3Pin, INPUT); // Set the switch pin as input with internal pull-up resistor
  pinMode(switch4Pin, INPUT); // Set the switch pin as input with internal pull-up resistor
  pinMode(LEDPin, OUTPUT);
}

void loop()
{
}