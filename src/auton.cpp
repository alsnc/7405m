#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"   
#include "main.h"
#include <ctime>



bool AC = false;
int max; 

void clawClose() {
    clawy.set_value(false); 
}

void clawOpeny() {
    clawy.set_value(true); 
}

void cascadeUp(int time) {
    cascade.move(127); 
    toggle.move(127); 

    pros::delay(time); 
    cascade.move(0); 
    toggle.move(0); 
}

void cascadeDown(int time) {
    cascade.move(-70); 
    toggle.move(-70); 

    pros::delay(time); 
    cascade.move(0); 
    toggle.move(0); 
}

void biasedSwing(int rightSpeed, int leftSpeed, int time) {
    rightMotors.move(rightSpeed);
    leftMotors.move(leftSpeed);

    pros::delay(time);

    rightMotors.move(0);
    leftMotors.move(0);
}


void autoclamp(void*) {
    while (true) {

        if (AC) {
            int distance = clampie.get();

            if (distance > 0 && distance < max) {
                clawy.set_value(false);
            }
        }

        pros::delay(5);
    }
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




void awp() {

    pros::Task autoclampTask(autoclamp, nullptr);

    chassis.setPose(0,0,180);

    toggle.move(-127); 
    pros::delay(650); 
    toggle.move(0); 

    cascadeUp(175); 

    //MOVE FORWARD TO ALIGN WITH ALLIANCE GOAL
    chassis.moveToPoint(0,15,350,{.forwards = false, .minSpeed = 70}, false);
    chassis.waitUntilDone(); 


    //MOVE TO FIRST SCORE
    chassis.turnToPoint(12,27, 280, {.forwards = false, .minSpeed = 80}, true);
    chassis.moveToPoint(11, 27, 300, {.forwards = false, .minSpeed = 80}, false);

    move(-30,0,0,550);
    chassis.waitUntilDone(); 

    //SCORE ALLIANCE PIN
    cascadeDown(100); 
    clawy.set_value(true); 
    pros::delay(700); 

    
    //MOVE BACK TO ALIGN
    chassis.moveToPoint(-4.86, 18.8, 400, {.forwards = true, .minSpeed = 80}, false);
    chassis.turnToHeading(302,600); 

    //go to WALL PIN
    chassis.moveToPoint(11.3, 12.5, 1100, {.forwards = false, .maxSpeed = 70}, false);

    cascadeDown(150); 


    //position for WALL PIN STRAIGHT
    rightMotors.move(-100);
    pros::delay(500); 
    rightMotors.move(0); 
    move(-50,0,0,250);
    clawy.set_value(false); 
    pros::delay(300); 
    cascadeUp(300); 


    //GO OUT OF WALL PIN
    move(-40,0,0,200); 
    chassis.turnToHeading(270,400); 
    chassis.moveToPoint(36.75, 6,1000, {.forwards = false, .maxSpeed = 80}, false);

    
    //TURN TO SCORE FIRST PIN
    chassis.turnToHeading(140, 700);
    cascadeUp(250); 
    chassis.moveToPoint(40.44, 12.67, 900, {.forwards = false, .maxSpeed = 80}, false);

   
    //SCORE FIRST PIN
    move(-45,0,0,200);

    cascade.move(-80); 
    toggle.move(-80); 
    pros::delay(250); 
    cascade.move(0); 
    toggle.move(0);
    pros::delay(100); 
    clawOpeny(); 
    
    
    //GO OUT OF FIRST GOAL
    chassis.turnToHeading(-237,1000); 
    // chassis.turnToPoint(50.88,0.69, 100, {.forwards = true, .minSpeed = 70}, true);
    chassis.moveToPoint(48.88,0.69,550, {.forwards = true, .maxSpeed = 50}, false);

    cascadeDown(150); 
    chassis.turnToHeading(219,400); 

    chassis.waitUntilDone(); 


    //MOVE TO SECOND PIN
    
    AC = true; 
    max = 70;
    chassis.moveToPoint(40.71,7.75,1000,{.forwards = false, .maxSpeed = 40}, false);
   
    pros::delay(100); 
    AC = false; 

    // // //ALIGN TOWARDS SCORING
    chassis.turnToHeading(185,300); 


    cascadeUp(250); 
   
    // // //SCORE SECOND
    // chassis.turnToPoint(60.5,35,200, {.forwards = false, .minSpeed = 40}, true);
    // chassis.moveToPoint(60.5,35,1100,{.forwards = false, .maxSpeed = 80}, false);
    // move(-30,0,0,200);

    // cascade.move(-60); 
    // toggle.move(-60); 
    // pros::delay(200); 
    // cascade.move(0); 
    // toggle.move(0);
    // clawOpeny(); 

    // // //MOVE BACK TO THIRD PIN
    // chassis.moveToPoint(53.7, 19.8, 500, {.forwards = true}, false);
    // chassis.turnToHeading(135.2,800); 
    // cascadeDown(300); 


    // // //MOVE TO THIRD PIN
    // AC = true; 
    // max = 75; 
    // chassis.turnToPoint(44.5, 39, 300 ,{.forwards = false}, true);
    // chassis.moveToPoint(44.5, 39,1000,{.forwards = false, .maxSpeed = 40}, false);

    // pros::delay(500); 
    // AC =false; 

    // //GO TO SCORE THIRD PIN
    // chassis.turnToHeading(69,1000);
    // cascadeUp(400);   

    // chassis.turnToPoint(-10.82, 29.14, 300, {.forwards = false}, true); 
    // chassis.moveToPoint(-10.82, 29.14, 1000, {.forwards = false, .maxSpeed = 90}, false); 
    
    // move(-30,0,0,300); 

    // //SCORE THIRD PIN
    // cascadeDown(300); 
    // clawOpeny(); 
}














