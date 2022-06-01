#include "AFMotor.h"
#include <Servo.h>

#define echopin A0 // echo pin
#define trigpin A1 // Trigger pin

Servo myservo;

const int MOTOR_1 = 1; //back left
const int MOTOR_2 = 2; //back right
const int MOTOR_3 = 3; //front right
const int MOTOR_4 = 4; //front left

AF_DCMotor back_left(MOTOR_1); // create motor object, 64KHz pwm back left motor
AF_DCMotor back_right(MOTOR_2); // create motor object, 64KHz pwm back right
AF_DCMotor front_right(MOTOR_3); // create motor object, 64KHz pwm front right motor
AF_DCMotor front_left(MOTOR_4); // create motor object, 64KHz pwm front left

//===============================================================================
//  Initialization
//===============================================================================

int distance_L, distance_F, distance_R;
long distance;

int set = 20;
 
void setup() {
  Serial.begin(115200);           // Initialize serial port
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(90);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  back_left.setSpeed(255);          // set the motor speed to 0-255
  back_right.setSpeed(255);
 front_right.setSpeed(255);          // set the motor speed to 0-255
  front_left.setSpeed(255);
}
//===============================================================================
//  Main
//=============================================================================== 
void loop() {
 distance_F = data();
 Serial.print("S=");
 Serial.println(distance_F);
  if (distance_F > set){
   Serial.println("Forward");
  back_left.run(FORWARD);         // turn it on going forward
  back_right.run(FORWARD); 
  front_left.run(FORWARD);         // turn it on going forward
  front_right.run(FORWARD);
    }
    else{hc_sr4();}
}


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echopin, HIGH);
  return distance / 29 / 2;
}


void compareDistance(){
  Serial.println(String(distance_L)+","+String(distance_F)+","+String(distance_R));
  if (distance_L > distance_R){
  back_left.run(BACKWARD);   // turn it on going left
back_right.run(FORWARD);
  front_left.run(BACKWARD);   // turn it on going left
front_right.run(FORWARD);
    delay(1000);
  }
  else if (distance_R > distance_L){
  back_left.run(FORWARD);  // the other right
  back_right.run(BACKWARD); 
  front_left.run(FORWARD);  // the other right
  front_right.run(BACKWARD); 
    delay(1000);
  }
  else{
  back_left.run(BACKWARD);  // the other way
  back_right.run(BACKWARD);
  front_left.run(BACKWARD);  // the other way
  front_right.run(BACKWARD);
   delay(500);
  back_left.run(BACKWARD);   // turn it on going left
  back_right.run(FORWARD);
   front_left.run(BACKWARD);   // turn it on going left
  front_right.run(FORWARD);
 
    delay(1000);
  }
}

void hc_sr4(){
    Serial.println("Stop");
    back_left.run(RELEASE);         // stopped
    back_right.run(RELEASE);
    front_left.run(RELEASE);         // stopped
    front_right.run(RELEASE);
    myservo.write(0);
    delay(300);
    distance_R = data();
    delay(100);
    myservo.write(150);
    delay(500);
    distance_L = data();
    delay(100);
    myservo.write(85);
    delay(300);
    compareDistance();
}
