# Integration Tests

This subdirectory contains all the integration tests that were peformed during labs 9 and 10.  In each test, a sensor subsytem was incrementally added to the main super loop to ensure it integrated properly with the motor control subsystem, and the robot functioned as expected.

## Test Coverage

### Line follower and motor control integration

In this test, the line follower sensor subsystem was combined with the motor control subsystem to ensure that the robot would correctly detect boundaries and correct its direction to avoid them accordingly.

### Line follower, ultrasonic, and motor control integration

In this test, the ultrasonic sensor subsystem was added to the previous test script to ensure that the robot would successfully detect an object accurately using the ultrasonic sensor, and correct the direction of the robot using the motors to avoid it.  The test also validated that the line follower system's funtionality did not interfere with that of the ultrasonic sensor system.

### Full integration (Line follower, ultrasonic, analog IR and motor control integration)

In this test, all subsytems were integrated together to ensure that the robot was capable of complete boundary detection and avoidance as well as obstacle avoidance, with the analog IR sensor covering any objects that were not detected by the ultrasonic sensor.
