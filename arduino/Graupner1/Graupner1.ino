#include <Servo.h> 

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;
int relais = 12;

//
// Graupner stuff
//
int rcPinLeftUpDown     = 8;  //  pin from RC receiver
int rcPinLeftLeftRight  = 7;  //  pin from RC receiver
int rcPinRightUpDown    = 4;  //  pin from RC receiver
int rcPinRightLeftRight = 2;  //  pin from RC receiver

int rcRegler = 6;  //  pin from RC receiver (Drehregler)

int ServoValue = 0;

int value = 0;

//
// The servos
//
Servo servoLeftUpDown;  // create servo object to control a servo 


void setup()
{
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  // pins which get signal from RC reciever
  pinMode(rcPinLeftUpDown, INPUT);
  pinMode(rcPinLeftLeftRight, INPUT);
  pinMode(rcPinRightUpDown, INPUT);
  pinMode(rcPinRightLeftRight, INPUT);

  pinMode(rcRegler, INPUT);

  // servo left eye, up/down
  servoLeftUpDown.attach(3);  // attaches the servo on this pin to the servo object 
  servoLeftUpDown.write(80); // default position
}


void loop()
{
  value = pulseIn(rcPinLeftUpDown, INPUT);
  
  
  if (value < 18600) // <18600 = switch down  >18600 = switch up
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH)
    digitalWrite(relais, HIGH);   // turn the LED on (HIGH)
  }
  else
  {
    digitalWrite(led, LOW);    // turn the LED off (LOW)
    digitalWrite(relais, LOW);    // turn the LED off (LOW)
  }

  // Drehregler auslesen
  value = pulseIn(rcRegler, INPUT);
  
  // map read values to servo compatible
  ServoValue = map(value, 17927, 18725, 0, 255);

  // sets the servo position according to the scaled value
//  servoLeftUpDown.write(ServoValue);

  
  Serial.print("pulseIn: ");
  Serial.println(value);
//  Serial.println(ServoValue);
  Serial.println("----------");
  delay(500);               // wait some time
}

