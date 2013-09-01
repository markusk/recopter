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


// a maximum of eight servo objects can be created!
//
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
Servo myservo3;  // create servo object to control a servo > not used, eyebrow
Servo myservo4;  // create servo object to control a servo 
Servo myservo5;  // create servo object to control a servo 
Servo myservo6;  // create servo object to control a servo > not used, eyebrow 

int i = 0;    // variable to store the servo position 
int pause = 250;  // for delay in ms

// servo 1
// right eye
// left/right (looking _from_ head head)
static const int servo1pin      =   5;
static const int servo1start    =  55;    // left     55 ??? left eye from head?!? wtf?
static const int servo1default  = 120;    // neutral 120
static const int servo1end      = 180;    // right   180

// servo 2
// right eye
// up/down
static const int servo2pin      =   3;
static const int servo2start    =  55;    // down     36
static const int servo2default  =  80;    // neutral  80
static const int servo2end      = 124;    // up      124

/* servo 3 >>>>>>>>>> not used
// right eyebrow
// left/right
static const int servo3pin      =   6;
static const int servo3start    =  50;    // right    50
static const int servo3default  = 100;    // neutral 100
static const int servo3end      = 136;    // left    136 */

// servo 4
// left eye
// left/right (looking _from_ head head)
static const int servo4pin      =   9;
static const int servo4start    =  30;    // left     30
static const int servo4default  = 100;    // neutral 100
static const int servo4end      = 155;    // right   155

// servo 5
// left eye
// up/down
static const int servo5pin      =   6;
static const int servo5start    =  55;    // down     36
static const int servo5default  =  80;    // neutral  80
static const int servo5end      = 124;    // up      124

/* servo 6 >>>>>>>>>> not used
// left eyebrow
// left/right
static const int servo6pin      =  11;
static const int servo6start    =  42;    // right    42
static const int servo6default  =  87;    // neutral  87
static const int servo6end      = 132;    // left    132 */

//! the possible eyes
static const unsigned char LEFTEYE  = 1;
static const unsigned char RIGHTEYE = 2;

//! the possible eyebrows
static const unsigned char LEFTBROW  = 1;
static const unsigned char RIGHTBROW = 2;

//! the possible servo data
static const unsigned char SVSTART   = 0;
static const unsigned char SVEND     = 1;
static const unsigned char SVDEFAULT = 2;
static const unsigned char SVCURRENT = 3;
static const unsigned char SVMIN     = 4;
static const unsigned char SVMAX     = 5;

//! the servo numbers
// +++ do not play around carelessly with these numbers, since we use them later in the eyeRollPos array +++
static const unsigned char SERVO1 = 0;
static const unsigned char SERVO2 = 1;
static const unsigned char SERVO3 = 2;
static const unsigned char SERVO4 = 3;
static const unsigned char SERVO5 = 4;
static const unsigned char SERVO6 = 5;

//! the head directions
static const unsigned char UP         =  0;
static const unsigned char UPLEFT     =  1;
static const unsigned char UPRIGHT    =  2;
static const unsigned char DOWN       =  3;
static const unsigned char DOWNLEFT   =  4;
static const unsigned char DOWNRIGHT  =  5;
static const unsigned char LEFT       =  6;
static const unsigned char RIGHT      =  7;
static const unsigned char FORWARD    =  8;
static const unsigned char NORMAL     =  9; // eyebrow
static const unsigned char CURIOUS    = 10;
static const unsigned char ANGRY      = 11;



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
  // servo init
  //
  myservo1.attach(servo1pin);  // attaches the servo on pin 3 to the servo object 
  myservo2.attach(servo2pin);  // attaches the servo on pin 9 to the servo object 
//  myservo3.attach(servo3pin);  // attaches the servo on pin 9 to the servo object 
  myservo4.attach(servo4pin);  // attaches the servo on pin 9 to the servo object 
  myservo5.attach(servo5pin);  // attaches the servo on pin 9 to the servo object 
//  myservo6.attach(servo6pin);  // attaches the servo on pin 9 to the servo object 

//  digitalWrite(led, HIGH);   // turn the LED on (HIGH)

//  look(FORWARD); < < < 
  delay(500);
}


void loop()
{
  // read PPM signals from RC receiver
  value = pulseIn(rcPinEyesLeftRight, INPUT);

  // map read values to servo compatible values
  ServoValue = map(value, 17927, 18725, 0, 255);


  
//  Serial.print("pulseIn: ");
//  Serial.println(value);
//  Serial.println(ServoValue);
//  Serial.println("----------");
//  delay(500);               // wait some time
}


