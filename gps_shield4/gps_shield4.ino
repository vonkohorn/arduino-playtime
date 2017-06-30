
#include "string.h"
#include "ctype.h"
#include "SoftwareSerial.h"
#include "dGPS.h"  // dGPS library from Dexter Industries - http://dexterindustries.com/Arduino-GPS_Shield.html


// Software serial TX & RX Pins for the GPS module
// Initiate the software serial connection

int ledPin = 13;                  // LED test pin
double desLat = 42.605669;              // Destination Latitude filled by user in Serial Monitor Box
double desLon = -71.582613;              // Destination Longitude filled by user in Serial Monitor Box
dGPS dgps = dGPS();               // Construct dGPS class


void setup() {
  pinMode(ledPin, OUTPUT);       // Initialize LED pin
  Serial.end();                  // Close any previously established connections
  Serial.begin(115200);            // Serial output back to computer.  On.
  dgps.init();                   // Run initialization routine for dGPS.
  delay(1000);  
  
  Serial.println("Navigate Home!");
  Serial.print("Destination Latitude (in degrees): "); Serial.println(desLat);
  Serial.print("Destination Longitude (in degrees): "); Serial.println(desLon);  
}

void loop() {
  
  dgps.update(desLat, desLon);    // Calling this updates the GPS data.  The data in dGPS variables stays the same unless
                                  // this function is called.  When this function is called, the data is updated.

  Serial.print("UTC Date(DDMMYY) & Time: ");
  Serial.print(dgps.Date());    // UTC date.  Date is in format:  DDMMYY (D - Day; M - Month; Y-Year)
  Serial.print(", ");
  Serial.println(dgps.Time() - 40000);    // .Time returns the UTC time (GMT) in HHMMSS, 24 huor format (H-Hour; M-Minute; S-Second)
  
  Serial.print("Status: ");
  Serial.println(dgps.Status());  // A - Satellites acquired and a valid signal.  V - No sats and not a valid signal.
  
  Serial.print("Latitude: ");
  Serial.print(dgps.Lat(), 6);    // Lattitude - in DD.MMSSSS format (decimal-degrees format)  (D-Degree; M-Minute; S-Second)
  Serial.println(" degrees");
  
  Serial.print("Longitude: ");
  Serial.print(dgps.Lon(), 6);    // Longitude - in DD.MMSSSS format (decimal-degrees format)  (D-Degree; M-Minute; S-Second)
  Serial.println(" degrees");
  
  Serial.print("Velocity: ");
  Serial.print(dgps.Vel(), 6);    // Velocity, in knots.
  Serial.println(" knots");
  
  Serial.print("Heading: ");
  Serial.print(dgps.Head(), 6);   // Heading, in degrees
  Serial.println(" degrees");
  
  Serial.print("Distance to destination: ");
  Serial.print(dgps.Dist());      // The distance to the destination in kilometers. Correct upto 2 decimal points. Radius of Earth taken as 6,378.1 kilometers
  Serial.println(" kilometers");
  
  Serial.print("Azimuth to destination: "); 
  Serial.print(dgps.Azim());      //Azimuth of the destination coordinates from the current location in degrees. Correct upto 2 decimal points
  Serial.println(" degrees");
         
  Serial.println(""); 
}
