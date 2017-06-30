
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

float signal1 = 0;  // to be shown as a line graph
float signal2 = 333.333;  // to be shown as a line graph
float signal3 = 666.666;  // to be shown as a line graph
float signal4 = 1000;  // to be shown as a line graph

void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();  // Clear the buffer.
  // init done
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ultrasonic Ranges");
  display.println("4 sensors, r1-r4");
  display.display();
  delay(2000);
}


void loop() {
  float meter1 = map(signal1,0,1000,0,17);
  float meter2 = map(signal2,0,1000,0,17);
  float meter3 = map(signal3,0,1000,0,17);
  float meter4 = map(signal4,0,1000,0,17);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.print("r1:");
  for (int i=0; i < meter1; i++) {
    display.print("-");
  }
  display.println("|");

  display.print("r2:");
  for (int i=0; i < meter2; i++) {
    display.print("-");
  }
  display.println("|");

  display.print("r3:");
  for (int i=0; i < meter3; i++) {
    display.print("-");
  }
  display.println("|");

  display.print("r4:");
  for (int i=0; i < meter4; i++) {
    display.print("-");
  }
  display.println("|");

  display.display();
  delay(1000);
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}


