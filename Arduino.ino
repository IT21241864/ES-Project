// Constants for pin assignments
const int trigpin = 2;
const int echopin = 3;
const int servoPin = 9;

float duration;
float cm;

void moveServo(int angle)
{
  int pulseWidth = map(angle, 0, 180, 1000, 2000);

  // Turn on the servo signal
  PORTB |= (1 << PORTB1);
  delayMicroseconds(pulseWidth);
  // Turn off the servo signal
  PORTB &= ~(1 << PORTB1);
  delayMicroseconds(20000 - pulseWidth);
}

void feed(char esp){
  if(esp == '1'){
    while(1){
      moveServo(0);
      char esp = Serial.read();
      feed(esp);
      //delay(2000);
    }
  }else if(esp == '0'){
    while(1){
      moveServo(180);
      char esp = Serial.read();
      feed(esp);
      //delay(2000);
    }
  }else if(esp == '2'){
    while(1){
      PORTD &= ~(1 << PORTD2);
      delayMicroseconds(2);
      PORTD |= (1 << PORTD2);
      delayMicroseconds(10);
      PORTD &= ~(1 << PORTD2);

      // Measure the pulse duration
      duration = pulseIn(echopin, HIGH);
      cm = (duration / 58.82);
      int distance = cm;

      if (distance >= 15)
      {
        moveServo(0); // Move the servo to a desired angle
      }
      else
      {
       moveServo(180); // Move the servo to the low position
       Serial.println("Fill\n");
      }
      char esp = Serial.read();
      feed(esp);
      //delay(2000);
    } 
  }
}

void setup()
{
  // Set trigpin as an output
  DDRD |= (1 << DDD2);

  // Set echopin as an input
  DDRD &= ~(1 << DDD3);

  // Set servoPin as an output
  DDRB |= (1 << DDB1);

  Serial.begin(9600);
}

void loop()
{
  
  if(Serial.available() > 0){
  char esp = Serial.read();
  feed(esp);
  }
 
  /*Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);*/
}
