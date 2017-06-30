
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Servo servo1;            // create servo object to control a servo
Servo servo2;            // create servo object to control a servo

const byte servo1pin = 10;
const byte servo2pin = 9;
const byte pot1pin = 0;
const byte pot2pin = 1;
const byte buttonPin = 2;
byte state = HIGH;       // HIGH means servos are on.  Button toggles LOW/HIGH

unsigned long time = 0;
unsigned long displaytime = 0;
unsigned long buttontime = 0;  // to protect against "bounce" in the button contact
short pot1, pot2 = 0;
float pos1, pos2 = 0.0;

long loopcount = 0;
long lastloopcount = 0;

// ---------------------------------------------------------------- //

void setup() {
  Serial.begin(9600);
  servo1.attach(servo1pin);
  servo2.attach(servo2pin);
  servo1.write(0);
  servo2.write(0);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING);  // HIGH means the button is pressed

  // by default, we'll generate the high voltage from the 3.3v line internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();  // Clear the buffer. init done.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // # of chars:  "12345678901234567890"
  display.println("  servo controller ");
  display.setTextSize(3);
  // # of chars:  "1234567"
  display.println("  O W  ");
  display.display();
  delay(2000);
}

// ---------------------------------------------------------------- //

void loop() {
  if (state == HIGH)
  {
    pot1 = analogRead(pot1pin);
    pot2 = analogRead(pot2pin);
    pos1 = fmap(pot1,0,1023,180,0); // map pot range to servo range of 0-179
    pos2 = fmap(pot2,0,1023,0,180); // map pot range to servo range of 0-179
    servo1.write(pos1);
    servo2.write(pos2);
  } else {
    servo1.write(90);  // just center the servos
    servo2.write(90);  // just center the servos    
  }

  // We don't have to update the display faster than every 100ms.
  if( millis() - displaytime > 100 ) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    if (state==HIGH) {
      display.println("manual control");
    } else {
      display.println("servos paused");
    }
    display.print("pot1:"); display.print(pot1); display.print(" => "); display.println(pos1);
    display.print("pot2:"); display.print(pot2); display.print(" => "); display.println(pos2);
    display.setCursor(84,24);
    display.print(lastloopcount);
    display.print("/s");
    display.display();  
    displaytime = millis();
  }

  // We track the number of loops/cycles per second
  if( millis() - time > 1000 ) 
  {
    time = millis();
    lastloopcount = loopcount;
    loopcount = 1;
  } else {
    loopcount++;
  }
  

}

// ---------------------------------------------------------------- //

void buttonPress() {
  if( millis() - buttontime > 300 ) {
    state = !state;
    buttontime = millis();
  }
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
