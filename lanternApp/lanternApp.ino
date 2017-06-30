/*
  App to control the schoolhouse's lanterns along the brick path

  Rest API controls a stepper motor to flip the physical light switch

  uses the Bridge library to access the digital and
  analog pins on the board through REST calls.
  create API for REST calls through the browser.

  Commands created:

  "/arduino/lantern/0"     -> rotate the stepper motor once cw
  "/arduino/lantern/1"     -> rotate the stepper motor once ccw
  "/arduino/digital/13"     -> digitalRead(13)
  "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
  "/arduino/analog/2/123"   -> analogWrite(2, 123)
  "/arduino/analog/2"       -> analogRead(2)
  "/arduino/mode/13/input"  -> pinMode(13, INPUT)
  "/arduino/mode/13/output" -> pinMode(13, OUTPUT)
*/

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>

// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
BridgeServer server;

byte ledPin = 13;
unsigned long time = 0;  
unsigned long reTime = 0;  

#include <AccelStepper.h>
#define HALFSTEP 8

// motor pins
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

// Rotary Encoder
volatile boolean TurnDetected;
volatile boolean up;

const int PinCLK = 2;                   // Used for generating interrupts using CLK signal
const int PinDT = 3;                    // Used for reading DT signal
const int PinSW = 4;                    // Used for the push button switch

void isr ()  {                    // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
 digitalRead(PinCLK) ? up = digitalRead(PinDT) : up = !digitalRead(PinDT);
 TurnDetected = true;
}

// ---------- // 

void setup() {
  // Bridge startup
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Bridge.begin();
  digitalWrite(ledPin, HIGH);

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

  // Rotary Encoder
  pinMode(PinCLK,INPUT);
  pinMode(PinDT,INPUT);  
  pinMode(PinSW,INPUT);
  attachInterrupt (digitalPinToInterrupt(PinCLK),isr,FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO

  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(2000.0);
  stepper.setCurrentPosition(0);
}

void loop() {
  if (TurnDetected && (millis() - reTime > 10))  {        // do this only if rotation was detected && debounce
    stepper.move(up?40:-40);                             // 4096 = 1 full rotation
    TurnDetected = false;                              // do NOT repeat IF loop until new rotation detected
    reTime = millis();
  }
  
  if( millis() - time > 500 ) {
    BridgeClient client = server.accept();    // Get clients coming from server
    if (client) {       // Is there a new client?
      process(client);  // Process request
      client.stop();    // Close connection and free resources.
    }
  }
  if (stepper.distanceToGo() == 0) {
    stepper.disableOutputs();
  } else {
    if (!stepper.isRunning()) 
      { stepper.enableOutputs(); } // only enableOutputs if the stepper is not already running
    stepper.run();
  }
}

// ---------- // 

void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "lantern" command?
  if (command == "lantern") {
    lanternCommand(client);
  }

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }

  // is "analog" command?
  if (command == "analog") {
    analogCommand(client);
  }

  // is "mode" command?
  if (command == "mode") {
    modeCommand(client);
  }
}

// ---------- // 

void lanternCommand(BridgeClient client) {
  int c = client.parseInt();; // 1=on, 0=off

  if (c == 1) {
    stepper.move(-2048);        // 4096 = 1 full rotation
    client.print("Turning on.");
  } else {
    stepper.move(2048);       // 4096 = 1 full rotation
    client.print("Turning off.");
  }
}

// --------------------------------------------------------------- // 

void digitalCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  } else {
    value = digitalRead(pin);
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  // Update datastore key with the current pin value
  String key = "D";
  key += pin;
  Bridge.put(key, String(value));
}

void analogCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/analog/5/120"
  if (client.read() == '/') {
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value);

    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "D";
    key += pin;
    Bridge.put(key, String(value));
  } else {
    // Read analog pin
    value = analogRead(pin);

    // Send feedback to client
    client.print(F("Pin A"));
    client.print(pin);
    client.print(F(" reads analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "A";
    key += pin;
    Bridge.put(key, String(value));
  }
}

void modeCommand(BridgeClient client) {
  int pin;

  // Read pin number
  pin = client.parseInt();

  // If the next character is not a '/' we have a malformed URL
  if (client.read() != '/') {
    client.println(F("error"));
    return;
  }

  String mode = client.readStringUntil('\r');

  if (mode == "input") {
    pinMode(pin, INPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as INPUT!"));
    return;
  }

  if (mode == "output") {
    pinMode(pin, OUTPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as OUTPUT!"));
    return;
  }

  client.print(F("error: invalid mode "));
  client.print(mode);
}
