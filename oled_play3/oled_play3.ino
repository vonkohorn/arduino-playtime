
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

float distance1, distance2;
float draw1, draw2;

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
  display.println("  Ultrasonic Ranges ");
  display.setTextSize(2);
  // # of chars:  "1234567890"
  display.println("    O W   ");
  display.setTextSize(1);
  // # of chars:  "12345678901234567890"
  display.println("    FutureForest    ");
  display.display();
  delay(2000);
}

// ---------------------------------------------------------------- //

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  // Range 1
  distance1 = updatedistance(distance1, ultrasonic1.Ranging(CM));
  draw1 = distance1 * 17 / 200; // mapping 200 cm to max 17 chars on the OLED screen
  
  display.print("r1: ");
  display.println(distance1);
  display.print("r1:");
  for (int i=0; i < draw1; i++) {
    display.print("-");
  }
  display.println("|");
  
  // Range 2
  distance2 = updatedistance(distance2, ultrasonic2.Ranging(CM));
  draw2 = distance2 * 17 / 200; // mapping 200 cm to max 17 chars on the OLED screen

  display.print("r2: ");
  display.println(distance2);
  display.print("r2:");
  for (int i=0; i < draw2; i++) {
    display.print("-");
  }
  display.println("|");


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


void testdrawchar(void) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    delay(500);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}


