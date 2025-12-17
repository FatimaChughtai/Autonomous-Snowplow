# SYSC4805 Autonomous Snowplow: L1-G8 - Team Beaver

Snow plows are an essential part of the community in the winter, as they significantly reduce the tedious labor and potential safety hazards that come with removing snow from roads, driveways, parking lots, etc. while keeping them safe for driving and walking.  This repository contains all the software for group L1-G8's implementation of a scale model of an autonomous snowplow system, which mimics this real world application within a variety of preset size and performance constraints.  The software in this repository includes the function handlers for the line follower sensors, ultrasonic sensors, and analog IR distance sensors, the unit tests for each sensor subsystem, the motor control subsystem, and the main superloop script where all subsystems are combined.  

## File Breakdown:

### [LineFollower](https://github.com/SYSC4805/project-l1-g8/tree/main/LineFollower), [UltrasonicSensor](https://github.com/SYSC4805/project-l1-g8/tree/main/UltrasonicSensor), and [LaserRange](https://github.com/SYSC4805/project-l1-g8/tree/main/LaserRange):

These three subdirectories contain the function handlers for their respective subsystems, as well as their header files.

### [UnitTests](https://github.com/SYSC4805/project-l1-g8/tree/main/UnitTests):

This subdirectory contains all the unit tests for each sensor subsystem, with each unit test verifying that the subsystem it tests against functions properly .  A breakdown of each subsystem's test cases can be found [here](https://github.com/SYSC4805/project-l1-g8/blob/main/UnitTests/README.md).

### [IntegrationTests](https://github.com/SYSC4805/project-l1-g8/tree/main/IntegrationTests)
This subdirectory contains all the integration tests performed during labs 9 and 10 to validate the robot had complete boundary detection and avoidance as well as obstacle detection and avoidance capabilities.  A breakdown of the integration testing plan and each test can be found [here](https://github.com/SYSC4805/project-l1-g8/blob/main/IntegrationTests/README.md).

### [Main](https://github.com/SYSC4805/project-l1-g8/tree/main/Main): 

This subdirectory implements the main functionality of the robot.  It contains the header files for each sensor subsystem and the motor control subsystem as well as [robotMain.ino](https://github.com/SYSC4805/project-l1-g8/blob/main/Main/robotMain.ino), where all the function handlers for each subsystem are used to implement the superloop that controls the robot's behaviour.

## Execution Instructions:

To deploy the software onto the autonomous snowplow robot, simply compile and flash [robotMain.ino](https://github.com/SYSC4805/project-l1-g8/blob/main/Main/robotMain.ino) onto the Arduino Due using its programming port.
