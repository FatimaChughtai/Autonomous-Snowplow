#include "Laser-Range-Test.h" 

void runTests() {
  Serial.println("Running unit tests...");
  polling_test(); 
  object_right_test();
  object_left_test();
  Serial.println("Unit tests complete!");
}

// Test 1: Checks to see if the function used for constantly polling is working correctly
void polling_test() {
  Serial.println("POLLING TEST STARTED");
  int sensor_test_value[] = {500, 450, 300, 500, 101, 200, 400, 400, 500, 500};
  int arraySize = sizeof(sensor_test_value) / sizeof(sensor_test_value[0]);
  for (int i = 0; i < arraySize; i += 2) {
    int distanceLeft = sensor_test_value[i];
    int distanceRight = sensor_test_value[i + 1];
    check_sensors(distanceLeft, distanceRight); 
  }
  Serial.println("POLLING TEST END");
  Serial.println();
}

// Test 2: Validate interrupt servicing for RIGHT detection
void object_right_test() {
  Serial.println("OBJECT RIGHT TEST STARTED");

  // Reset relevant flags
  TURN_LEFT = false;
  left_interrupt_triggered = false;

  // Call the sensor check function
  check_sensors(500, 88);

  // Check if the interrupt was triggered
  if (!TURN_LEFT) {
      Serial.println("FAIL: Left interrupt not triggered.");
      return;
  }

  // Simulate servicing the interrupt
  if (TURN_LEFT) {
      object_Detected_Right();
  }

  // Verify if the interrupt was serviced correctly
  if (!left_interrupt_triggered && !TURN_LEFT) {
      Serial.println("PASS: Left interrupt serviced correctly.");
  } else {
      Serial.println("FAIL: Left interrupt not serviced correctly.");
  }

  // Reset flags
  TURN_LEFT = false;
  left_interrupt_triggered = false;

  Serial.println("OBJECT RIGHT TEST ENDED");
  Serial.println();
}


// Test 3: Test to make sure that it responds correctly to object detection on the left
void object_left_test() {
  Serial.println("OBJECT LEFT TEST STARTED");

  // Reset relevant flags
  TURN_RIGHT = false;
  right_interrupt_triggered = false;

  // Call the sensor check function
  check_sensors(90, 188);

  // Check if the interrupt was triggered
  if (!TURN_RIGHT) {
      Serial.println("FAIL: Right interrupt not triggered.");
      return;
  }

  // Simulate servicing the interrupt
  if (TURN_RIGHT) {
      object_Detected_Left();
  }

  // Verify if the interrupt was serviced correctly
  if (!right_interrupt_triggered && !TURN_RIGHT) {
      Serial.println("PASS: Right interrupt serviced correctly.");
  } else {
      Serial.println("FAIL: Right interrupt not serviced correctly.");
  }

  // Reset flags
  TURN_RIGHT = false;
  right_interrupt_triggered = false;

  Serial.println("OBJECT LEFT TEST ENDED");
  Serial.println();
}