#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Define pins used
#define TRIGPIN1 8
#define TRIGPIN2 9
#define ECHOPIN1 7
#define ECHOPIN2 10

// Define functions
void initializeUltrasonic();
void checkLeft(int distance);
void checkRight(int distance);
int getDistance(bool sensor);

#endif