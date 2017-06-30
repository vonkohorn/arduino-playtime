
/************************************************************************/
// Use SPI interface to talk to MPU9250
// Arduino Nano v3.0 version
/************************************************************************/

#include <SPI.h>
#include <Wire.h>

/************************************************************************/

#define NCS_PIN   10
#define MOSI_PIN  11
#define MISO_PIN  12
#define SCK_PIN   13

/************************************************************************/

const int NCS = NCS_PIN;

/************************************************************************/

uint8_t SPI_read_register( uint8_t reg )
{
  digitalWrite( NCS, LOW);
  SPI.transfer( reg | 0x80 ); // reg | 0x80 to denote read
  uint8_t read_value = SPI.transfer( 0x00 ); // write 8-bits zero
  digitalWrite( NCS, HIGH);
  return read_value;
}

/************************************************************************/

void SPI_write_register( uint8_t reg, uint8_t value )
{
  digitalWrite( NCS, LOW);
  SPI.transfer( reg );
  SPI.transfer( value );
  digitalWrite( NCS, HIGH);
}

/************************************************************************/

void setup()
{
  byte id;
  
  Serial.begin( 115200 );
  
  pinMode( NCS_PIN, OUTPUT );
  pinMode( MOSI_PIN, OUTPUT );
  pinMode( MISO_PIN, INPUT );
  pinMode( SCK_PIN, OUTPUT );

  SPI.begin( );
  SPI.setDataMode( SPI_MODE0 );
  SPI.setBitOrder( MSBFIRST );
  SPI.setClockDivider( 16 ); // 1MHz
  digitalWrite(NCS, HIGH);
  delay( 1000 );

  Serial.println( "MPU9250 SPI" );

  // reset the device
  SPI_write_register( 0x6B, 0x80 );
  delay( 100 );

  // disable I2C protocol
  SPI_write_register( 0x6A, 0x10 );
  delay( 100 );

  // reset acc, gyro and temp
  SPI_write_register( 0x68, 0x07 );
  delay( 100 );

  if(SPI_read_register(0x75) == 0x71) {
      Serial.println("Good to GO");
    } else {
      Serial.println("No connection");
    }
  delay( 100 );
}

/************************************************************************/

void loop()
{
  uint8_t id = SPI_read_register( 0x75 );
  Serial.println( id );
  delay(1000);
}

/************************************************************************/


