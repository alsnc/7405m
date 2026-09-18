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
    leftMotors({12,14,13},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {-17,-19,-18},
    pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

lemlib::Drivetrain drivetrain(&leftMotors,  // left motor group
                              &rightMotors, // right motor group
                              12,           // 10 inch track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm is 450
                              2    // horizontal drift is 2 (for now)
);

pros::Imu imu(1);

pros::Rotation horizontal_encoder(9); // odom sensor
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
pros::MotorGroup lift_motors ({-11,20},pros::v5::MotorGears::green /*to be specified!*/,pros::v5::MotorEncoderUnits::degrees); // the lift has two motors

//Pneumatics

pros::adi::DigitalOut clawWrist('B', false); //false is outwards
pros::adi::DigitalOut claw('A', true);


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


    // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y, pose.theta,
    // vertical_rot.get_position());
    // pros::lcd::print(2, "right distance sensor: %f", right_sensor.get());
    // pros::lcd::print(3, "front distance sensor: %f", front_sensor.get());
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

  // pros::delay(4000);
  pros::delay(3000);


  // autonSelectorStart();
  pros::Task screenTask(screen);
  //pros::Task jam(antiJam);

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

  //chassis.calibrate();
  pros::delay(3000);
  chassis.setPose(0, 0, 0);

  // horLift.set_value(false);
  // verLift.set_value(false);

  chassis.moveToPoint(0,28, 3000); 
  chassis.turnToHeading(90,800); 

  chassis.moveToPoint(-15,28,3000);
  //chassis.turnToHeading(270,1000);
}

void opcontrol() {

  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  //scraper.set_value(false);
    bool lastClaw = true;

    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        chassis.arcade(leftY, rightX);

        runIntake();

        //yooo this is in centidegrees I'm stupid
        double position = liftDeg.get_position()/100;

        // LIFT UP
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            clawWrist.set_value(false);
            if (position >= 65 && position < 90) {
                lift_motors.move(40);       // slow near top (90)
            }
            else if (position < 65) {
                lift_motors.move(127);      // normal speed
            }
            else {
                lift_motors.move(0);        // stop at top
            }
        }

        // LIFT DOWN
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            clawWrist.set_value(false);
            if (position <= 43 && position > 0) {
                lift_motors.move(-40);      
            }
            else if (position > 43 && position <= 92) {
                lift_motors.move(-127);     
            }
            else {
                lift_motors.move(0);        
            }
        }

        // NOTHING PRESSED
        else {
            lift_motors.move(0);
        }

        // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        // {
        //     if (lastClaw)
        //     {
        //         claw.set_value(false);
        //         lastClaw = true;
        //     }
        //     else
        //     {
        //         claw.set_value(true);
        //         lastClaw = false;
        //     }
        // }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) claw.set_value(true);
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) claw.set_value(false);

        pros::delay(20);
    }

}
  
