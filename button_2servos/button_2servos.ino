/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servoLeft;            // create servo object to control a servo
Servo servoRight;            // create servo object to control a servo
// twelve servo objects can be created on most boards

int buttonState = 0;      // HIGH means the button is pressed
int pos = 0;              // variable to store the servo position
const int buttonPin = 2;
const int servoLeftPin = 9;
const int servoRightPin = 10;
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);         // turn LED on:
    forward();             // Example: move forward
    delay(2000);           // Wait 2000 milliseconds (2 seconds)
    reverse();
    delay(2000);
    turnRight();
    delay(2000);
    turnLeft();
    delay(2000);
    stopRobot();
    delay(2000);
  } 
  servoLeft.write(90);                      // back to center
  servoRight.write(90);                     // back to center
  digitalWrite(LED_BUILTIN, HIGH);          // turn LED off:
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
/*    
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      servoLeft.write(pos); 
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servoLeft.write(pos);
      delay(15);
    }
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servoRight.write(pos);
      delay(15);
    }
*/
