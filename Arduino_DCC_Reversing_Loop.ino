int DCCWhite = 5; //declares our DCC feeders
int DCCBlue = 6;
int turnout = 12; //turnout direction
int brake = 9; //releases brake on motorshield
int power = 3; //power to the turnout
int sensor1 = A2; //sensor input
int sensor2 = A3; //sensor input

void setup() {
  Serial.begin(9600);//sets up serial monitoring
  pinMode(DCCWhite, OUTPUT); //establishes pin as output
  pinMode(DCCBlue, OUTPUT);
  pinMode(turnout, OUTPUT);
  pinMode(brake, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(sensor1, INPUT); //establishes pin as intput
  pinMode(sensor1, INPUT);
}

enum LOOPSTATES {
  ST_R1,
  ST_R2,
  ST_L1,
  ST_L2,
};

LOOPSTATES loopState = ST_R1;

void loop() {
 int Sensorval1 = analogRead(sensor1); //reads sensor input
 int Sensorval2 = analogRead(sensor2);
 Serial.println(Sensorval1);//displays sensor value in serial monitor
 Serial.println(Sensorval2);
 delay(500); //reads sensors every 0.5 seconds

 switch (loopState){
  case ST_R1:
  switchR1(Sensorval1, Sensorval2);
  break;
  case ST_R2:
  switchR2(Sensorval1, Sensorval2);
  break;
  case ST_L1:
  switchL1(Sensorval1, Sensorval2);
  break;
  case ST_L2:
  switchL2(Sensorval1, Sensorval2);
  break;
 }
 }

 void switchR1(int Sensorval1, int Sensorval2){
  digitalWrite(DCCWhite, HIGH);//turns on DCCWhite Relay
  digitalWrite(DCCBlue, HIGH);//turns on DCCBlue Relay
  digitalWrite(turnout, HIGH);//switches turnout
  digitalWrite(brake, LOW);
  digitalWrite(power, 255);//max power to the turnout
  loopState=ST_R2; //switches to off state
  
 }

void switchR2(int Sensorval1, int Sensorval2){
  digitalWrite(DCCWhite, HIGH);//turns on DCCWhite Relay
  digitalWrite(DCCBlue, HIGH);//turns on DCCBlue Relay
  digitalWrite(turnout, HIGH);//switches turnout
  digitalWrite(brake, LOW);
  digitalWrite(power, 0);//max power to the turnout

  if (Sensorval2 <200){
    loopState = ST_L1;
  }
} 

void switchL1(int Sensorval1, int Sensorval2){
  digitalWrite(DCCWhite, LOW);//turns off DCCWhite Relay
  digitalWrite(DCCBlue, LOW);//turns off DCCBlue Relay
  digitalWrite(turnout, LOW);//switches turnout
  digitalWrite(brake, LOW);
  digitalWrite(power, 255);//max power to the turnout
  loopState=ST_L2; //switches to off state
  
 }

void switchL2(int Sensorval1, int Sensorval2){
  digitalWrite(DCCWhite, LOW);//turns off DCCWhite Relay
  digitalWrite(DCCBlue, LOW);//turns off DCCBlue Relay
  digitalWrite(turnout, LOW);//switches turnout
  digitalWrite(brake, LOW);
  digitalWrite(power, 0);//max power to the turnout

  if (Sensorval1 <200){
    loopState = ST_R1;
  }
} 
