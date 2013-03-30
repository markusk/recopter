#include <Servo.h> 


// a maximum of eight servo objects can be created!
//
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
Servo myservo3;  // create servo object to control a servo 
Servo myservo4;  // create servo object to control a servo 
Servo myservo5;  // create servo object to control a servo 
Servo myservo6;  // create servo object to control a servo 
 
int s1 = 0;    // variable to store the servo position 

// servo 1
// right eye
// left/right (looking _to_ head head)
static const int servo1pin      =   3;
static const int servo1start    =  40;    // left     40
static const int servo1default  =  74;    // neutral  74
static const int servo1end      = 110;    // right   110

// servo 2
// right eye
// up/down
static const int servo2pin      =   5;
static const int servo2start    =  36;    // up       36
static const int servo2default  =  70;    // neutral  70
static const int servo2end      = 124;    // down    124

// servo 3
// right eyebrow
// left/right
static const int servo3pin      =   6;
static const int servo3start    =  50;    // right    50
static const int servo3default  = 100;    // neutral 100
static const int servo3end      = 136;    // left    136

// servo 4
// left eye
// left/right (looking _to_ head head)
static const int servo4pin      =   9;
static const int servo4start    =  30;    // left     30
static const int servo4default  =  74;    // neutral  74
static const int servo4end      = 110;    // right   110

// servo 5
// left eye
// up/down
static const int servo5pin      =  10;
static const int servo5start    =  36;    // up       36
static const int servo5default  =  66;    // neutral  66
static const int servo5end      = 124;    // down    124

// servo 6
// left eyebrow
// left/right
static const int servo6pin      =  11;
static const int servo6start    =  42;    // right    42
static const int servo6default  =  87;    // neutral  87
static const int servo6end      = 132;    // left    132

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
static const unsigned char SERVO1 = 0;
static const unsigned char SERVO2 = 1;
static const unsigned char SERVO3 = 2;
static const unsigned char SERVO4 = 3;
static const unsigned char SERVO5 = 4;
static const unsigned char SERVO6 = 5;



 
void setup() 
{ 
  myservo1.attach(servo1pin);  // attaches the servo on pin 3 to the servo object 
  myservo2.attach(servo2pin);  // attaches the servo on pin 9 to the servo object 
  myservo3.attach(servo3pin);  // attaches the servo on pin 9 to the servo object 
  myservo4.attach(servo4pin);  // attaches the servo on pin 9 to the servo object 
  myservo5.attach(servo5pin);  // attaches the servo on pin 9 to the servo object 
  myservo6.attach(servo6pin);  // attaches the servo on pin 9 to the servo object 

  // move servos to thier default positions
  myservo1.write(servo1default); 
  myservo2.write(servo2default); 
  myservo3.write(servo3default); 
  myservo4.write(servo4default); 
  myservo5.write(servo5default); 
  myservo6.write(servo6default); 
} 
 

void loop() 
{ 
/*
  for(s1 = servo1start; s1 < servo1end; s1 += 1)
  {
    moveServo(SERVO1, s1);
    delay(15);            // waits 15ms for the servo to reach the position 
  } 

  for(s1 = servo1end; s1 > servo1start; s1 -= 1)
  {
    moveServo(SERVO1, s1);
    delay(15);            // waits 15ms for the servo to reach the position 
  } 
*/
} 




void moveServo(unsigned char servo, unsigned char position)
{
  switch (servo)
  {
    case SERVO1:
      myservo1.write(position);
      break; 
  }
}

