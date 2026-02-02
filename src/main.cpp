#include "main.h"
#include "autons.h"
#include "autonselector.h"
#include "distanceReset.h"
#include "intake.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pid.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include <cstddef>

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
// pros::MotorGroup leftMotors({-20, -18, -10},
//                             pros::MotorGearset::blue); // left motor group -
//                             ports 3 (reversed), 4, 5 (reversed)
// pros::MotorGroup rightMotors({12, 5, 6}, pros::MotorGearset::blue); // right
// motor group - ports 6, 7, 9 (reversed)

pros::MotorGroup
    leftMotors({-5, -4, -11},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {19, 9, 20},
    pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

lemlib::Drivetrain drivetrain(&leftMotors,  // left motor group
                              &rightMotors, // right motor group
                              12,           // 10 inch track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm is 450
                              2    // horizontal drift is 2 (for now)
);

pros::Imu imu(7);

pros::Rotation horizontal_encoder(16); // odom sensor
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder,
                                                lemlib::Omniwheel::NEW_2,
                                                -1.875);

pros::Rotation vertical_encoder(18); // odom sensor
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                              lemlib::Omniwheel::NEW_2, .125);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr,
                            &horizontal_tracking_wheel, nullptr, &imu);

// lemlib::OdomSensors sensors(nullptr, nullptr,
//                             &horizontal_tracking_wheel, nullptr, &imu);

lemlib::ControllerSettings
    lateral(4.23, // proportional gain (kP)
            0,    // integral gain (kI)
            5,    // derivative gain (kD)
            0,    // anti windup
            .5,   // small error range, in inches
            100,  // small error range timeout, in milliseconds
            .7,   // large error range, in inches
            2000, // large error range timeout, in milliseconds
            20    // maximum acceleration (slew)
    );

lemlib::ControllerSettings
    angular(3.075, // proportional gain (kP)
            0,     // integral gain (kI)
            14,    // derivative gain (kD)
            3,     // anti windup
            .5,    // small error range, in degrees
            500,   // small error range timeout, in milliseconds
            1,     // large error range, in degrees
            800,   // large error range timeout, in milliseconds
            0      // maximum acceleration (slew)
    );
lemlib::ExpoDriveCurve throttle(3, 10, 1.019);
lemlib::ExpoDriveCurve steer(3, 10, 1.019);

// Chassis with dummy settings
lemlib::Chassis chassis(drivetrain, lateral, angular, sensors, &throttle,
                        &steer);

// Scraper
pros::adi::DigitalOut scraper('F', false);
// pros::adi::DigitalOut descore('F', false);
pros::adi::DigitalOut wing('E', false);
pros::adi::DigitalOut horLift('D', false);
pros::adi::DigitalOut verLift('G',false);
// pros::adi::DigitalOut flappier('B', false);

// wing
bool removerActivated = false;
bool wingActivated = false;
bool hoodActivated = false;
bool scraperActivated = false;

// flingBlue = false;
bool removerPressedLast = false;
bool hoodPressedLast = false;
bool scraperPressedLast = false;
bool wingPressedLast = false;

void screen() {
  // loop forever
  while (true) {
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y,
                     pose.theta);             // print the x position
    pros::lcd::print(1, "H: %f", pose.theta); // print the x position
    // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y, pose.theta,
    // vertical_rot.get_position());
    pros::lcd::print(2, "right distance sensor: %f", right_sensor.get());
    pros::lcd::print(3, "front distance sensor: %f", front_sensor.get());
    pros::delay(50);
  }
}

void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  chassis.setPose(0, 0, 0);
  horizontal_encoder.reset_position();
  vertical_encoder.reset_position();
  pros::lcd::initialize(); // initialize brain screen
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  opticalSensor.set_led_pwm(100);

  // pros::delay(4000);
  pros::delay(1000);


  // autonSelectorStart();
  pros::Task screenTask(screen);
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

void autonomous() {
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  // Skills 
  skills();


  // Right side Low goal
  // lowGoal();


  // Solo AWP
  // soloAWPCedar();
  //skills2();


  // Left side 3 + 4 
  // leftSide3Plus4();



}

void opcontrol() {
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  // chassis.turnToHeading(130, 2000);
  // turnToHeading(180, 1000, 127);
  // chassis.moveToPoint(0, 20, 750);
  // skills();
  while (true) {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(leftY, rightX);

    // bool removerPressedNow
    // =controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    // wing.set_value(removerPressedNow);

    bool removerPressedNow =
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

    if (removerPressedNow && !removerPressedLast) {
      // Toggle remover
      removerActivated = !removerActivated;
      wing.set_value(removerActivated);
    }

    removerPressedLast = removerPressedNow;

    bool scraperPressedNow =
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

    if (scraperPressedNow && !scraperPressedLast) {
      // Toggle hood
      scraperActivated = !scraperActivated;
      scraper.set_value(scraperActivated);
    }

    scraperPressedLast = scraperPressedNow;

    updateIntake();

    pros::delay(20);
  }
}