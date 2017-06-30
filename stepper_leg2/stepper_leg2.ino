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
AccelStepper waist(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

// I don't know how to initialize the stepper position... so all routines should end up back at the same spot... TODO fix
// angles are measured from fully contracted and parallel to the supporting limb set to 0.
long thighMin = 60;
long thighMax = 120;
long thigh0 = 120;
long thighCurrent = thigh0;
long waistMin = 0;
long waistMax = 60;
long waist0 = 60;
long waistCurrent = waist0;

bool dir = true; // temp var for demoing movement back and forth.  false = back & true = forth.

// based on globals
long orthowaistAngle() {
  long ofa = 180 - thighCurrent; // TODO replace with actual geometry
}

long angleMap(long a) {
  return a*11.377777; // 4096 steps for these motors = 1 full rotation = 360 degrees -> 11.37777777 ratio
}

void setup() {
  pinMode(button1Pin, INPUT);  // Safety first
  attachInterrupt(digitalPinToInterrupt(button1Pin), button1Press, RISING);  // HIGH means the button is pressed

  pinMode(button2Pin, INPUT);  // Reset neutral position to current position
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2Press, RISING);  // HIGH means the button is pressed

  thigh.setMaxSpeed(1400.0);
  thigh.setAcceleration(400.0);
  thigh.setCurrentPosition(angleMap(thighCurrent));
  //thigh.setSpeed(0);
  //thigh.moveTo(2048); // 4096 = 1 full rotation

  waist.setMaxSpeed(1400.0);
  waist.setAcceleration(100.0);
  waist.setCurrentPosition(angleMap(waistCurrent));
  //waist.setSpeed(0);
  //waist.moveTo(4096);

}

void loop() {
  (state==HIGH) ? runstate() : pausestate();
}

// 

// -------------------------------------------------------------------- //

void runstate() {
  // moves to the max and min, back and forth
  if (thigh.distanceToGo() == 0 && waist.distanceToGo() == 0) {
    dir = !dir;
    if (dir) {
      thigh.moveTo(angleMap(thighMax));
      waist.moveTo(angleMap(waistMax));    
    } else {
      thigh.moveTo(angleMap(thighMin));
      waist.moveTo(angleMap(waistMin));    
    }
  }
  thigh.run();
  waist.run();
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
      waist.enableOutputs();  // the design of your electronics this may turn off the power to the 
    } else {                     // motor coils, saving power. This is useful to support Arduino low 
      thigh.disableOutputs(); // power modes: disable the outputs during sleep and then reenable with 
      waist.disableOutputs(); // enableOutputs() before stepping again. If the enable Pin is defined, 
    }                            // sets it to OUTPUT mode and clears the pin to disabled.
    button1time = millis();
  }
}
void button2Press() {
  if( millis() - button2time > 300 ) {  // reject "bounce" from the button contact 
    thigh.setCurrentPosition(angleMap(thighNeutral));
    waist.setCurrentPosition(angleMap(waistNeutral));

    button1time = millis();
  }
}

