#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// Define pins used
#define frontLeftDirection A10
#define backLeftDirection A11
#define frontRightDirection A7
#define backRightDirection A9

// Define functions
void initializeMotors();
void forward();
void backward();
void turnRight();
void turnLeft();
void off();
void slow();
void fast();
void borderLShallow();
void borderRShallow();
void borderL();
void borderR();
void border();
void ir();
void ultrasonicL();
void ultrasonicR();
void initializeSpeed();

#endif