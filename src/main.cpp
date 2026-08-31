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
    leftMotors({1},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {-2},
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
    lateral(0, // proportional gain (kP) 
            0,    // integral gain (kI)
            0,    // derivative gain (kD)
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

// Lift
pros::MotorGroup lift_motors ({1,-10},pros::v5::MotorGears::green /*to be specified!*/,pros::v5::MotorEncoderUnits::degrees); // the lift has two motors

// Intake
pros::Motor intake (5,pros::v5::MotorGears::blue,pros::v5::MotorEncoderUnits::degrees); // I suppose the intake spins at highest speed? Putting it at port 1 for now



void screen() {
  // loop forever
  while (true) {
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y,
                     pose.theta);             // print the x position
    pros::lcd::print(1, "H: %f", pose.theta); // print the x position
    pros::lcd::print(2, "Lift: %d", liftDeg.get_position());
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
  vertical_encoder.reset_position();
  //liftDeg.reset_position();
  pros::lcd::initialize(); // initialize brain screen
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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

  // horLift.set_value(false);
  // verLift.set_value(false);
  
  leftMotors.move_velocity(90);
  rightMotors.move_velocity(90);
  pros::delay(900); 
  leftMotors.move_velocity(0);
  rightMotors.move_velocity(0);
  // chassis.setPose(0,0,0); 
  // chassis.moveToPoint(0,10,1000);


}
//lift parameters
  double liftTop = 85.5;
  double liftBottom = 0;


void opcontrol() {
  // horLift.set_value(true);
  // verLift.set_value(false);
  // scraper.set_value(false);
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  //scraper.set_value(false);

  
  double lastError = 0;
  double integral = 0;

  // PID constants
  double kP = 0.70;
  double kI = 0.02;
  double kD = 0.15;
  while (true) {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(leftY, rightX);

    // bool removerPressedNow
    // =controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    // wing.set_value(removerPressedNow);

        double position = liftDeg.get_position()/100.0;

  
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {

            if (position >= liftTop - 10) {
                lift_motors.move(120); // slow near top
            }
            else {
                lift_motors.move(127); // normal speed
            }
        }

        // LIFT DOWN
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      

        // Target is the bottom position
        double error = liftBottom - position;


        // -------------------------
        // INTEGRAL
        // -------------------------

        integral += error;

        // Anti-windup
        if (integral > 100) {
            integral = 100;
        }

        if (integral < -100) {
            integral = -100;
        }


        // -------------------------
        // DERIVATIVE
        // -------------------------

        double derivative = error - lastError;


        // -------------------------
        // PID OUTPUT
        // -------------------------

        double output =
            (kP * error) +
            (kI * integral) +
            (kD * derivative);


        // -------------------------
        // MOTOR OUTPUT LIMIT
        // -------------------------

        if (output > 127) {
            output = 127;
        }

        if (output < -127) {
            output = -127;
        }

        if (fabs(error) < 3) {

            lift_motors.move(0);

            // Reset PID memory
            integral = 0;
            lastError = 0;
        }

        else {

            lift_motors.move(output);

            lastError = error;
        }
    
      }
        // NOTHING PRESSED
        else {
            
            lift_motors.move(0);
        }

        pros::delay(20);

  //   //CLAW CONTROL
  //   if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) and push == false and pressed == false){
  //     push = true;
  //     piston.set_value(push);
  //     pressed = true;
  //   }
  //   else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) and push == true and pressed == false){
  //     push = false;
  //     piston.set_value(push);
  //     pressed = true;
  //   }

  //   if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
  //     pressed = false;
  //   }
  //   pros::delay(20);
  // }
}
}
  
