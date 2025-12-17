#include "LineFollower.h"

  // Declare sensor objects
  SensorReadings leftSensor, rightSensor;
  char CORRECTION_DIRECTION = '\0';

void assertEqualsBoolean(bool expected, bool actual, String testName) {
  if (expected == actual) {
    Serial.println(testName + ": PASS");
  } else {
    Serial.println(testName + ": FAIL");
    Serial.println("  Expected: " + expected ? "true" : "false");
    Serial.println("  Actual: " + actual ? "true" : "false");
  }
}

void assertEqualsChar(char expected, char actual, String testName) {
  if (expected == actual) {
    Serial.println(testName + ": PASS");
  } else {
    Serial.println(testName + ": FAIL");
    Serial.println("  Expected: " + expected);
    Serial.println("  Actual: " + actual);
  }
}

void countdown(int seconds) {
  Serial.println("Starting next test in " + String(seconds) + "seconds...");
  for (int i = seconds; i > 0; i--) {
    delay(1000); // 1-second delay
  }
  Serial.println("Starting next test...");
}

void setup() {
  // Initialize the sensors
  initializeSensors();
  Serial.begin(9600);
}

void loop() {

  //Test case 1: Read sensor values on white surface and verify sensors correctly detect white (< STATIC_THRESHOLD)
  Serial.println("Test 1a: White surface detection test - Move left sensor to white surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  bool leftSensorWhiteSurfaceDetected = (leftSensor.leftReading < STATIC_THRESHOLD && leftSensor.middleReading < STATIC_THRESHOLD && leftSensor.rightReading < STATIC_THRESHOLD);
  assertEqualsBoolean(true, leftSensorWhiteSurfaceDetected, "Left sensor white surface detection test");

  Serial.println("Test 1b: White surface detection test - Move right sensor to white surface");
  countdown(5);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  bool rightSensorWhiteSurfaceDetected = (rightSensor.leftReading < STATIC_THRESHOLD && rightSensor.middleReading < STATIC_THRESHOLD && rightSensor.rightReading < STATIC_THRESHOLD);
  assertEqualsBoolean(true, rightSensorWhiteSurfaceDetected, "Right sensor white surface detection test");

  //Test case 2: Read sensor values on black surface and verify sensors correctly detect black (> STATIC_THRESHOLD)
  Serial.println("Test 2a: Black surface detection test - Move left sensor to Black surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  bool leftSensorBlackSurfaceDetected = (leftSensor.leftReading > STATIC_THRESHOLD && leftSensor.middleReading > STATIC_THRESHOLD && leftSensor.rightReading > STATIC_THRESHOLD);
  assertEqualsBoolean(true, leftSensorBlackSurfaceDetected, "Left sensor black surface detection test");

  Serial.println("Test 2b: Black surface detection test - Move right sensor to black surface");
  countdown(5);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  bool rightSensorBlackSurfaceDetected = (rightSensor.leftReading > STATIC_THRESHOLD && rightSensor.middleReading > STATIC_THRESHOLD && rightSensor.rightReading > STATIC_THRESHOLD);
  assertEqualsBoolean(true, rightSensorBlackSurfaceDetected, "Right sensor black surface detection test");

  //Test case 3: Boundary detection test for front edge (verify correction direction is 'B')
  Serial.println("Test 3: Boundary detection test (front edge detection) - Move both sensors to black surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  checkBoundary(leftSensor, rightSensor);
  assertEqualsChar('B', CORRECTION_DIRECTION, "Boundary detection test (front edge detection)");

  //Test case 4: Boundary detection test for left edge (verify correction direction is 'R')
  Serial.println("Test 4: Boundary detection test (left edge detection) - Move left sensor to black surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  checkBoundary(leftSensor, rightSensor);
  assertEqualsChar('R', CORRECTION_DIRECTION, "Boundary detection test (left edge detection)");

//Test case 5: Boundary detection test for right edge (verify correction direction is 'L')
  Serial.println("Test 5: Boundary detection test (right edge detection) - Move right sensor to black surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  checkBoundary(leftSensor, rightSensor);
  assertEqualsChar('L', CORRECTION_DIRECTION, "Boundary detection test (right edge detection)");

//Test case 6: Boundary detection test for no boundaries (verify correction direction is '\0')
  Serial.println("Test 6: Boundary detection test (no boundaries) - Move both sensors to white surface");
  countdown(5);
  leftSensor = readSensorValues(LEFT_SENSOR_LEFT_PIN, LEFT_SENSOR_RIGHT_PIN, LEFT_SENSOR_MIDDLE_PIN);
  rightSensor = readSensorValues(RIGHT_SENSOR_LEFT_PIN, RIGHT_SENSOR_RIGHT_PIN, RIGHT_SENSOR_MIDDLE_PIN);
  printSensorReadings();
  checkBoundary(leftSensor, rightSensor);
  assertEqualsBoolean('\0', CORRECTION_DIRECTION, "Boundary detection test (no boundaries)");

  Serial.println("Unit test complete.");
  delay(10000);
}
