#include <Servo.h> 


// a maximum of eight servo objects can be created!
//
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
Servo myservo3;  // create servo object to control a servo 
Servo myservo4;  // create servo object to control a servo 
Servo myservo5;  // create servo object to control a servo 
Servo myservo6;  // create servo object to control a servo 
 
int pos = 0;    // variable to store the servo position 

// servo 1    okay
// right eye
// left/right (looking _to_ head head)
const int servo1pin      =   3;
const int servo1start    =  40;    // left     40
const int servo1default  =  74;    // neutral  74
const int servo1end      = 110;    // right   110

// servo 2    okay
// right eye
// up/down
const int servo2pin      =   5;
const int servo2start    =  36;    // up       36
const int servo2default  =  66;    // neutral  66
const int servo2end      = 124;    // down    124

// servo 3    okay
// right eyebrow
// left/right
const int servo3pin      =   6;
const int servo3start    =  50;    // right    50
const int servo3default  = 100;    // neutral 100
const int servo3end      = 136;    // left    136

// servo 4    okay
// left eye
// left/right (looking _to_ head head)
const int servo4pin      =   9;
const int servo4start    =  30;    // left     30
const int servo4default  =  74;    // neutral  74
const int servo4end      = 110;    // right   110

// servo 5    okay
// left eye
// up/down
const int servo5pin      =  10;
const int servo5start    =  36;    // up       36
const int servo5default  =  66;    // neutral  66
const int servo5end      = 124;    // down    124

// servo 6    okay
// left eyebrow
// left/right
const int servo6pin      =  11;
const int servo6start    =  42;    // right    42
const int servo6default  =  87;    // neutral  87
const int servo6end      = 132;    // left    132

 
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
  for(pos = servo1start; pos < servo1end; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = servo1end; pos > servo1start; pos -= 1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 


  for(pos = servo2start; pos < servo2end; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = servo2end; pos > servo2start; pos -= 1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
 */
} 

