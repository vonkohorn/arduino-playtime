

#include <Servo.h>

Servo servoLeft;            // create servo object to control a servo
Servo servoRight;            // create servo object to control a servo

const byte servoLeftPin = 9;
const byte servoRightPin = 10;
const byte buttonPin = 2;
const byte ledPin = 13;
const int sensorPin = A0;
volatile float smoothed = 0;

unsigned long time = 0;
volatile byte state = LOW;

void setup() {
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);  // HIGH means the button is pressed
}

void loop() {
  if (state == HIGH) {
    digitalWrite(ledPin, HIGH);   // turn LED on:
    forward(); 
    delay(1000);
    reverse();
    delay(1000);
    turnRight();
    delay(1000);
    turnLeft();
    delay(1000);
    state = LOW;
  } else {
    blink();
    smoothed = (smoothed*9 + analogRead(sensorPin)/5)/10;
    servoLeft.write(smoothed);
    servoRight.write(180-smoothed);
    delay(10);
    //stopRobot();
  }
}

void buttonPress() {
  state = HIGH;
}

void blink() {
  if( millis() - time > 2000 ) {
    time = millis();
  }
  if( millis() - time < 50 ) {
    digitalWrite(ledPin, HIGH);  // turn LED on:
  } else {
    digitalWrite(ledPin, LOW);   // turn LED off:
  }
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  servoLeft.write(0);
  servoRight.write(180);
}

void reverse() {
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  servoLeft.write(0);
  servoRight.write(0);
}

void stopRobot() {
  servoLeft.write(90);
  servoRight.write(90);
}

