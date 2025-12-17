#include "LineFollower.h"
//Uses the VL53L1X example as the base for this
#include <Wire.h>
#include <VL53L1X.h>

// The number of sensors in your system.
const uint8_t sensorCount = 2;

// The Arduino pin connected to the XSHUT pin of each sensor.
const uint8_t xshutPins[sensorCount] = {2, 3};

VL53L1X sensors[sensorCount];

bool TURN_RIGHT = false;
bool TURN_LEFT = false;

#define FLD A10
#define BLD A11
#define FRD A8
#define BRD A9
#define speedPin A6

int TRG_PIN = 8;
int ECHO_PIN = 7;
bool CAPTRUE_FLAG = false;
bool RESPONSE = false;
unsigned char byteCoverter;

void check_sensors() {
  int distanceLeft = sensors[0].read();
  int distanceRight = sensors[1].read();
  // Individual checks for each sensor
    for (uint8_t i = 0; i < sensorCount; i++)
    {   
      int distance = sensors[i].read();
      if (distance <= 100) {
        // Check which sensor is too close
        if (i == 0) {  // Left sensor
          TURN_RIGHT = true; 
        } else if (i == 1) {  // Right sensor
          TURN_LEFT = true; 
        }
      } else if (sensors[i].timeoutOccurred()) { 
        Serial.print("TIMEOUT");
      } else {
        Serial.print(distance);
      }
      Serial.print('\t');
    }
    Serial.println();
  delay(500); // Delay between readings
}

void object_Detected_Left() {
  // WAIT ON RESPONSE FROM THE I2C
  Serial.println("TURNING LEFT RN!");  //WILL BE REPLACED WITH I2C 
  off();
  delay(200);
  turnRight();
  slow();
  delay(1500);
  off();
  forward();
  // delay(5000);  //WILL BE REPLACED WITH I2C 
  TURN_LEFT = false;
}

void object_Detected_Right() {
  // WAIT ON RESPONSE FROM THE I2C
  Serial.println("TURNING RIGHT RN!");  //WILL BE REPLACED WITH I2C 
  off();
  delay(200);
  turnRight();
  slow();
  delay(1500);
  off();
  forward();
  // delay(5000);  //WILL BE REPLACED WITH I2C 
  TURN_RIGHT = false;
}

