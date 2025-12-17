# Line Follower Sensor Subsystem

This subdirectory contains the implementation for all the function handlers associated with the line follower sensor subsystem.  
The main purpose of these handlers is to allow the subsystem to interface with the line follower sensors to be able to 
correctly detect when the robot has crossed a black boundary line, and generate an interrupt to correct the robot's direction 
based on which boundary was detected.

To run an example implementation of the line follower subsystem, simply compile and upload the [LineFollower.ino](https://github.com/SYSC4805/project-l1-g8/blob/main/LineFollower/LineFollower.ino) file to your Arduino Due.
