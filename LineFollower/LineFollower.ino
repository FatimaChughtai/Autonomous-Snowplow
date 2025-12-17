#include "LineFollower.h"

SensorReadings leftSensor, rightSensor;

int dynamicThreshold = 0;

char CORRECTION_DIRECTION = '\0';

void setup() {    
  Serial.begin(9600);
  initializeSensors();
  // dynamicThreshold = calibrateThreshold();
  // attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR_LEFT_PIN), boundaryISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR_RIGHT_PIN), boundaryISR, CHANGE);
}

void loop() {
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  // //DEBUG
  printSensorReadings();

  checkBoundary(leftSensor, rightSensor);
  delay(1000);
}