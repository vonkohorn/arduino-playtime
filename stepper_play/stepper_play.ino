#include <AccelStepper.h>
#define HALFSTEP 8

const byte buttonPin = 2;
byte state = HIGH;       // HIGH/LOW corresponds to run/pause
unsigned long buttontime = 0;  // to protect against "bounce" in the button contact

// motor pins
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define motorPin5  8     // IN1 on the ULN2003 driver 2
#define motorPin6  9     // IN2 on the ULN2003 driver 2
#define motorPin7  10    // IN3 on the ULN2003 driver 2
#define motorPin8  11    // IN4 on the ULN2003 driver 2

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);


void setup() {
  pinMode(buttonPin, INPUT);  // Safety first
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);  // HIGH means the button is pressed

  stepper1.setMaxSpeed(1400.0);
  stepper1.setAcceleration(20000.0);
  stepper1.setSpeed(0);
  stepper1.moveTo(2048); // 4096 = 1 full rotation

  stepper2.setMaxSpeed(1400.0);
  stepper2.setAcceleration(12000.0);
  stepper2.setSpeed(0);
  stepper2.moveTo(1024);

}

void loop() {
  (state==HIGH) ? runstate() : pausestate();
}

// 

// -------------------------------------------------------------------- //

void runstate() {
  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  if (stepper2.distanceToGo() == 0) {
    stepper2.moveTo(-stepper2.currentPosition());
  }
  stepper1.run();
  stepper2.run();
}

void pausestate() {
  // don't do anything
}

void buttonPress() {
  if( millis() - buttontime > 300 ) {  // intended to eliminate "bounce" from the button contact 
    state = !state;
    if (state == HIGH) { 
      stepper1.enableOutputs();  // Disable motor pin outputs by setting them all LOW Depending on 
      stepper2.enableOutputs();  // the design of your electronics this may turn off the power to the 
    } else {                     // motor coils, saving power. This is useful to support Arduino low 
      stepper1.disableOutputs(); // power modes: disable the outputs during sleep and then reenable with 
      stepper2.disableOutputs(); // enableOutputs() before stepping again. If the enable Pin is defined, 
    }                            // sets it to OUTPUT mode and clears the pin to disabled.
    buttontime = millis();
  }
}

