#include "pid.h"
#include <ctime>
#include <cmath>
#include "lemlib/api.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"


bool is_turning = false;
double prev_left_output = 0, prev_right_output = 0;
double x_pos = 0, y_pos = 0;
double correct_angle = 0;
// Field config for distance resets, DO NOT CHANGE
double field_half_size = 70.25;  // Half field size in inches

pros::Distance front_sensor(15); 
pros::Distance left_sensor(2);
pros::Distance right_sensor(21);
pros::Distance back_sensor(17);
double front_sensor_offset = 6.5;
double left_sensor_offset = 5.8;
double right_sensor_offset = 5.8;
double back_sensor_offset = 3.2;

double getInertialHeading() {
  // Get inertial sensor rotation in degrees
  return imu.get_rotation();
}

double getResetPositionX(){
    return x_pos;
}

double getResetPositionY(){
    return y_pos;
}

void resetPositionWithSensor(pros::Distance& sensor, double sensor_offset, double sensor_angle_offset, double field_half_size) {
    double sensorReading = ((sensor.get())/25.4);
  
    // Check for invalid reading (distance sensors return -1 or very large values when no object detected)
    if (sensorReading < 0 || sensorReading > 200) {
        printf("Invalid distance sensor reading: %.2f", sensorReading);
        return;
    }
    
    // Get current pose
    double current_heading_deg = getInertialHeading();
    double robot_heading_deg = current_heading_deg + sensor_angle_offset;
    
    // Normalize heading to 0-360 range
    int headingDeg = (int)(robot_heading_deg);
    headingDeg = (headingDeg + 360) % 360;
    
    // Determine which wall we're facing and which axis to reset
    bool resettingX = false;
    double wallSign = 1.0;
    
    if (315 <= headingDeg || headingDeg <= 45) {
        // Top wall - reset Y position
        resettingX = false;
        wallSign = 1.0;
    }
    else if (45 < headingDeg && headingDeg <= 135) {
        // Right wall - reset X position
        resettingX = true;
        wallSign = 1.0;
    }
    else if (135 < headingDeg && headingDeg <= 225) {
        // Bottom wall - reset Y position
        resettingX = false;
        wallSign = -1.0;
    }
    else {
        // Left wall - reset X position
        resettingX = true;
        wallSign = -1.0;
    }
    
    // Calculate distance from wall to robot center
    double wallToCenter = sensorReading + sensor_offset;
    
    // Calculate actual position
    double actualPos = wallSign * (field_half_size - wallToCenter);
    
    // Update position (only reset the appropriate axis)
    if (resettingX) {
        x_pos = actualPos;

    } else {
        y_pos = actualPos;

    }
}
// ============================================================================
// DISTANCE SENSOR POSITION RESET FUNCTIONS
// ============================================================================

/*
 * resetPositionWithSensor
 * Resets position using a distance sensor based on which wall the robot is facing.
 * Only resets X or Y position (not both) based on the wall being measured.
 * 
 * - sensor: Distance sensor to use
 * - sensor_offset: Distance offset of the sensor from robot center (in inches)
 * - sensor_angle_offset: Angle offset for the sensor direction (0° = front, 90° = right, 180° = back, 270° = left)
 * - field_half_size: Half the field dimension (distance from center to wall, in inches)

 ** - IMPORTANT NOTE FOR THE USER - **
 * - DO NOT CALL THIS FUNCTION DIRECTLY, use the specific direction functions below instead.
 */

/*
 * resetPositionFront
 * Resets position using the front distance sensor.
 * Remember to only use these when perpendicular to the wall!
 * - sensor: Front distance sensor
 * - sensor_offset: Distance offset of the sensor from robot center (in inches)
 * - field_half_size: Half the field dimension (distance from center to wall, in inches)
 */




void resetPositionFront() {
    resetPositionWithSensor(front_sensor, front_sensor_offset, 0.0, field_half_size);
}

/*
 * resetPositionBack
 * Resets position using the back distance sensor.
 * Remember to only use these when perpendicular to the wall!
 * - sensor: Back distance sensor 
 * - sensor_offset: Distance offset of the sensor from robot center (in inches)
 * - field_half_size: Half the field dimension (distance from center to wall, in inches)
 */
void resetPositionBack() {
    resetPositionWithSensor(back_sensor, back_sensor_offset, 180.0, field_half_size);
}

/*
 * resetPositionLeft
 * Resets position using the left distance sensor.
 * Remember to only use these when perpendicular to the wall!
 * - sensor: Left distance sensor
 * - sensor_offset: Distance offset of the sensor from robot center (in inches)
 * - field_half_size: Half the field dimension (distance from center to wall, in inches)
 */
void resetPositionLeft() {
    resetPositionWithSensor(left_sensor, left_sensor_offset, 270.0, field_half_size);
}

/*
 * resetPositionRight
 * Resets position using the right distance sensor.
 * Remember to only use these when perpendicular to the wall!
 * - sensor: Right distance sensor
 * - sensor_offset: Distance offset of the sensor from robot center (in inches)
 * - field_half_size: Half the field dimension (distance from center to wall, in inches)
 */
void resetPositionRight() {
    resetPositionWithSensor(right_sensor, right_sensor_offset, 90.0, field_half_size);
}
void resetAllPositions() {
    resetPositionFront();
    resetPositionBack();
    resetPositionLeft();
    resetPositionRight();
}

// ============================================================================
// TEMPLATE NOTE
// ============================================================================
// This file is intended as a template for VEX/V5 robotics teams.
// All functions and variables use clear, consistent naming conventions.
// Comments are concise and explain the intent of each section.
// Teams can adapt PID values, drive base geometry, and logic as needed for their robot.