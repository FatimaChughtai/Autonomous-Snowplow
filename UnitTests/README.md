# Unit Tests

## Purpose
The purpose of the following Unit tests is to ensure that each indiviual sensor module meets its functional purpose

## Test Coverage
### Line follower sensor
1 - Read sensor values on white surface and verify sensors correctly detect white (< STATIC_THRESHOLD) <br>
2 - Read sensor values on black surface and verify sensors correctly detect black (> STATIC_THRESHOLD) <br>
3 - Boundary detection test for front edge (verify correction direction is backwards) <br>
4 - Boundary detection test for left edge (verify correction direction is right) <br>
5 - Boundary detection test for right edge (verify correction direction is left) <br>
6 - Boundary detection test for no boundaries (verify correction direction is null) <br>
### Laser range finder sensor
1 - Make sure sensor is constantly polling values <br>
2 - Make sure that interrupt flags can be serviced <br>
3 - Make sure that interrupt is only serviced when it within the threshold <br>
### Ultrasonic sensor
1 - Ensure that the sensor is only send an interrupt when threshold isnt met <br>
2 - The sensor is capable of analyzing accurate readings given a threshold value
