#include <Servo.h>   // Servo
#include <Wire.>"    // I2C

#define RASPI_I2CADDR 0x77



// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

//
// Graupner stuff
//
int rcPinEyesLeftRight = 8;  //  pin from RC receiver
int rcPinEyesUpDown    = 7;  //  pin from RC receiver
int rcPinSpeech        = 4;  //  pin from RC receiver
int rcPinMusic         = 2;  //  pin from RC receiver

int servoLeftValue  = 110;
int servoRightValue = 140;

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
static const unsigned char CURIOUS    = 10; // eyebrow
static const unsigned char ANGRY      = 11; // eyebrow



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

  look(FORWARD);
  delay(500);
}


void loop()
{
  //
  // look LEFT, RIGHT, NORMAL
  //
  // read PPM signals from RC receiver
  value = pulseIn(rcPinEyesLeftRight, HIGH);

  // map read values to servo compatible values
  ServoValue = map(value, 1089, 1880, 0, 255);

/*
  Serial.print("pulseIn rcPinEyesLeftRight: ");
  Serial.println(value);
  Serial.print("mapped to ServoValue: ");
  Serial.println(ServoValue);
  Serial.println("----------");
//      delay(500);               // wait some time
*/

  if (ServoValue < servoLeftValue)
  {
    look(LEFT);
  }
  else
  {
    if (ServoValue > servoRightValue)
    {
      look(RIGHT);
    }
    else
    {
      look(FORWARD);
    }
  }


  //
  // look UP, DOWN, NORMAL?
  //
  // read PPM signals from RC receiver
  value = pulseIn(rcPinEyesUpDown, HIGH);

  // map read values to servo compatible values
  ServoValue = map(value, 1089, 1880, 0, 255);

  if (ServoValue < servoLeftValue)
  {
    look(DOWN);
  }
  else
  {
    if (ServoValue > servoRightValue)
    {
      look(UP);
    }
    else
    {
      look(FORWARD); // collides with look FORWARD, when looking left or right! @todo: think about alternative. e.g. look MIDDLE
    }
  }

}



void look(unsigned char direction)
{
  	if (direction == UP)
	{
		
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == UPLEFT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == UPRIGHT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
		
	if (direction == DOWN)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == DOWNLEFT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == DOWNRIGHT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == LEFT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == RIGHT)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == FORWARD)
	{
		eye(LEFTEYE, direction);
		eye(RIGHTEYE, direction);
		return;
	}
	
	if (direction == NORMAL)
	{
//		eyebrow(LEFTBROW, direction);
//		eyebrow(RIGHTBROW, direction);
		return;
	}
	
	if (direction == CURIOUS)
	{
//		eyebrow(LEFTBROW, UP);
//		eyebrow(RIGHTBROW, UP);
		return;
	}
	
	if (direction == ANGRY)
	{
//		eyebrow(LEFTBROW, DOWN);
//		eyebrow(RIGHTBROW, DOWN);
		return;
	}
}



