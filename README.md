#### THIS REPOSITORY IS ARCHIVED

# Edubot
# All Features:
  - void Edutbot.Setup(unsigned int threshold): Setup the robot for a given threshold.
        - threshold: The threshold value.

  - void Edubot.readSensors(void): Reads all infrared sensors.

  - void Edubot.setMotorSpeed(boolean motor, int s):
        - motor: defines the left or right motor.
        - s: the speed of the motor between -255 and 255.

  - bool Edubot.irLine(int sensor): Checks if a sensor is above the line. 
Note: This function does not update the sensor values, you should make a read of these first.
        - sensor: the index of the sensor to check.
        - returns: true if the sensor value is greater than the threshold or false otherwise.

  - bool Edubot.chkLine(int sensor_val): Checks if the given sensor value is above the threshold.
Note: This function does not update the sensor values, you should make a read of these first.
        - sensor_val: the sensor value to compare.
        - returns:  true if the value is greater than the threshold or false otherwise.

  - void Edubot.turnRobotBackToLine(): Makes the robot turns 180°.

  - void Edubot.turnRobotInCross(boolean dir): Turns the robot 90°.
        - dir: If true makes the robot turns clockwise, if false makes the robot turns anti clockwise.

### Installation

Just download and paste this folder on Arduino/libraries folder.


### Authors
This library was made available by the teacher of Embedded Computing Systems of Electrical Engineering and Computers in ESTG - IPLeiria, we don't know who are the real authors of this library.
