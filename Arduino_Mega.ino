String readString;

int L298N_A_In1_pin = 9;
int L298N_A_In2_pin = 8;

int L298N_B_In3_pin = 12;
int L298N_B_In4_pin = 13;

// buzzer pin
int speakerPIN = 30;

//sensor 1
const int frontRighttrigPin = 26;
const int frontRightechoPin = 27;


//sensor 2
const int frontlefttrigPin = 24;
const int frontleftechoPin = 25;

//sensor 3
const int RighttrigPin = 4;
const int RightechoPin = 5;

//sensor 4
const int lefttrigPin = 6;
const int leftechoPin = 7;

// Finding Distance of Object
long duration1;
long duration2;
long duration3;
long duration4;
int distance1;
int distance2;
int distance3;
int distance4;

int automode = 0;

void setup() {

  Serial2.begin(9600);
  Serial.begin(9600);

  pinMode(L298N_A_In1_pin, OUTPUT);
  pinMode(L298N_A_In2_pin, OUTPUT);
  pinMode(L298N_B_In3_pin, OUTPUT);
  pinMode(L298N_B_In4_pin, OUTPUT);

  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, LOW);

  Serial.println("ULTRA CODE ");
  pinMode(frontRighttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(frontRightechoPin, INPUT); // Sets the echoPin as an Input

  pinMode(frontlefttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(frontleftechoPin, INPUT); // Sets the echoPin as an Input

  pinMode(RighttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(RightechoPin, INPUT); // Sets the echoPin as an Input

  pinMode(lefttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(leftechoPin, INPUT); // Sets the echoPin as an Input

}


void loop() {

  if (automode == 1 )
  {
    digitalWrite(frontRighttrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(frontRighttrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontRighttrigPin, LOW);
    duration1 = pulseIn(frontRightechoPin, HIGH);
    distance1 = duration1 * 0.034 / 2;
    digitalWrite(frontlefttrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(frontlefttrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontlefttrigPin, LOW);
    duration2 = pulseIn(frontleftechoPin, HIGH);
    distance2 = duration2 * 0.034 / 2;
    digitalWrite(RighttrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(RighttrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(RighttrigPin, LOW);
    duration3 = pulseIn(RightechoPin, HIGH);
    distance3 = duration3 * 0.034 / 2;
    digitalWrite(lefttrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(lefttrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(lefttrigPin, LOW);
    duration4 = pulseIn(leftechoPin, HIGH);
    distance4 = duration4 * 0.034 / 2;
    Serial.print("distance1 ");
    Serial.println(distance1);
    Serial.print("distance2 ");
    Serial.println(distance2);
    Serial.print("distance3 ");
    Serial.println(distance3);
    Serial.print("distance4 ");
    Serial.println(distance4);
    Serial.println("************");

    if ((distance1 <= 10) || (distance2 <= 10))
    {
      tone(speakerPIN, HIGH);
      delay(600);
      noTone(speakerPIN);
      MotorStop();

      if (distance3 > 20)
      {
        MotorStop();
        TurnRight();
        //        MotorForward();
        Serial2.println("Obstacle detected turning right");
      }

      else if (distance4 > 20)
      {
        MotorStop();
        TurnLeft();
        //        MotorForward();
        Serial2.println("Obstacle detected turning left");
      }

      else if ((distance1 <= 23) || (distance2 <= 23) && distance3 > 10 && distance4 > 10)
      {
        TurnLeft();
        Serial2.println("No path turing left");
      }
    }
    else
    {
      MotorForward();
      //      Serial2.println("Moving forward");
    }
  }


  if (Serial2.available())
  {
    char c = Serial2.read();
    Serial.print(c);
    if (c == 'm') manual();
    if (c == 'a') automatic();
    if (automode == 0)
    {
      if   (c == 'f')    MotorForward();
      else if (c == 'b')   MotorBackward();
      else if (c == 'l')       TurnLeft();
      else if (c == 'r')      TurnRight();
      else if (c == 's')      MotorStop();
    }
  }
}


/********************************** RECEIVE DATA FROM the APP ******************************************/
void manual(void)
{
  delay(100);
  Serial.println("manual");
  automode = 0;
}

void automatic(void)
{
  delay(100);
  Serial.println("automatic");
  automode = 1;
}


void MotorBackward(void)
{
  Serial.println("Backward");
  digitalWrite(L298N_A_In1_pin, HIGH);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, HIGH);
  digitalWrite(L298N_B_In4_pin, LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)
{
  Serial.println("Left");
  digitalWrite(L298N_A_In1_pin, HIGH);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, HIGH);
  delay(1100);
  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, LOW);
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)
{
  Serial.println("Right");
  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, HIGH);
  digitalWrite(L298N_B_In3_pin, HIGH);
  digitalWrite(L298N_B_In4_pin, LOW);
  delay(1100);
  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, LOW);
}

/********************************************* FORWARD *****************************************************/
void MotorForward(void)
{
  Serial.println("Forward");
  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, HIGH);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, HIGH);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)
{
  Serial.println("Stop");
  digitalWrite(L298N_A_In1_pin, LOW);
  digitalWrite(L298N_A_In2_pin, LOW);
  digitalWrite(L298N_B_In3_pin, LOW);
  digitalWrite(L298N_B_In4_pin, LOW);

}
