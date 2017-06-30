// joystick
int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
boolean buttonState = 0;
boolean prevButtonState = 1; // this is high so that the input_pullup won't trigger the fan when the unit powers on and runs setup.

// motor1
int enablePin1 = 11;
int in1Pin = 10;
int in2Pin = 9;
int speed1 = 0;

// motor2
int enablePin2 = 8;
int in3Pin = 7;
int in4Pin = 6;
int speed2 = 0;

boolean fanState = 0;

void setup() {
  Serial.begin(115200); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  // activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
   
  pinMode(enablePin1, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(enablePin2, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  delay(50);
}

void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  if (buttonState && !prevButtonState) {  // this is a click down on the joystick
    fanState = !fanState;
  }

  if (fanState == 1) {
    setMotor1(-255); // blows forward at full strength
    setMotor2(0);    
  } else {
    speed1 = map(xPosition,0,1023,-255,255);
    speed2 = map(yPosition,0,1023,-255,255);
    setMotor1(speed1);
    setMotor2(speed2);
  }
  prevButtonState = buttonState;
}


void setMotor1(int speed) {
  boolean dir = (speed > 0) ? 1 : 0;
  analogWrite(enablePin1, abs(speed));
  digitalWrite(in1Pin, ! dir);
  digitalWrite(in2Pin, dir);
}
// can a better programmer make this easy for n motors, please?
void setMotor2(int speed) {
  boolean dir = (speed > 0) ? 1 : 0;
  analogWrite(enablePin2, abs(speed));
  digitalWrite(in3Pin, ! dir);
  digitalWrite(in4Pin, dir);
}

