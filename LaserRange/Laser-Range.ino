#include "Laser-range.h"
#include "Laser-Range-Test.h" 

VL53L1X sensors[sensorCount];

bool TURN_RIGHT = false;
bool TURN_LEFT = false;

// Interrupt flags
volatile bool right_interrupt_triggered = false;
volatile bool left_interrupt_triggered = false;

void setup()
{
  while (!Serial) {}
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  // Runs tests
  runTests();

  // Set up interrupts
  pinMode(2, INPUT_PULLUP); // Example: Pin 2 for LEFT trigger
  pinMode(3, INPUT_PULLUP); // Example: Pin 3 for RIGHT trigger
  attachInterrupt(digitalPinToInterrupt(2), ISR_Left, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), ISR_Right, FALLING);

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

    sensors[i].setDistanceMode(VL53L1X::Long);
    sensors[i].setMeasurementTimingBudget(20000); // 20 msec

    // Assign unique addresses to each sensor
    sensors[i].setAddress(0x2A + i);
    sensors[i].startContinuous(50);
  }
}

void loop()
{
  // Handle interrupts for LEFT
  if (left_interrupt_triggered) {
    Serial.println("OBJECT ON LEFT!");
    check_sensors(sensors[0].read(),sensors[1].read());
  }

  // Handle interrupts for RIGHT
  if (right_interrupt_triggered) {
    Serial.println("OBJECT ON RIGHT!");
    check_sensors(sensors[0].read(),sensors[1].read());
  }
}

void check_sensors(int distanceLeft, int distanceRight) {
  // Check the left sensor distance
  if (distanceLeft <= 100) {
    object_Detected_Left();
  } else if (sensors[0].timeoutOccurred()) {
    Serial.print("TIMEOUT");
  } else {
    Serial.print(distanceLeft);
  }
  Serial.print('\t'); // Tab space between readings
  // Check the right sensor distance
  if (distanceRight <= 100) {
    object_Detected_Right();
  } else if (sensors[1].timeoutOccurred()) {
    Serial.print("TIMEOUT");
  } else {
    Serial.print(distanceRight);
  }
  Serial.println();
  delay(500);
}

// Interrupt Service Routines (ISRs)
void ISR_Left() {
  left_interrupt_triggered = true; // Set the left interrupt flag
}

void ISR_Right() {
  right_interrupt_triggered = true; // Set the right interrupt flag
}

void object_Detected_Left() {
  // DOES MOTOR FUNCTION
  delay(5000);  
  right_interrupt_triggered = false; 
}

void object_Detected_Right() {
  // DOES MOTOR FUNCTION
  delay(5000);
  left_interrupt_triggered = false; 
}