
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

const byte servo1pin = 9;
const byte servo2pin = 10;
const byte pot1pin = 0;
const byte pot2pin = 1;

unsigned long time = 0;
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

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
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
  if( millis() - time > 1000 ) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("pot1:");
    display.println(pot1);
    display.print("pos1:");
    display.println(pos1);
    display.setCursor(84,0);
    display.print(lastloopcount);
    display.print("/s");
    display.display();  

    time = millis();
    lastloopcount = loopcount;
    loopcount = 1;
  } else {
    loopcount++;
  }
  
  pot1 = analogRead(pot1pin);  
  pos1 = map(pot1,0,1023,0,179); // map pot range to servo range of 0-179
  servo1.write(pos1);
  servo2.write(pos1);

}


