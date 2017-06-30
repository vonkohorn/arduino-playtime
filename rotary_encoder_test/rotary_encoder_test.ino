
volatile boolean TurnDetected;
volatile boolean up;

const int PinCLK=2;                   // Used for generating interrupts using CLK signal
const int PinDT=3;                    // Used for reading DT signal
const int PinSW=4;                    // Used for the push button switch
unsigned long reTime = 0;  

long pos=0;    // without STATIC it does not count correctly!!!

void isr ()  {                    // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
 digitalRead(PinCLK) ? up = digitalRead(PinDT) : up = !digitalRead(PinDT);
 TurnDetected = true;
}


void setup ()  {
 pinMode(PinCLK,INPUT);
 pinMode(PinDT,INPUT);  
 pinMode(PinSW,INPUT);
 attachInterrupt (digitalPinToInterrupt(PinCLK),isr,FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO
 Serial.begin (115200);
 Serial.println("Start");
}

void loop ()  {
 if (TurnDetected && (millis() - reTime > 10))  {        // do this only if rotation was detected
   up ? pos++ : pos--;
   TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
   reTime = millis();
   Serial.print ("pos = ");  
   Serial.println (pos);
 }
}

