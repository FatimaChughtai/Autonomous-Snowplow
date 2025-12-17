#ifndef LASER_RANGE_TESTS_H
#define LASER_RANGE_TESTS_H

#include "laser-range.h"

// Test runner function
void runTests();

// Test case for polling
void polling_test();

// Test case for making sure that it respond correctly to object detection on the right
void object_right_test();

// Test case for making sure that it respond correctly to object detection on the left
void object_left_test();
#endif