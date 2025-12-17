#include "LineFollower.h"

void initializeSensors() {
  pinMode(LEFT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(LEFT_SENSOR_LEFT_PIN, INPUT);
  pinMode(LEFT_SENSOR_MIDDLE_PIN, INPUT);

  pinMode(RIGHT_SENSOR_RIGHT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_LEFT_PIN, INPUT);
  pinMode(RIGHT_SENSOR_MIDDLE_PIN, INPUT);
}

int readSensorAverage() {
  int numReadings = 10;
  int total = 0;
  SensorReadings temp;
  for (int i = 0; i < numReadings; i++) {
    temp = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
    // total += (temp.leftReading + temp.middleReading + temp.rightReading) / 3;
    total += temp.leftReading;
    delay(10); // Small delay between readings
  }
  return total / numReadings; // Return the average
}

int calibrateThreshold() {
  int whiteAverage = 0;
  int blackAverage = 0;
  // Prompt user to place on white surface
  Serial.print("Place sensors on a white surface.  Calibration will begin in ");
  for (int i = 5; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000); // 1-second delay
  }
  whiteAverage = readSensorAverage();
  // Prompt user to place on black surface
  Serial.print("Place sensors on a black surface.  Calibration will begin in ");
  for (int i = 5; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000); // 1-second delay
  }
  blackAverage = readSensorAverage();
  int threshold = (whiteAverage + blackAverage) / 2;
  Serial.println("Threshold calibrated succesfully.  Threshold = " + String(threshold));
  return threshold;
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
  // if((left_sensor.leftReading > dynamicThreshold || left_sensor.middleReading > dynamicThreshold || left_sensor.rightReading > dynamicThreshold) && (right_sensor.leftReading > dynamicThreshold || right_sensor.middleReading > dynamicThreshold || right_sensor.rightReading > dynamicThreshold)) {
  if((left_sensor.leftReading > STATIC_THRESHOLD || left_sensor.middleReading > STATIC_THRESHOLD || left_sensor.rightReading > STATIC_THRESHOLD) && (right_sensor.leftReading > STATIC_THRESHOLD || right_sensor.middleReading > STATIC_THRESHOLD || right_sensor.rightReading > STATIC_THRESHOLD)) {
    //DEBUG
    Serial.println("FRONT EDGE DETECTED.  TURNING AROUND");
    CORRECTION_DIRECTION = 'B';
  }

  // else if(left_sensor.leftReading > dynamicThreshold) {
  else if(left_sensor.leftReading > STATIC_THRESHOLD) {
    //DEBUG
    Serial.println("LEFT BOUNDARY DETECTED.  TURNING RIGHT");
    CORRECTION_DIRECTION = 'R';
  }

  // else if(right_sensor.rightReading > dynamicThreshold) {
  else if(right_sensor.rightReading > STATIC_THRESHOLD) {
    // //DEBUG
    Serial.println("RIGHT BOUNDARY DETECTED.  TURNING LEFT");
    CORRECTION_DIRECTION = 'L';
  }

  else {
    //DEBUG
    Serial.println("No boundaries detected");
    CORRECTION_DIRECTION = '\0';
  }
}

void boundaryISR() {
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  checkBoundary(leftSensor, rightSensor);
}