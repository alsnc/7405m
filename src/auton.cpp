#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"   
#include "main.h"



//  void sevenBall() {
//     pros::delay(100); 
// }

void move(double power, double turn, bool swing=false, double time=10000) {
    chassis.cancelAllMotions();

    int left = power + turn;
    int right = power - turn;
    // double t = time; 

    if (swing && left < 0) {left = 0;}
    if (swing && right < 0) {right = 0;}

    leftMotors.move(left);
    rightMotors.move(left);
    pros::delay(time);
    leftMotors.brake();
    rightMotors.brake();
    // left_center_motor.move(left);
    // left_back_motor.move(left);
    // right_front_motor.move(left);
    // right_center_motor.move(left);
    // right_back_motor.move(left);
}




void oneStack() {
   chassis.setPose(0,0,-180);

   lift_motors.move(127); 
   pros::delay(650); 
   lift_motors.move(-127); 
   pros::delay(800); 
   lift_motors.move(0); 
   
    chassis.moveToPoint(0,17.5, 1000, {.forwards = false}, false);

    //lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   
    chassis.turnToPoint(18.6, 15.5, 1000, {.forwards = false}, true); 
   
    //lift lift 
    lift_motors.move (80);
    pros::delay(600);
    lift_motors.move(0); 
    pros::delay(600);
    
    
    chassis.moveToPoint(18.6,15.5, 1000, {.forwards = false}, false);
    lift_motors.move(-50);
     move(-25,0,0,700); 
    //pros::delay(50);
    claw.set_value(false);
    lift_motors.move(0); 

    //go back
    chassis.moveToPoint(4.6, 18.5, 800, {}, false);

    //go to the grab second thing
    chassis.turnToPoint(19.6, 35.75, 1000, {.forwards = false}, true);

    lift_motors.move (60);
    pros::delay(500);
    lift_motors.move(0); 
    //pros::delay(600);
    
    
    chassis.moveToPoint(19.8, 35.75, 1000, {.forwards = false, .maxSpeed = 55}, false);
    pros::delay(300);
    move(-30,0,0,350);
    claw.set_value(true); 

    lift_motors.move (90);
    pros::delay(400);
    lift_motors.move(0); 
    pros::delay(600);
    //go back
    chassis.moveToPoint(8.62, 19.5, 1000, {}, false);

    //go to score
    chassis.turnToPoint(19.8, 13.8, 1000, {.forwards = false, .maxSpeed = 50});

    lift_motors.move (90);
    pros::delay(500);
    lift_motors.move(0); 
    pros::delay(600);
    
    chassis.moveToPoint(19, 13.8, 1000, {.forwards = false});
    move(-40,0,0,630); 

    pros::delay(800);
    lift_motors.move (-50);
    pros::delay(300);
    lift_motors.move(0); 
    pros::delay(500);

    claw.set_value(false); 

    move(40,0,0,900);


}

void threeStack() {

    chassis.setPose(0,0,-180);
    chassis.moveToPoint(0,17.5, 1000, {.forwards = false}, false);

    //lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   
    chassis.turnToPoint(18.6, 15.5, 1000, {.forwards = false}, true); 
   
    //lift lift 
    lift_motors.move (90);
    pros::delay(600);
    lift_motors.move(0); 
    pros::delay(600);
    
    
    chassis.moveToPoint(18.6,15.5, 1000, {.forwards = false}, false);
    lift_motors.move(-50);
     move(-25,0,0,700); 
    //pros::delay(50);
    claw.set_value(false);
    lift_motors.move(0); 

    //go back
    chassis.moveToPoint(4.6, 18.5, 800, {}, false);

    //go to the grab second thing
    chassis.turnToPoint(19.6, 35.75, 1000, {.forwards = false}, true);

    lift_motors.move (60);
    pros::delay(500);
    lift_motors.move(0); 
    //pros::delay(600);
    
    
    chassis.moveToPoint(19.8, 35.75, 1000, {.forwards = false, .maxSpeed = 55}, false);
    pros::delay(300);
    move(-30,0,0,400);
    claw.set_value(true); 

    lift_motors.move (90);
    pros::delay(400);
    lift_motors.move(0); 
    pros::delay(600);

    chassis.turnToHeading(-18,1000); 

    

    lift_motors.move (90);
    pros::delay(500);
    lift_motors.move(0); 
    pros::delay(600);

    
    
    // chassis.moveToPoint(19, 13.8, 1000, {.forwards = false});
    // move(-40,0,0,630); 

    // pros::delay(800);
    // lift_motors.move (-50);
    // pros::delay(300);
    // lift_motors.move(0); 
    // pros::delay(500);

    // claw.set_value(false); 

    // move(40,0,0,900);

}







