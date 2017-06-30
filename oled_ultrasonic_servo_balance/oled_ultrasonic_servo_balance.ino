
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Ultrasonic.h"
#include <Servo.h>
#include <math.h>       /* atan */

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Ultrasonic ultrasonic1(12,8); // trig, echo
Ultrasonic ultrasonic2(6,5);  // trig, echo

float distance1, distance2;
float draw1, draw2;

Servo servoLeft;            // create servo object to control a servo
Servo servoRight;            // create servo object to control a servo
const byte servoLeftPin = 9;
const byte servoRightPin = 10;
float angle;
float smoothed = 90.0;
unsigned long time = 0;

short loopcount = 0;
short lastloopcount = 0;

// ---------------------------------------------------------------- //

void setup() {
  Serial.begin(9600);
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);
  servoLeft.write(smoothed);
  servoRight.write(smoothed);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();  // Clear the buffer. init done.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // # of chars:  "12345678901234567890"
  display.println("  Ultrasonic Ranges ");
  display.setTextSize(3);
  // # of chars:  "1234567"
  display.println("  O W  ");
  display.display();
  delay(4000);
}

// ---------------------------------------------------------------- //

void loop() {
  if( millis() - time > 1000 ) {
    time = millis();
    lastloopcount = loopcount;
    loopcount = 1;
  } else {
    loopcount++;
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  distance1 = updatedistance(distance1, ultrasonic1.Ranging(CM));
  distance2 = updatedistance(distance2, ultrasonic2.Ranging(CM));
  angle = 90 - atan((distance1 - distance2)/9)*180/PI;  // the 12.8 cm refers to the distance between the range finders
  angle = max(angle,0);
  angle = min(angle,180);
  smoothed = (smoothed*14 + angle)/15;
  servoLeft.write(smoothed);

  // Draw Range 1  
  draw1 = distance1 * 13 / 200; // mapping 200 cm to max 17 chars on the OLED screen
  display.print("r1:");
  display.println(distance1);
  display.print("r1:");
  for (int i=0; i < draw1; i++) {
    display.print("-");
  }
  display.println("|");
  
  // Draw Range 2
  draw2 = distance2 * 13 / 200; // mapping 200 cm to max 17 chars on the OLED screen
  display.print("r2:");
  display.println(distance2);
  display.print("r2:");
  for (int i=0; i < draw2; i++) {
    display.print("-");
  }
  display.println("|");

  display.setCursor(100,0);
  display.print(lastloopcount);
  display.print("/s");

  display.setCursor(100,8);
  display.print(angle-90);
  display.setCursor(100,16);
  display.print(smoothed-90);
  display.setCursor(100,24);
  display.print("Hi");
  
  display.display();  
}

// ---------------------------------------------------------------- //

float updatedistance(float prevdistance, float newreading)
{
  if (newreading < 2) {
    return(prevdistance);
  } else if (newreading > 200) {
    return(min(200,prevdistance+10));  
  }
  return(newreading);
}


