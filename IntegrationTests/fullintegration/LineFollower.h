#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

// Define sensor pin assignments
#define LEFT_SENSOR_LEFT_PIN A0
#define LEFT_SENSOR_RIGHT_PIN A1
#define LEFT_SENSOR_MIDDLE_PIN A2

#define RIGHT_SENSOR_LEFT_PIN A3
#define RIGHT_SENSOR_RIGHT_PIN A4
#define RIGHT_SENSOR_MIDDLE_PIN A5

#define STATIC_THRESHOLD 900

#define THRESHOLD_BOUNDARY 15

// Define a struct to hold sensor readings
struct SensorReadings {
  int leftReading = 0;
  int middleReading = 0;
  int rightReading = 0;
};

// Function prototypes
void initializeLineFollowers();
int calibrateThreshold();
SensorReadings readSensorValues(int leftPin, int middlePin, int rightPin);
void printSensorReadings();
void checkBoundary(SensorReadings &left_sensor, SensorReadings &right_sensor);
void BoundaryISR();

#endif