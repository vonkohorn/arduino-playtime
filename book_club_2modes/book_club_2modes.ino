

#include <Servo.h>

Servo servoLeft;            // create servo object to control a servo
Servo servoRight;            // create servo object to control a servo

const byte servoLeftPin = 9;
const byte servoRightPin = 10;
const byte buttonPin = 2;
const byte ledPin = 13;
const int sensorPin = A0;

unsigned long time = 0;
unsigned long lastPress = 0;
volatile byte state = LOW;
volatile byte mode = LOW;     // LOW = button, HIGH = photoresistor
volatile int smoothed = 0;

void setup() {
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);  // HIGH means the button is pressed
}

void loop() {
  if (mode==LOW) {
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
      stopRobot();
      blink();
    }
  } else {
    smoothed = (smoothed*3 + analogRead(sensorPin)/4)/4;
    servoLeft.write(smoothed);
    servoRight.write(180-smoothed);
    delay(10);
  }
}

void buttonPress() {
  if( millis() - lastPress < 2000 ) {     // indicates a "double click"
    mode = !mode;                         // toggle the mode
  } else {                                // just a normal button press
    state = HIGH;
  }
  lastPress = millis();                   // reset this variable
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

