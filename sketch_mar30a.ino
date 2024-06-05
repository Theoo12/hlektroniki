#include <Servo.h>
#include <NewPing.h>

//our L298N control pins
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

#define trig_pin A1 //analog input 1
#define echo_pin A0 //analog input 2

#define maximum_distance 15

bool goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function 
Servo servo_motor; //our servo name

void setup() {

  pinMode(IN3, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo_motor.attach(7); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing(); 
  delay(100);
  distance = readPing(); 
  delay(100);
}
void loop() {
  int distanceRight = 0; 
  int distanceLeft = 0; 
  delay(50);

  if (distance <= 20){
    moveStop(); 
    delay(300); 
    moveBackward();
    delay(400); 
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft) {
    turnRight();
    moveStop();
  }
    else{
      turnLeft(); 
      moveStop();
    }
  }
    else{
      moveForward();
    }
    distance = readPing();
  }
  int lookRight() {
    servo_motor.write(50); 
    delay(500);
    int distance = readPing(); 
    delay(100);
    servo_motor.write(115);
    return distance;
  }
  int lookLeft() {
    servo_motor.write(170);
    delay(500);
    int distance = readPing(); 
    delay(100);
    servo_motor.write(115);
    return distance;
    delay(100);
  }
int readPing() { 
    delay(70);
    int cm = sonar.ping_cm();
    if (cm==0){
      cm=250;
    }
  return cm;
  }
  void moveStop() {

    digitalWrite(IN3, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN2, LOW);
  }
  void moveForward(){

    if (!goesForward) {

      goesForward=true;

    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);

    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }
}
  void moveBackward () {

    goesForward=false;

    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, HIGH);

    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
}
  void turnRight () {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, HIGH);

    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);

    delay(500);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);

    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }
  void turnLeft() {

    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);

    digitalWrite(IN1, LOW);
    digitalWrite(IN4, LOW);

    delay(500);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);

    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }