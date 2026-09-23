#include "main.h"
#include "autons.h"
#include "lift.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include <cstddef>
#include "intake.h"
#include <iostream>
#include <cmath>

pros::Controller controller(pros::E_CONTROLLER_MASTER);
//pros::ADIDigitalOut piston ('A'); // replace with actual port number
bool push = false;
bool pressed = false;
// motor groups
// pros::MotorGroup leftMotors({-20, -18, -10},
//                             pros::MotorGearset::blue); // left motor group -
//                             ports 3 (reversed), 4, 5 (reversed)
// pros::MotorGroup rightMotors({12, 5, 6}, pros::MotorGearset::blue); // right
// motor group - ports 6, 7, 9 (reversed)


pros::MotorGroup 
    leftMotors({16,19,18},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {-11,-14,-13},
    pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

lemlib::Drivetrain drivetrain(&leftMotors,  // left motor group
                              &rightMotors, // right motor group
                              12,           // 10 inch track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm is 450
                              2    // horizontal drift is 2 (for now)
);

pros::Imu imu(9);

pros::Rotation horizontal_encoder(17); // odom sensor
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder,
                                                lemlib::Omniwheel::NEW_2,
                                                -0.725);

// pros::Rotation vertical_encoder(18); // odom sensor
// lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
//                                               lemlib::Omniwheel::NEW_2, .125);

// lemlib::TrackingWheel vertical_tracking_wheel(&leftMotors,
//                                               lemlib::Omniwheel::NEW_325, // drivetrain wheel size
//                                               6.0,                        // half track width (inches)
//                                               450);    


lemlib::OdomSensors sensors(nullptr, nullptr,
                            &horizontal_tracking_wheel, nullptr, &imu);

                                               // drivetrain RPM

                            
// lemlib::OdomSensors sensors(nullptr, nullptr,
//                             &horizontal_tracking_wheel, nullptr, &imu);

lemlib::ControllerSettings
    lateral(6.45, // proportional gain (kP) //6.5
            0,    // integral gain (kI)
            0.03,    // derivative gain (kD)
            0,    // anti windup
            .5,   // small error range, in inches
            100,  // small error range timeout, in milliseconds
            .7,   // large error range, in inches
            2000, // large error range timeout, in milliseconds
            20    // maximum acceleration (slew)
    );

lemlib::ControllerSettings
    angular(1.274, // proportional gain (kP)
            0.0,     // integral gain (kI)
            0.1,    // derivative gain (kD)
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

// Lift
pros::MotorGroup lift_motors ({-1,10},pros::v5::MotorGears::green /*to be specified!*/,pros::v5::MotorEncoderUnits::degrees); // the lift has two motors
pros::Motor clawClose(12);
pros::Motor roller(20);
//Pneumatics

//TUNE for claw
int speed = -127; //MAKE A NEGATIVE NUMBER
int timeSpin = 100;
bool clawOpen = false;

//claw motors
void spinClaw(void*)
{
    int spinAt = speed;
    if (!clawOpen) spinAt = std::abs(speed);
    clawClose.move(spinAt);
    pros::delay(timeSpin);
    clawClose.brake();
    //pros::delay(100);
    clawOpen = !clawOpen;
}

void screen() {
  // loop forever
  while (true) {
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y,
                     pose.theta);             // print the x position
    pros::lcd::print(1, "H: %f", pose.theta); // print the x position

    double pos = liftDeg.get_position()/100;
    pros::lcd::print(2, "Lift: %d", pos);

    controller.print(0, 0, "Lift: %d", liftDeg.get_position());

    pros::delay(50);
  }
}

void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  chassis.setPose(0, 0, 0);
  horizontal_encoder.reset_position();
  //liftDeg.reset_position();
  pros::lcd::initialize(); // initialize brain screen
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  liftDeg.reset_position();
  liftDeg.set_reversed(true);

  pros::delay(2000);

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
  lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  //liftMacro(40);  //moveLift()
  threeStack(); 
  //oneStack();
  //liftMacro(45);
}

void opcontrol() {

  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  bool rollerSpin = false;

    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        chassis.arcade(leftY, rightX);

        //yooo this is in centidegrees I'm stupid
        double position = liftDeg.get_position()/100;

        // LIFT UP
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            if (position >= 65 && position < 90) {
                lift_motors.move(40);       // slow near top (90)
            }
            else if (position < 65) {
                lift_motors.move(127);      // normal speed
            }
            else {
                lift_motors.brake();       // stop at top
            }
        }
        // LIFT DOWN
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (position <= 43 && position > 0 && clawOpen == false) {
                lift_motors.move(-20);      
            }
            else if (position > 43 && position <= 92 && clawOpen == false) {
                lift_motors.move(-60);     
            }
            else if (position <= 43 && position > 0) {
                lift_motors.move(-40);      
            }
            else if (position > 43 && position <= 92) {
                lift_motors.move(-127);     
            }
            else {
                lift_motors.brake();       // stop at top
            }
        }
        // NOTHING PRESSED
        else {
            lift_motors.move(0);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
            //claw toggle
            pros::Task spinclaw(spinClaw);
            //pros::delay(30);
        }
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
        {
            //roller
            if (rollerSpin) roller.brake();
            else if (!rollerSpin) roller.move(127);
            rollerSpin = !rollerSpin;
            pros::delay(30);
        }

        pros::delay(20);
    }

}
  
