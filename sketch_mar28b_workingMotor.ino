#include <L298N.h>
#include <Enes100.h>

int motor1pin1 = 49;
int motor1pin2 = 47;

int motor2pin1 = 45;
int motor2pin2 = 43;

int motor3pin1 = 39;
int motor3pin2 = 37;

int motor4pin1 = 35;
int motor4pin2 = 33;

int enA = 28;
int enB = 30;
int enC = 29;
int enD = 31;

L298N backLeft(enA, motor1pin1, motor1pin2);
L298N backRight(enB, motor2pin1, motor2pin2);
L298N frontLeft(enC, motor3pin1, motor3pin2);
L298N frontRight(enD, motor4pin1, motor4pin2);

//wifi module
int wifiPinRX = 10;
int wifiPinTX = 11;

//duty Cycle
int dutyPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);

  backLeft.setSpeed(250);
  backRight.setSpeed(250);
  frontLeft.setSpeed(250);
  frontRight.setSpeed(250);

  Enes100.begin("Data Dinos", DATA, 417, wifiPinRX, wifiPinTX); //wifi module

  pinMode(dutyPin, INPUT); //duty cycle

  Serial.begin(9600);
}

void loop() {

//WifiModule
  Enes100.updateLocation();
  float x = Enes100.getX();
  float y = Enes100.getY();
  float theta = Enes100.getTheta();
  bool visible = Enes100.isVisible();
  Enes100.println(x);
  Enes100.println(y);
  Enes100.println(theta);

//Motors
  backLeft.backward();
  backRight.forward();
  frontLeft.backward();
  frontRight.forward();
  delay(1000);

  //DutyCycle
   ontime = pulseIn(pulse_ip,HIGH);
   offtime = pulseIn(pulse_ip,LOW);
   period = ontime+offtime;
   freq =  1000000.0/period;
   duty = (ontime/period)*100;  
   delay(100);
   Enes100.println(duty); 
}


