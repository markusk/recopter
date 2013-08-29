#include <Servo.h> 

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

//
// Graupner stuff
//
int rcPinEyesLeftRight = 8;  //  pin from RC receiver
int rcPinEyesUpDown    = 7;  //  pin from RC receiver
int rcPinSpeech        = 4;  //  pin from RC receiver
int rcPinMusic         = 2;  //  pin from RC receiver

int rcRegler = 6;  //  pin from RC receiver (Drehregler)

int ServoValue = 0;

int value = 0;

//
// The servos
//
Servo servoLeftUpDown;  // create servo object to control a servo 
Servo servoLeftLeftRight;
Servo servoRightUpDown;
Servo servoRightLeftRight;


void setup()
{
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  //
  // pin init
  //
  // pins which get signal from RC reciever
  pinMode(rcPinEyesLeftRight, INPUT);
  pinMode(rcPinEyesUpDown, INPUT);
  pinMode(rcPinSpeech, INPUT);
  pinMode(rcPinMusic, INPUT);

  pinMode(rcRegler, INPUT);


  //
  // Servo init
  //
  servoLeftUpDown.attach(3); // attach servo to this pin
  servoLeftUpDown.write(80); // default position

  servoLeftLeftRight.attach(5);
  servoLeftLeftRight.write(120);

  servoRightUpDown.attach(6);
  servoRightUpDown.write(80);

  servoRightLeftRight.attach(9);
  servoRightLeftRight.write(100);
}


void loop()
{
  value = pulseIn(rcPinEyesLeftRight, INPUT);
  
  
  if (value < 18600) // <18600 = switch down  >18600 = switch up
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH)
  }
  else
  {
    digitalWrite(led, LOW);    // turn the LED off (LOW)
  }

  // Drehregler auslesen
  value = pulseIn(rcRegler, INPUT);
  
  // map read values to servo compatible
  ServoValue = map(value, 17927, 18725, 0, 255);

  // sets the servo position according to the scaled value
//  servoLeftUpDown.write(ServoValue);

  
//  Serial.print("pulseIn: ");
//  Serial.println(value);
//  Serial.println(ServoValue);
//  Serial.println("----------");
//  delay(500);               // wait some time
}

