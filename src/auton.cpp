#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"   
#include "main.h"
#include "lift.h"



//  void sevenBall() {
//     pros::delay(100); 
// }


void clawOpeny() {
    clawy.move(127);
    pros::delay(600); 
    clawy.move(40); 
}

void clawClose() {
    clawy.move(-127);
    pros::delay(600); 
    clawy.brake();
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

void passiveClose() {
    pros::Task clawyclosey(clawClose);
    //pros::delay(100);
    chassis.setPose(0,0,-180);

    timeLift(127,250);
    timeLift(-100,300);

    pros::delay(200); 
    
    
    chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
    timeLift(90,300);
    
    //go to first pin
    chassis.turnToPoint(10.65, 15.86, 300, {.forwards = false,.minSpeed = 60}, true); 
    //pros::delay(20); 
    chassis.moveToPoint(10.65, 15, 500, {.forwards = false,.minSpeed = 45}, false);

    timeLift(-50, 270); 
    pros::delay(20); 
    clawOpeny(); 

    //back up to align with the pin we must chomp!!!!
    chassis.moveToPoint(1.77, 13.59, 850);
    pros::delay(20);
    clawClose();
    clawy.move(50);
    pros::delay(80); 
    clawy.brake();     
    roller.move(127);

    chassis.turnToHeading(-40, 300, {}, false);

    //move to chompy pin
    chassis.turnToPoint(12.5, 1, 500, {.forwards = false});
    chassis.moveToPoint(12.5, 1, 800, {.forwards = false, .maxSpeed = 35}, false);

    move(-30, 0,0,500);

    rightMotors.move(-30); 
    pros::delay(600);
    clawClose(); 
    rightMotors.brake();
    roller.brake();
    clawy.move(-40);

}

void threeFar() {
    pros::Task clawyclosey(clawClose);
    //pros::delay(100);
    chassis.setPose(0,0,180);

    timeLift(127,250);
    timeLift(-100,300);

    pros::delay(200); 


    chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
    timeLift(90,300);

    // go to first pin
    chassis.turnToPoint(-10.65, 15.86, 300, {.forwards = false,.minSpeed = 60}, true); 
    //pros::delay(20); 
    chassis.moveToPoint(-10.65, 15, 500, {.forwards = false,.minSpeed = 45}, false);

    timeLift(-50, 300); 
    pros::delay(20); 
    clawOpeny(); 


    // back up to align with next pin
    chassis.moveToPoint(-0.06, 16.5, 300, {.minSpeed = 60}, false);
    // go to pick up pins

    chassis.turnToHeading(165,200);
    timeLift(-50,150); 

    

    // get second PIN
    roller.move(127);
    chassis.turnToPoint(-13, 37,700, {.forwards = false}, true);
    chassis.moveToPoint(-13, 37,1000, {.forwards = false, .maxSpeed = 60}, false); 

    move(-25,0,0,400); 
    clawClose(); 
    roller.move(0); 


    chassis.turnToHeading(18,400); 
    timeLift(80,500); 
    chassis.turnToPoint(-17.86, 24, 450, {.forwards = false});
    chassis.moveToPoint(-17.86, 24,700,{.forwards = false}, false); 

    // // score second PIN
    move(30,0,0,300); 
    timeLift(-30,200); 
    clawOpeny(); 

    // // move to Third PIN
    // chassis.moveToPoint(-15.4, 35.4, 700);
    // chassis.turnToHeading(78,350);


    // timeLift(-50,380); 

    // // take third PIN
    // roller.move(127);
    // chassis.turnToPoint(-39.7, 17.5, 400, {.forwards = false}); 
    // chassis.moveToPoint(-39.7, 17.5, 900, {.forwards = false}, false);

    // clawClose(); 
    // roller.move(0); 

    // timeLift(90,750); 

    // pros::delay(100); 


    // chassis.turnToHeading(-76,400); 



    // chassis.turnToPoint(-27.27,19.8, 450, {.forwards = false});
    // chassis.moveToPoint(-27.27,19.8, 600, {.forwards = false}, false);

    // timeLift(-60,400); 
    // clawOpeny();
}
void threeStack() {

    pros::Task clawyclosey(clawClose);
    //pros::delay(100);
    chassis.setPose(0,0,-180);

    timeLift(127,250);
    timeLift(-100,300);

    pros::delay(200); 
    
    
    chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
    timeLift(90,300);
    
    //go to first pin
    chassis.turnToPoint(10.65, 15.86, 300, {.forwards = false,.minSpeed = 60}, true); 
    //pros::delay(20); 
    chassis.moveToPoint(10.65, 15, 500, {.forwards = false,.minSpeed = 45}, false);

    timeLift(-40, 300); 
    pros::delay(20); 
    clawOpeny(); 


    // //back up to align with next pin
    chassis.moveToPoint(0.06, 16.5, 300, {.minSpeed = 60}, false);
    // //go to pick up pins

    chassis.turnToHeading(-141,25);
    timeLift(-50,150); 

    // chassis.turnToPoint(13.8, 36.5,1000, {.forwards = false}, true); 

    //get second PIN
    roller.move(127); 
    chassis.turnToPoint(13.5, 37,1000, {.forwards = false}, true);
    chassis.moveToPoint(13.5, 37,1000, {.forwards = false, .maxSpeed = 60}, false); 

    move(-20,0,0,300); 
    clawClose(); 
    roller.move(0); 

    
    chassis.turnToHeading(-18,400); 
    timeLift(80,500); 
    chassis.turnToPoint(17.86, 24, 450, {.forwards = false});
    chassis.moveToPoint(17.86, 24,700,{.forwards = false}, false); 

    //score second PIN
    move(-30,0,0,300); 
    timeLift(-30,200); 
    clawOpeny(); 

    //move to Third PIN
    chassis.moveToPoint(15.4, 35.4, 700);
    chassis.turnToHeading(-78,350);


    timeLift(-50,380); 

    //take third PIN
    roller.move(127);
    chassis.turnToPoint(39.7, 17.5, 400, {.forwards = false}); 
    chassis.moveToPoint(39.7, 17.5, 900, {.forwards = false}, false);

    clawClose(); 
    roller.move(0); 

    timeLift(90,750); 

    pros::delay(100); 
    

    chassis.turnToHeading(76,400); 



    chassis.turnToPoint(27.27,19.8, 450, {.forwards = false});
    chassis.moveToPoint(27.27,19.8, 600, {.forwards = false}, false);

    timeLift(-60,400); 
    clawOpeny(); 

    //timeLift(-60,400); 

    //chassis.moveToPose(14,38,-145,2000, {.forwards = false,.lead =0.1, .minSpeed = 40}, false);
    // move(-50,0,0,300);
    // clawClose();  
    // chassis.turnToPoint(15, 38.1, 230, {.forwards = false, .minSpeed = 60}, true);
    // chassis.moveToPoint(15, 38.1, 600, {.forwards = false, .minSpeed = 60}, false);
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