void checkObject(int distance){
  /**
  The purpose of this function is detect for objects using a given threshold of
  15 cm
  **/
    if (distance > 15 || distance < 0.5){
      Serial.println("No obsclates detected");
      delay(100);
    }
    else {
    CAPTRUE_FLAG = true;
    Serial.println("OBJECTED DETECTED @ ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);
    // objectDetected(distance);
    
    }

}
void objectDetected(int distance){
  /** The purpose of this function is to send out a interrupt signal to the Arduino due to stop the system has
      an object was detected
      **/
  delay(1000);
  byteCoverter = (unsigned char)distance;
  Wire.beginTransmission(8);
  Wire.write(byteCoverter);
  Wire.endTransmission();
  
  while(!RESPONSE){
    Wire.requestFrom(8, 1); // Request 1 byte from slave address 8
    if (Wire.available()) {
    byte confirmation = Wire.read();
      if (confirmation == 1) {
        Serial.println("Detection Acknowledged!");
        RESPONSE = true;      
      }
    }
  }
  CAPTRUE_FLAG = false;
}

void initializeMotors() {
  // initialize motors
  pinMode(FLD, OUTPUT);
  pinMode(BLD, OUTPUT);
  pinMode(FRD, OUTPUT);
  pinMode(BRD, OUTPUT);
  pinMode(speedPin, OUTPUT);
}

void forward() {
  // motor direction to forward
  digitalWrite(FLD, 1);
  digitalWrite(BLD, 1);
  digitalWrite(FRD, 0);
  digitalWrite(BRD, 0);
}

void backward() {
  // motor direction backward
  digitalWrite(FLD, 0);
  digitalWrite(BLD, 0);
  digitalWrite(FRD, 1);
  digitalWrite(BRD, 1);
}

void turnRight() {
  // motor direction right
  digitalWrite(FLD, 0);
  digitalWrite(BLD, 0);
  digitalWrite(FRD, 0);
  digitalWrite(BRD, 0);
}

void turnLeft() {
  // motor direction left
  digitalWrite(FLD, 1);
  digitalWrite(BLD, 1);
  digitalWrite(FRD, 1);
  digitalWrite(BRD, 1);
}

void off() {
  // motors off
  analogWrite(speedPin, 0);
}

void fast() {
  // motors fast
  analogWrite(speedPin, 255);
}

void slow() {
  // motors slow
  analogWrite(speedPin, 150);
}

SensorReadings leftSensor, rightSensor;

char CORRECTION_DIRECTION = '\0';
// bool boundaryDetected = false;

void initializeSensors() {
  pinMode(LEFT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(LEFT_SENSOR_LEFT_PIN, INPUT);
  pinMode(LEFT_SENSOR_MIDDLE_PIN, INPUT);

  pinMode(RIGHT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_LEFT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_MIDDLE_PIN, INPUT);
}

SensorReadings readSensorValues(int leftPin, int middlePin, int rightPin) {
  SensorReadings sensor;
  sensor.leftReading = analogRead(leftPin);
  sensor.middleReading = analogRead(middlePin);
  sensor.rightReading = analogRead(rightPin);
  return sensor;
}

void printSensorReadings() {
  Serial.println("Left Sensor left: " + String(leftSensor.leftReading) + " | Left Sensor middle: " + String(leftSensor.middleReading) + " | Left Sensor right: " + String(leftSensor.rightReading));
  Serial.println("Right Sensor left: " + String(rightSensor.leftReading) + " | Right Sensor middle: " + String(rightSensor.middleReading) + " | Right Sensor right: " + String(rightSensor.rightReading));
}

void checkBoundary(SensorReadings &left_sensor, SensorReadings &right_sensor) {
  if((left_sensor.leftReading > STATIC_THRESHOLD || left_sensor.middleReading > STATIC_THRESHOLD || left_sensor.rightReading > STATIC_THRESHOLD) && (right_sensor.leftReading > STATIC_THRESHOLD || right_sensor.middleReading > STATIC_THRESHOLD || right_sensor.rightReading > STATIC_THRESHOLD)) {
    //DEBUG
    Serial.println("FRONT EDGE DETECTED.  TURNING AROUND");
    CORRECTION_DIRECTION = 'B';
    off();
    delay(200);
    turnRight();
    slow();
    delay(1500);
    off();
    forward();
  }

  else if(left_sensor.leftReading > STATIC_THRESHOLD) {
    //DEBUG
    Serial.println("LEFT BOUNDARY DETECTED.  TURNING RIGHT");
    CORRECTION_DIRECTION = 'R';
    off();
    delay(200);
    turnRight();
    slow();
    delay(1500);
    off();
    forward();
  }

  else if(right_sensor.rightReading > STATIC_THRESHOLD) {
    // //DEBUG
    Serial.println("RIGHT BOUNDARY DETECTED.  TURNING LEFT");
    CORRECTION_DIRECTION = 'L';
    off();
    delay(200);
    turnRight();
    slow();
    delay(1500);
    off();
    forward();
  }

  else {
    //DEBUG
    Serial.println("No boundaries detected");
    CORRECTION_DIRECTION = '\0';
    forward();
    slow();
  }
}

void boundaryISR() {
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  checkBoundary(leftSensor, rightSensor);
}

void setup() {    
  initializeSensors();
  initializeMotors();
  // attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR_LEFT_PIN), boundaryISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR_RIGHT_PIN), boundaryISR, CHANGE);
  pinMode(TRG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  
  // while (!Serial) {}
  Wire.begin();
  Wire.setClock(400000);

  // Disable/reset all sensors by driving their XSHUT pins low.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }

  // Enable, initialize, and start each sensor, one by one.
  for (uint8_t i = 0; i < sensorCount; i++)
  {
    pinMode(xshutPins[i], INPUT);
    delay(10);

    sensors[i].setTimeout(500);
    if (!sensors[i].init())
    {
      Serial.print("Failed to detect and initialize sensor ");
      Serial.println(i);
      while (1);
    }

    sensors[i].setDistanceMode(VL53L1X::Short);
    sensors[i].setMeasurementTimingBudget(20000); // 20 msec

    // Assign unique addresses to each sensor
    sensors[i].setAddress(0x2A + i);

    sensors[i].startContinuous(50);
  }
  forward();
}

void loop() {
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  // //DEBUG
  // Serial.println("New sensor values from left line follower");
  // leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  // //DEBUG
  // Serial.println("Left Sensor left: " + String(leftSensor.leftReading) + " | Left Sensor middle: " + String(leftSensor.middleReading) + " | Left Sensor right: " + String(leftSensor.rightReading));

  // //DEBUG
  // Serial.println("New sensor values from right line follower");
  // rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  // //DEBUG
  // Serial.println("Right Sensor left: " + String(rightSensor.leftReading) + " | Right Sensor middle: " + String(rightSensor.middleReading) + " | Right Sensor right: " + String(rightSensor.rightReading));
  printSensorReadings();

  checkBoundary(leftSensor, rightSensor);
  if (CORRECTION_DIRECTION == 'B') {
    Serial.println("Turning around");
    
  } else if (CORRECTION_DIRECTION == 'R') {
    Serial.println("Going right");
  } else if (CORRECTION_DIRECTION == 'L') {
    Serial.println("Going left");
  } else {

  }

  int duration = 0;
  int distance = 0;
  int pulse = 0;
  digitalWrite(TRG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG_PIN, LOW);
  pulse = pulseInLong(ECHO_PIN, HIGH);
  distance = (pulse * 0.0343) / 2;
  checkObject(distance);
  // delay(500);

  // check_sensors();
  // if (TURN_LEFT) {
  //   object_Detected_Left();
  // }
  // if (TURN_RIGHT) {
  //   object_Detected_Right();
  // }
  forward();
  slow();
  delay(50);
}


