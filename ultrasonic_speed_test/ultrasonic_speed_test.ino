
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Ultrasonic.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Ultrasonic ultrasonic1(12,8); // trig, echo
Ultrasonic ultrasonic2(6,5);  // trig, echo

float distance;
unsigned long time = 0;

short loopcount = 0;


// ---------------------------------------------------------------- //

void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();  // Clear the buffer. init done.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // # of chars:  "12345678901234567890"
  display.println("Ultrasonic Range");
  display.println("Speed Test");
  display.println("");
  display.println("       ~FutureForest");
  display.display();
  delay(3000);
}

// ---------------------------------------------------------------- //

void loop() {
  if( millis() - time > 1000 ) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(loopcount);
    display.println(" updates / sec");
    display.print(distance);
    display.print(" cm");
    display.display();
    loopcount = 1;
    time = millis();
  } else {
    loopcount++;
  }
  distance = updatedistance(distance, ultrasonic1.Ranging(CM));
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

