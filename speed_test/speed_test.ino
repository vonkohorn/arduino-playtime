
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Ultrasonic ultrasonic1(12,8); // trig, echo
float distance;

unsigned long time = 0;

short loopcount = 0;
short lastloopcount = 0;



void setup() {
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();  // Clear the buffer. init done.
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // # of chars:  "12345678901234567890"
  display.println("Speed test");
  display.setTextSize(3);
  // # of chars:  "1234567"
  display.println("  O W  ");
  display.display();
  delay(2000);
}

void loop() {
  if( millis() - time > 1000 ) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(loopcount);
    display.println(" loops / sec");
    display.display();
    loopcount = 1;
    time = millis();
  } else {
    loopcount++;
  }
  // nothing but the counting
  
}
