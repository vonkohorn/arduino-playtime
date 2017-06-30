

#include <Servo.h>
#include "Ultrasonic.h"
Servo servoH;            // Horizontal servo object
Servo servoV;            // Vetrical servo object

const byte servoHPin = 9; 
const byte servoVPin = 10;

long d00, d01, d10, d11; // distances, in cm
long hposition = 90; // horizontal rotation position, positive is to the right
long vposition = 90; // vertical rotation position, positive is up
long h,v; // used for storing horizontal and vertical diffs

Ultrasonic ultrasonic00(12,13); // left, low
Ultrasonic ultrasonic01(4,2); // left, high
Ultrasonic ultrasonic10(7,8); // right, low
Ultrasonic ultrasonic11(5,6); // right, high

void setup() {
  servoH.attach(servoHPin);
  servoV.attach(servoVPin);
}

void loop() {
  d00 = ultrasonic00.Ranging(CM);
  d01 = ultrasonic01.Ranging(CM);
  d10 = ultrasonic10.Ranging(CM);
  d11 = ultrasonic11.Ranging(CM);
  
  h = (d10+d11)-(d00+d01); // Horizontal diff, right is positive
  v = (d01+d11)-(d00+d10); // Vertical diff, up is positive
    
  if (h > 0) {
    hposition = hposition + 5;
  } else {
    hposition = hposition - 5;
  }

  if (hposition > 180) { hposition = 180; }
  if (hposition < 0) { hposition = 0; }
  
  servoH.write(hposition);
  servoV.write(90);

  delay(100);
}

