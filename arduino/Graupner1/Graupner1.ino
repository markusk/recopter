// Pin 13 has an LED connected on most Arduino boards.
int led = 13;
int relais = 12;

int rcpin = 7;  //  pin from RC receiver
int rcRegler = 6;  //  pin from RC receiver (Drehregler)

int ServoValue = 0;

int value = 0;


void setup()
{
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  pinMode(rcpin, INPUT);
  pinMode(rcRegler, INPUT);
}


void loop()
{
  value = pulseIn(rcpin, INPUT);
  
  
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
  
//  Serial.println(value);
//  Serial.println(ServoValue);
//  Serial.println("----------");
//  delay(500);               // wait some time
}

