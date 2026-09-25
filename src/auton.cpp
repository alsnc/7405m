#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"   
#include "main.h"
#include "lift.h"



//  void sevenBall() {
//     pros::delay(100); 
// }

void clawOpen() {
    clawy.move(127); 
}

void clawClose() {
    clawy.move(-127); 
}

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

//    lift_motors.move(127); 
//    pros::delay(650); 
//    lift_motors.move(-127); 
//    pros::delay(800); 
//    lift_motors.move(0); 
   
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

    chassis.setPose(0,0,0);

    chassis.moveToPoint(0,6.5, 325, {.minSpeed = 70, .forwards = false}, true);
    timeLift(90,300);
    pros::delay(100); 
    
    chassis.turnToPoint(14.5, 12, 300, {.minSpeed = 60, .forwards = false}, true); 
    pros::delay(80); 
    //chassis.moveToPoint(13.3, 8.4, 465, { .minSpeed = 80}, false);

    //back up to align with next pin
    // chassis.moveToPoint(2.06, 14.09, 500, {.minSpeed = 60}, false);
    // //go to pick up pins
    // chassis.turnToPoint(18, 35.84, 230, {.minSpeed = 60}, true);
    // chassis.moveToPoint(18, 35.84, 600, {.minSpeed = 60}, false);
    // move(-50, 0, false, 100);
    
    // pros::delay(400);

    // //turn to goal
    // chassis.turnToHeading(-23, 500, {.minSpeed = 50}, false);
    // chassis.moveToPoint(21.1, 24.26, 500, {.minSpeed = 60}, false);

    // timeLift(80,500); 
    // clawOpen(); 
    // pros::delay(1000); //score




    // // //go backwards to get into the right position
    // // chassis.moveToPoint(8.46, 34.19, 430, {.minSpeed = 60}, true);
    // // chassis.turnToHeading(-65, 400, {}, false);
   
   
    // // //get next pin
    // // chassis.moveToPose(43.7, 14.5, -57.6, 1700, {.forwards = false, .lead = 0.4, .minSpeed = 80}, false); 
    // // pros::delay(600); 


    // // chassis.turnToHeading(73.1, 800); 

    // // chassis.moveToPoint(32, 12.2, 800, {.forwards = false, .minSpeed =70});

    // // pros::delay(800); 
    // // //get last pin

    // // chassis.moveToPoint(48.7, 16, 1000, {}, false); 
    // // //chassis.moveToPose(27, -4, 31, 1000, {.forwards = false, .lead = 0.4});
    // // chassis.turnToHeading(45.28, 900, {}, false);
    
    // // chassis.turnToPoint(41.90, 4.93, 800, {.forwards = false}, true); 
    // // chassis.moveToPoint(41.90, 4.93, 1000, {.forwards = false}, false);
    
    

    // // chassis.turnToPoint(25.6, -5.45, 800, {.forwards = false}, true); 
    // // chassis.moveToPoint(25.6, -5.45, 1000, {.forwards = false}, false); 
    // // // move(-30, -50,true,1000);
    
    // // //chassis.turnToPoint(43.9, 14.4, 200, {.forwards = false, .minSpeed = 60}, true);
    // // // chassis.turnToPoint(43.1, 15, 500,{.forwards = false, .minSpeed = 60}, true);
    // // // chassis.moveToPoint(43.1, 15.07, 500, {.forwards = false, .minSpeed = 60}, false);
    


    // // // //go back
    // // // chassis.moveToPoint(4.6, 18.5, 800, {}, false);

    // // // //go to the grab second thing
    // // // chassis.turnToPoint(19.6, 35.75, 1000, {.forwards = false}, true);

    // // // lift_motors.move (60);
    // // // pros::delay(500);
    // // // lift_motors.move(0); 
    // // // //pros::delay(600);
    
    
    // // // chassis.moveToPoint(19.8, 35.75, 1000, {.forwards = false, .maxSpeed = 55}, false);
    // // // pros::delay(300);
    // // // move(-30,0,0,350);
    // // // claw.set_value(true); 

    

}







