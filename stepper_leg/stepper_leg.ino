#include <AccelStepper.h>
#define HALFSTEP 8

const byte button1Pin = 2;
byte state = HIGH;       // HIGH/LOW corresponds to run/pause
unsigned long button1time = 0;  // to protect against "bounce" in the button contact

const byte button2Pin = 3;
unsigned long button2time = 0;  // to protect against "bounce" in the button contact

// motor pins
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

#define motorPin5  9     // IN1 on the ULN2003 driver 2
#define motorPin6  10     // IN2 on the ULN2003 driver 2
#define motorPin7  11    // IN3 on the ULN2003 driver 2
#define motorPin8  12    // IN4 on the ULN2003 driver 2

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper thigh(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper foot(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// I don't know how to initialize the stepper position... so all routines should end up back at the same spot... TODO fix
// angles are measured from fully contracted and parallel to the supporting limb set to 0.
long thighMin = 60;
long thighMax = 120;
long thighNeutral = 90;
long thighCurrent = thighNeutral;
long footMin = 60;
long footMax = 90;
long footNeutral = 120;
long footCurrent = footNeutral;

bool dir = true; // temp var for demoing movement back and forth.  false = back & true = forth.

// based on globals
long orthoFootAngle() {
  long ofa = 180 - thighCurrent; // TODO replace with actual geometry
}

long angleMap(long a) {
  return map(a,0,360,0,4096); // 4096 = 1 full rotation
}

void setup() {
  pinMode(button1Pin, INPUT);  // Safety first
  attachInterrupt(digitalPinToInterrupt(button1Pin), button1Press, RISING);  // HIGH means the button is pressed

  pinMode(button2Pin, INPUT);  // Reset neutral position to current position
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2Press, RISING);  // HIGH means the button is pressed

  thigh.setMaxSpeed(1400.0);
  thigh.setAcceleration(400.0);
  thigh.setCurrentPosition(angleMap(thighCurrent));
  thigh.setSpeed(0);
  //thigh.moveTo(2048); // 4096 = 1 full rotation

  foot.setMaxSpeed(1400.0);
  foot.setAcceleration(100.0);
  foot.setCurrentPosition(angleMap(footCurrent));
  foot.setSpeed(0);
  //foot.moveTo(4096);

}

void loop() {
  (state==HIGH) ? runstate() : pausestate();
}

// 

// -------------------------------------------------------------------- //

void runstate() {
  // moves to the max and min, back and forth
  if (thigh.distanceToGo() == 0 && foot.distanceToGo() == 0) {
    dir = !dir;
    if (dir) {
      thigh.moveTo(angleMap(thighMax));
      foot.moveTo(angleMap(footMax));    
    } else {
      thigh.moveTo(angleMap(thighMin));
      foot.moveTo(angleMap(footMin));    
    }
  }
  thigh.run();
  foot.run();
}

void pausestate() {
  // the steppers are disabled, but you could still do other stuff in the pause state
  // but we don't do anything
}

void button1Press() {
  if( millis() - button1time > 300 ) {  // reject "bounce" from the button contact 
    state = !state;
    if (state == HIGH) { 
      thigh.enableOutputs();  // Disable motor pin outputs by setting them all LOW Depending on 
      foot.enableOutputs();  // the design of your electronics this may turn off the power to the 
    } else {                     // motor coils, saving power. This is useful to support Arduino low 
      thigh.disableOutputs(); // power modes: disable the outputs during sleep and then reenable with 
      foot.disableOutputs(); // enableOutputs() before stepping again. If the enable Pin is defined, 
    }                            // sets it to OUTPUT mode and clears the pin to disabled.
    button1time = millis();
  }
}
void button2Press() {
  if( millis() - button2time > 300 ) {  // reject "bounce" from the button contact 
    thigh.setCurrentPosition(angleMap(thighNeutral));
    foot.setCurrentPosition(angleMap(footNeutral));

    button1time = millis();
  }
}

