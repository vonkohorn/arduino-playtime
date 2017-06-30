
#include <SoftwareSerial.h>

// setup gps serial
int gpsTxPin = 18;
int gpsRxPin = 19;
SoftwareSerial gpsSerial(gpsTxPin, gpsRxPin);

void setup()
{
  Serial.begin(115200);  //set monitor to 9600
 
  gpsSerial.begin(9600); //adjust for GPS unit

  Serial.println("Ready!");
}

void loop()
{
  Serial.println(gpsSerial.available());
  while(gpsSerial.available())
  {
    char c = gpsSerial.read();
    Serial.print(c);
  }
  delay(1000);
}
