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

int enA = 6;
int enB = 5;
int enC = 4;
int enD = 3;

int dutyPin = 2;

//Motor setup
L298N frontLeft(enA, motor1pin2, motor1pin1);
L298N backLeft(enB, motor2pin2, motor2pin1);
L298N backRight(enC, motor4pin2, motor4pin1);
L298N frontRight(enD, motor3pin2, motor3pin1);

//Wifi module pins
int wifiPinRX = 10;
int wifiPinTX = 11;



void setup() {
  // put your setup code here, to run once:
  pinMode(dutyPin, INPUT); //duty cycle

  backLeft.setSpeed(255);  // ~ 90 to 255
  backRight.setSpeed(255); // ~ 90 to 255
  frontLeft.setSpeed(255); // ~ 90 to 255
  frontRight.setSpeed(255); // ~ 90 to 255

  //Wifi module setup
  Enes100.begin("Data Dinos", DATA, 417, wifiPinRX, wifiPinTX); //wifi module

  //pinMode(dutyPin, INPUT); //duty cycle

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
  frontLeft.backward();
  backLeft.backward();
  backRight.forward();
  frontRight.forward();
  delay(4500);

  frontLeft.stop();
  frontRight.stop();
  backLeft.stop();
  backRight.stop();
  
  //Print duty cycle
  Serial.println("Duty Cycle: ");
  Serial.println(readDutyCycle());

  delay(1000);
}

double readDutyCycle() {
  double ontime = pulseIn(dutyPin,HIGH);
  double offtime = pulseIn(dutyPin,LOW);
  double period = ontime+offtime;
  double freq =  1000000.0/period;
  double duty = (ontime/period)*100;  

  return duty;
}
