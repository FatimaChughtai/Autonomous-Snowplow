#ifndef LASERRANGE_H
#define LASERRANGE_H

#include <Wire.h>
#include <VL53L1X.h>
#include <Arduino.h>

// The number of sensors in your system
const uint8_t sensorCount = 2;

// The Arduino pins connected to the XSHUT pins of each sensor
const uint8_t xshutPins[sensorCount] = {2, 3};

// Declare interrupt service routines
void ISR_Left();
void ISR_Right();

// Function prototypes
void check_sensors(int distanceLeft, int distanceRight);
void object_Detected_Left();
void object_Detected_Right();

#endif