void eye(unsigned char whichEye, unsigned char direction)
{
  // move servo to the start or end position (*not* to the min or max posisiotns!)
  if (direction == UP)
  {
    if (whichEye==LEFTEYE)
    {
      // up
      moveServo(SERVO2, servo2end);
      // default
      moveServo(SERVO1, servo1default);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // up
      moveServo(SERVO5, servo5end);
      // default
      moveServo( SERVO4, servo4default);
      return;
    }
    return;
  }

  if (direction == UPLEFT)
  {
    if (whichEye==LEFTEYE)
    {
      // up
      moveServo(SERVO2, servo2end);
      //left
      moveServo(SERVO4, servo4start);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // up
      moveServo(SERVO5, servo5end);
      // left
      moveServo(SERVO1, servo1start);
      return;
    }
    return;
  }

  if (direction == UPRIGHT)
  {
    if (whichEye==LEFTEYE)
    {
      // right
      moveServo(SERVO4, servo4end);
      // up
      moveServo(SERVO2, servo2end);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // up
      moveServo(SERVO5, servo5end);
      // right
      moveServo(SERVO1, servo1end);
      return;
    }
    return;
  }

  // move servo to the start or end position (*not* to the min or max posisiotns!)
  if (direction == DOWN)
  {
    if (whichEye==LEFTEYE)
    {
      // down
      moveServo(SERVO2, servo2start);
      // default
      moveServo( SERVO1, servo1default);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // down
      moveServo(SERVO5, servo5start);
      // default
      moveServo(SERVO4, servo4default);
      return;
    }
    return;
  }

  if (direction == DOWNLEFT)
  {
    if (whichEye==LEFTEYE)
    {
      // down
      moveServo(SERVO2, servo2start);
      // left
      moveServo(SERVO4, servo4start);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // down
      moveServo(SERVO5, servo5start);
      // left
      moveServo(SERVO1, servo1start);
      return;
    }
    return;
  }

  if (direction == DOWNRIGHT)
  {
    if (whichEye==LEFTEYE)
    {
      // down
      moveServo(SERVO2, servo2start);
      // right
      moveServo(SERVO4, servo4end);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // down
      moveServo(SERVO5, servo5start);
      // right
      moveServo(SERVO1, servo1end);
      return;
    }
    return;
  }

  // move servo to the start or end position (*not* to the min or max posisiotns!)
  if (direction == LEFT)
  {
    if (whichEye==LEFTEYE)
    {
      // left
      moveServo(SERVO4, servo4start);
      // default
      moveServo(SERVO2, servo2default);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // left
      moveServo(SERVO1, servo1start);
      // default
      moveServo(SERVO5, servo5default);
      return;
    }
    return;
  }

/*
  // move servo to its maximum end position
  if (direction == LEFTMAX)
  {
    if (whichEye==LEFTEYE)
    {
      // 
      moveServo(SERVO4, servo4start); // min
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // 
      moveServo(SERVO1, servo1start); // min
      return;
    }
    return;
  }
*/

  // move servo to the start or end position (*not* to the min or max posisiotns!)
  if (direction == RIGHT)
  {
    //qDebug("right");
    if (whichEye==LEFTEYE)
    {
      // right
      moveServo(SERVO4, servo4end); // end
      // default
      moveServo(SERVO2, servo2default);
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      // right
      moveServo(SERVO1, servo1end); // end
      // default
      moveServo(SERVO5, servo5default);
      return;
    }
    return;
  }
  
/*
  // move servo to its maximum end position
  if (direction == RIGHTMAX)
  {
    if (whichEye==LEFTEYE)
    {
      moveServo(SERVO4, servo4end); // max
      return;
    }

    if (whichEye==RIGHTEYE)
    {
      moveServo(SERVO1, servo1end); // max
      return;
    }
    return;
  }
*/

  if (direction == FORWARD)
  {
    moveServo(SERVO1, servo1default);
    moveServo(SERVO2, servo2default);

    moveServo(SERVO4, servo4default);
    moveServo(SERVO5, servo5default);
    return;
  }
}


void eyebrow(unsigned char whichBrow, unsigned char direction)
{
/*
  	if (direction == NORMAL)
	{
		if (whichBrow==LEFTBROW)
		{
			// default pos
			moveServo(SERVO3, servo3default);
			return;
		}

		if (whichBrow==RIGHTBROW)
		{
			// default pos
			moveServo(SERVO6, servo6default);
			return;
		}
		return;
	}

	if (direction == UP)
	{
		if (whichBrow==LEFTBROW)
		{
			// inside up
			moveServo(SERVO3, servo3end);
			return;
		}

		if (whichBrow==RIGHTBROW)
		{
			// inside up
			moveServo(SERVO6, servo6start);
			return;
		}
		return;
	}
	
	if (direction == DOWN)
	{
		if (whichBrow==LEFTBROW)
		{
			// inside down
			moveServo(SERVO3, servo3start);
			return;
		}

		if (whichBrow==RIGHTBROW)
		{
			// inside down
			moveServo(SERVO6, servo6end);
			return;
		}
		return;
	}
*/
}


void rollEye(unsigned char servo, unsigned char hour)
{
//  Serial.print("Moving to ");
//  Serial.println(hour);
  
//  moveServo(servo, eyeRollPos[servo][hour]);
}


void moveServo(unsigned char servo, unsigned char position)
{
  switch (servo)
  {
  case SERVO1:
    myservo1.write(position);
    break; 
  case SERVO2:
    myservo2.write(position);
    break; 
  case SERVO3:
    myservo3.write(position);
    break; 
  case SERVO4:
    myservo4.write(position);
    break; 
  case SERVO5:
    myservo5.write(position);
    break; 
  case SERVO6:
    myservo6.write(position);
    break; 
  }
}

