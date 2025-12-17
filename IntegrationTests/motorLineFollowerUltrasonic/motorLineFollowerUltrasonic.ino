// SYSC 4805 L1-G8
// Joseph Vretenar
// Fatima Chunghtai
// Aniesh Sabnani
// Aaranan Sathiendran

#include "LineFollower.h"
#include "MotorControl.h"
#include "Ultrasonic.h"

int watchdogTime = 10000;
SensorReadings leftSensor, rightSensor;

void setup() {
  // Initialize all functions of the robot
  initializeLineFollowers();
  initializeUltrasonic();
  initializeMotors();
  initializeSpeed();
  forward();
  watchdogEnable(watchdogTime);
}

void loop() {
  // Reset the watchdog timer
  watchdogReset();
  // Check line follower sensors
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  checkBoundary(leftSensor, rightSensor);
  // Check ultrasonic sensors
  checkLeft(getDistance(1));
  checkRight(getDistance(1));
  // Default move forwards();
  forward();
  slow();
}

// Line Follower Functions

void initializeLineFollowers() {  // Initialize all pins for line following sensors
  pinMode(LEFT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(LEFT_SENSOR_LEFT_PIN, INPUT);
  pinMode(LEFT_SENSOR_MIDDLE_PIN, INPUT);
  pinMode(RIGHT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_LEFT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_MIDDLE_PIN, INPUT);
}

SensorReadings readSensorValues(int leftPin, int middlePin, int rightPin) { // Read one sensor's values
  SensorReadings sensor;
  sensor.leftReading = analogRead(leftPin);
  sensor.middleReading = analogRead(middlePin);
  sensor.rightReading = analogRead(rightPin);
  return sensor;
}

void checkBoundary(SensorReadings &left_sensor, SensorReadings &right_sensor) { // Check sensors for boundaries
  if ((left_sensor.leftReading > STATIC_THRESHOLD || left_sensor.middleReading > STATIC_THRESHOLD || left_sensor.rightReading > STATIC_THRESHOLD) && (right_sensor.leftReading > STATIC_THRESHOLD || right_sensor.middleReading > STATIC_THRESHOLD || right_sensor.rightReading > STATIC_THRESHOLD)) {
    border();
  } else if (left_sensor.leftReading > STATIC_THRESHOLD || left_sensor.middleReading > STATIC_THRESHOLD || left_sensor.rightReading > STATIC_THRESHOLD) {
    if (left_sensor.leftReading > STATIC_THRESHOLD && !(left_sensor.middleReading > STATIC_THRESHOLD) && !(left_sensor.rightReading > STATIC_THRESHOLD)) {
      borderLShallow();
    } else {
      borderL();
    }
  } else if (right_sensor.leftReading > STATIC_THRESHOLD || right_sensor.middleReading > STATIC_THRESHOLD || right_sensor.rightReading > STATIC_THRESHOLD) {
    if (!(right_sensor.leftReading > STATIC_THRESHOLD) && !(right_sensor.middleReading > STATIC_THRESHOLD) && right_sensor.rightReading > STATIC_THRESHOLD) {
      borderRShallow();
    } else {
      borderR();
    }
  }
}

// Ultrasonic Functions
void initializeUltrasonic() { // Initialize all pins for ultrasonic sensors
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(ECHOPIN1, INPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(ECHOPIN2, INPUT);
}
void checkLeft(int distance) {  // Check left sensor distance
  if (distance > 10 || distance < 0.5) {
  } else {
    ultrasonicL();
  }
}
void checkRight(int distance) { // Check right sensor distance
  if (distance > 10 || distance < 0.5) {
  } else {
    ultrasonicR();
  }
}
int getDistance(bool sensor) {  // Get the distance for selected sensor
  if (sensor) {
    digitalWrite(TRIGPIN1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN1, LOW);
    int duration = pulseIn(ECHOPIN1, HIGH);
    int distance = duration * 0.034 / 2;
    return distance;
  } else {
    digitalWrite(TRIGPIN2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN2, LOW);
    int duration = pulseIn(ECHOPIN2, HIGH);
    int distance = duration * 0.034 / 2;
    return distance;
  }
}

// Motor Control Functions
void initializeMotors() { // Initialize motor direction pins
  pinMode(frontLeftDirection, OUTPUT);
  pinMode(backLeftDirection, OUTPUT);
  pinMode(frontRightDirection, OUTPUT);
  pinMode(backRightDirection, OUTPUT);
}
void forward() {  // Set direction to forwards
  digitalWrite(frontLeftDirection, 1);
  digitalWrite(backLeftDirection, 1);
  digitalWrite(frontRightDirection, 0);
  digitalWrite(backRightDirection, 0);
}
void backward() { // Set direction to backwards
  digitalWrite(frontLeftDirection, 0);
  digitalWrite(backLeftDirection, 0);
  digitalWrite(frontRightDirection, 1);
  digitalWrite(backRightDirection, 1);
}
void turnRight() {  // Set direction to turning right
  digitalWrite(frontLeftDirection, 0);
  digitalWrite(backLeftDirection, 0);
  digitalWrite(frontRightDirection, 0);
  digitalWrite(backRightDirection, 0);
}
void turnLeft() { // Set direction to turning left
  digitalWrite(frontLeftDirection, 1);
  digitalWrite(backLeftDirection, 1);
  digitalWrite(frontRightDirection, 1);
  digitalWrite(backRightDirection, 1);
}
void off() {  // Set speed to off
  REG_PWM_CDTY0 = 0;
}
void slow() { // Set speed to slow
  REG_PWM_CDTY0 = 13000;
}
void fast() { // Set speed to fast
  REG_PWM_CDTY0 = 33600;
}
void borderLShallow() { // Move away from left border
  turnLeft();
  fast();
  delay(100);
  forward();
  slow();
}
void borderRShallow() { // Move away from right border
  turnRight();
  fast();
  delay(100);
  forward();
  slow();
}
void borderL() {  // Move away from left border
  delay(150);
  backward();
  delay(400);
  off();
  delay(200);
  turnLeft();
  fast();
  delay(400);
  forward();
  slow();
}
void borderR() {  // Move away from right border
  delay(150);
  backward();
  delay(400);
  off();
  delay(200);
  turnRight();
  fast();
  delay(400);
  forward();
  slow();
}
void border() { // Move away from edge border
  delay(150);
  backward();
  delay(400);
  off();
  delay(200);
  turnRight();
  fast();
  delay(400);
  off();
  forward();
  slow();
}
void ultrasonicL() {  // Function on how to move after ultrasonic left detects something
  backward();
  slow();
  delay(500);
  turnRight();
  fast();
  delay(500);
  slow();
  forward();
}
void ultrasonicR() {  // Function on how to move after ultrasonic right detects something
  backward();
  slow();
  delay(500);
  turnLeft();
  fast();
  delay(500);
  slow();
  forward();
}
void initializeSpeed() {  // Initialize all the speed pins for the robot
  REG_PMC_PCER1 |= PMC_PCER1_PID36;
  REG_PIOB_ABSR |= PIO_ABSR_P16;
  REG_PIOB_PDR |= PIO_PDR_P16;
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);
  REG_PWM_CMR0 = PWM_CMR_CPRE_CLKA;
  REG_PWM_CPRD0 = 84000;
  REG_PWM_CDTY0 = 0;
  REG_PWM_ENA = PWM_ENA_CHID0;
}

// Watchdog Timer Functions
void watchdogSetup(void) {}
