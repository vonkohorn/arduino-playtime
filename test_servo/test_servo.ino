/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;            // create servo object to control a servo
// twelve servo objects can be created on most boards

int buttonState = 0;      // HIGH means the button is pressed
int pos = 0;              // variable to store the servo position
const int buttonPin = 2;
const int servoPin = 9;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(servoPin);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    for (pos = 0; pos <= 180; pos += 45) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(750);                       // waits 15ms for the servo to reach the position
    }
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

  } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
    myservo.write(90);
  }}


