#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"   
#include "main.h"
#include "lift.h"





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
    cascade.move(-127); 
    toggle.move(-127); 

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
    chassis.setPose(0,0,180);

    toggle.move(-127); 
    pros::delay(650); 
    toggle.move(0); 

    cascadeUp(150); 

    chassis.moveToPoint(0,15,350,{.forwards = false, .minSpeed = 70}, false);
    chassis.waitUntilDone(); 


    //score FIRST PIN
    chassis.turnToPoint(12,29, 280, {.forwards = false, .minSpeed = 80}, true);
    chassis.moveToPoint(11, 29, 300, {.forwards = false, .minSpeed = 80}, false);

    move(-30,0,0,550);
    chassis.waitUntilDone(); 

    cascadeDown(300); 


    clawy.set_value(true); 

    pros::delay(700); 


    //move BACK to position for wall PIN
    chassis.moveToPoint(-4.86, 18.8, 400, {.forwards = true, .minSpeed = 80}, false);
    chassis.turnToHeading(302,600); 

    //go to WALL PIN
    chassis.moveToPoint(11.3, 12.5, 1000, {.forwards = false, .maxSpeed = 80}, false);

    //position for WALL PIN
    rightMotors.move(-100);
    pros::delay(500); 
    rightMotors.move(0); 
    move(-50,0,0,250);
    clawy.set_value(false); 


    pros::delay(300); 
    cascadeUp(200); 


    leftMotors.move(-100); 
    pros::delay(200); 
    leftMotors.move(0); 

    biasedSwing(120, -80, 175);

    leftMotors.move(-100); 
    pros::delay(275); 
    leftMotors.move(0); 

    pros::delay(275); 
    

    //move back to align with goal 
    chassis.moveToPoint(-13.4, 12.89, 1000, {.forwards = true, .maxSpeed = 75}, false);

    cascadeUp(300); 

    chassis.turnToPoint(8.52, 12.5, 700, {.forwards = false, .maxSpeed = 65, .minSpeed = 30}, true);

    chassis.moveToPoint(8.52, 14.7, 900, {.forwards = false, .maxSpeed = 80}, false);
    pros::delay(200);

    move(-45,0,0,250);

    cascadeDown(400); 


    clawy.set_value(true); 

  //move back
    
    chassis.turnToPoint(0,13, 100, {.forwards = true, .minSpeed = 70}, true);
    chassis.moveToPoint(0,13, 800, {.forwards = true, .minSpeed = 70}, false);

    chassis.turnToHeading(410,800);
    

//    //chassis.turnToPoint(-10.96,7.37, 100, {.forwards = false, .minSpeed = 70}, true);
    chassis.moveToPoint(-16.5,6.6,1000,{.forwards = false, .maxSpeed = 80}, false);



    leftMotors.move(-100);
    pros::delay(500); 
    leftMotors.move(0); 
    move(-50,0,0,250);
    clawy.set_value(false); 


    pros::delay(300); 
    cascadeUp(200); 

    rightMotors.move(-100); 
    pros::delay(200); 
    rightMotors.move(0); 

    biasedSwing(-80, 120, 200);

    rightMotors.move(-100); 
    pros::delay(275); 
    rightMotors.move(0); 

    //  pros::delay(275); 

    //  chassis.turnToHeading(180,1000); 

}
















void threeStack() {


    chassis.setPose(0,0,180);


    toggle.move(-127); 
    pros::delay(550); 
    toggle.move(0); 
    

    chassis.moveToPoint(0,12,400,{.forwards = false, .minSpeed = 70}, true);



    cascade.move(127); 
    pros::delay(200);
    cascade.move(0);

    chassis.turnToPoint(9.9, 23.2, 300, {.forwards = false, .minSpeed = 70}, true);
    chassis.moveToPoint(8.9, 23.2, 1000, {.forwards = false, .minSpeed = 70}, false);

    move(-30,0,0,400);

    cascade.move(-90);
    pros::delay(200);
    cascade.move(0); 
    
    pros::delay(200);
   // move(-30,0,0,200);
    clawy.set_value(true); 
    pros::delay(300); 
    chassis.moveToPoint(5.44,28.15, 800, {.maxSpeed = 70}, false);
   
    // cascade.move(-127); 
    // pros::delay(100); 
    // cascade.move(0); 

    // // //go to first pin
    // chassis.turnToPoint(20.5, 39.5, 300, {.forwards = false,.minSpeed = 60}, true); 
    // chassis.moveToPoint(20.5, 39.5,1000, {.forwards = false,.maxSpeed = 45}, false);
    
    // timeLift(-50, 300); 
    // pros::delay(100); 
    // //roller.move(0); 
    // clawOpeny(); 


    // // //back up to align with next pin
    // chassis.moveToPoint(0.06, 16.5, 300, {.minSpeed = 60}, false);
    // // //go to pick up pins

    // chassis.turnToHeading(-141,25);
    // timeLift(-50,150); 

    // // chassis.turnToPoint(13.8, 36.5,1000, {.forwards = false}, true); 

    // //get second PIN
    // chassis.turnToPoint(13.5, 37,1000, {.forwards = false}, true);
    // chassis.moveToPoint(13.5, 37,1000, {.forwards = false, .maxSpeed = 60}, false); 

    // move(-20,0,0,300); 
    // clawClose(); 
    // //roller.move(0); 

    
    // chassis.turnToHeading(-18,400); 
    // timeLift(80,500); 
    // chassis.turnToPoint(16.86, 24, 450, {.forwards = false});
    // chassis.moveToPoint(16.86, 24,700,{.forwards = false}, false); 

    // //score second PIN
    // move(-30,0,0,300); 
    // timeLift(-30,200); 
    // clawOpeny(); 

    // //move to Third PIN
    // chassis.moveToPoint(15.4, 35.4, 700);
    // chassis.turnToHeading(-78,350);


    // timeLift(-50,380); 

    // //take third PIN
    // chassis.turnToPoint(38.25, 17.25, 400, {.forwards = false}); 
    // chassis.moveToPoint(38.25, 17.25, 650, {.forwards = false}, false);
    // chassis.moveToPoint(38.25, 17.25, 280, {.forwards = false, .maxSpeed = 30}, false);


    // clawClose(); 
    // //roller.move(0); 

    // timeLift(90,750); 

    // pros::delay(100); 
    

    // chassis.turnToHeading(76,400); 



    // chassis.turnToPoint(27.27,19.8, 450, {.forwards = false});
    // chassis.moveToPoint(27.27,19.8, 600, {.forwards = false}, false);
    // move(-30,0,0,300); 

    // timeLift(-60,400); 
    // clawOpeny(); 


}

// void skills() {

//     roller.move(127); 
//     pros::Task clawyclosey(clawClose);
//     //pros::delay(100);
//     chassis.setPose(-1,0,-180);

//     timeLift(127,250);
//     timeLift(-100,300);
    


//     pros::delay(200); 
    
    
//     chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
//     timeLift(90,300);
    
//     //go to first pin
//     chassis.turnToPoint(10.65, 14.5, 300, {.forwards = false,.minSpeed = 60}, true); 
//     //pros::delay(20); 
//     chassis.moveToPoint(10.65, 14.5, 500, {.forwards = false,.minSpeed = 45}, false);
    
//     timeLift(-50, 300); 
//     pros::delay(100); 
//     roller.move(0); 
//     clawOpeny(); 


//     // //back up to align with next pin
//     chassis.moveToPoint(0.06, 16.5, 300, {.minSpeed = 60}, false);
//     // //go to pick up pins

//     chassis.turnToHeading(-141,25);
//     timeLift(-50,150); 

//     // chassis.turnToPoint(13.8, 36.5,1000, {.forwards = false}, true); 

//     //get second PIN
//     roller.move(127); 
//     chassis.turnToPoint(13.5, 37,1000, {.forwards = false}, true);
//     chassis.moveToPoint(13.5, 37,1000, {.forwards = false, .maxSpeed = 60}, false); 

//     move(-20,0,0,300); 
//     clawClose(); 
//     roller.move(0); 

    
//     chassis.turnToHeading(-18,400); 
//     timeLift(80,500); 
//     chassis.turnToPoint(16.86, 24, 450, {.forwards = false});
//     chassis.moveToPoint(16.86, 24,700,{.forwards = false}, false); 

//     //score second PIN
//     move(-30,0,0,300); 
//     timeLift(-30,200); 
//     clawOpeny(); 

//     //move to Third PIN
//     chassis.moveToPoint(15.4, 35.4, 700);
//     chassis.turnToHeading(-78,350);


//     timeLift(-50,380); 

//     //take third PIN
//     roller.move(127);
//     chassis.turnToPoint(38.25, 17.25, 400, {.forwards = false}); 
//     chassis.moveToPoint(38.25, 17.25, 650, {.forwards = false}, false);
//     chassis.moveToPoint(38.25, 17.25, 280, {.forwards = false, .maxSpeed = 30}, false);


//     clawClose(); 
//     roller.move(0); 

//     timeLift(90,750); 

//     pros::delay(100); 
    

//     chassis.turnToHeading(76,400); 



//     chassis.turnToPoint(27.27,19.8, 450, {.forwards = false});
//     chassis.moveToPoint(27.27,19.8, 600, {.forwards = false}, false);
//     move(-30,0,0,300); 

//     timeLift(-60,400); 
//     clawOpeny(); 

    

//     //PARK
//     chassis.moveToPoint(41.1, 19.7, 1000, {}, false); 
//     //move (30,0,0,800); 

//     chassis.turnToHeading(145,600, {},false);

//     move(-80,0,0,1200);

// }

































//GRAVEYARD WHERE AUTOS GO TO DIE

// void oneStack() {
//    chassis.setPose(0,0,-180);

// //    lift_motors.move(127); 
// //    pros::delay(650); 
// //    lift_motors.move(-127); 
// //    pros::delay(800); 
// //    lift_motors.move(0); 
   
//     chassis.moveToPoint(0,17.5, 1000, {.forwards = false}, false);

//     //lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   
//     chassis.turnToPoint(18.6, 15.5, 1000, {.forwards = false}, true); 
   
//     //lift lift 
//     lift_motors.move (80);
//     pros::delay(600);
//     lift_motors.move(0); 
//     pros::delay(600);
    
    
//     chassis.moveToPoint(18.6,15.5, 1000, {.forwards = false}, false);
//     lift_motors.move(-50);
//      move(-25,0,0,700); 
//     //pros::delay(50);
//     claw.set_value(false);
//     lift_motors.move(0); 

//     //go back
//     chassis.moveToPoint(4.6, 18.5, 800, {}, false);

//     //go to the grab second thing
//     chassis.turnToPoint(19.6, 35.75, 1000, {.forwards = false}, true);

//     lift_motors.move (60);
//     pros::delay(500);
//     lift_motors.move(0); 
//     //pros::delay(600);
    
    
//     chassis.moveToPoint(19.8, 35.75, 1000, {.forwards = false, .maxSpeed = 55}, false);
//     pros::delay(300);
//     move(-30,0,0,350);
//     claw.set_value(true); 

//     lift_motors.move (90);
//     pros::delay(400);
//     lift_motors.move(0); 
//     pros::delay(600);
//     //go back
//     chassis.moveToPoint(8.62, 19.5, 1000, {}, false);

//     //go to score
//     chassis.turnToPoint(19.8, 13.8, 1000, {.forwards = false, .maxSpeed = 50});

//     lift_motors.move (90);
//     pros::delay(500);
//     lift_motors.move(0); 
//     pros::delay(600);
    
//     chassis.moveToPoint(19, 13.8, 1000, {.forwards = false});
//     move(-40,0,0,630); 

//     pros::delay(800);
//     lift_motors.move (-50);
//     pros::delay(300);
//     lift_motors.move(0); 
//     pros::delay(500);

//     claw.set_value(false); 

//     move(40,0,0,900);


// }

// void passiveClose() {
//     pros::Task clawyclosey(clawClose);
//     //pros::delay(100);
//     chassis.setPose(0,0,-180);

//     timeLift(127,250);
//     timeLift(-100,300);

//     pros::delay(200); 
    
    
//     chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
//     timeLift(90,300);
    
//     //go to first pin
//     chassis.turnToPoint(10.65, 15.86, 300, {.forwards = false,.minSpeed = 60}, true); 
//     //pros::delay(20); 
//     chassis.moveToPoint(10.65, 15, 500, {.forwards = false,.minSpeed = 45}, false);

//     timeLift(-50, 270); 
//     pros::delay(20); 
//     clawOpeny(); 

//     //back up to align with the pin we must chomp!!!!
//     chassis.moveToPoint(1.77, 13.59, 850);
//     pros::delay(20);
//     clawClose();
//     clawy.move(50);
//     pros::delay(80); 
//     clawy.brake();     
//     roller.move(127);

//     //chassis.turnToHeading(-40, 300, {}, false);

//     //move to chompy pin
//     chassis.turnToPoint(-15.7, 11, 500, {.forwards = false});
//     chassis.moveToPoint(-15.7, 11, 800, {.forwards = false, .maxSpeed = 35}, true);
//     pros::delay(300);

//     // chassis.turnToPoint(8, 1, 500, {.forwards = false});
//     // chassis.moveToPoint(8, 1, 800, {.forwards = false, .maxSpeed = 35}, false);

//     // move(-30, 0,0,500);

//     // rightMotors.move(-30); 
//     // pros::delay(600);
//     // clawClose(); 
//     // rightMotors.brake();
//     // roller.brake();
//     // clawy.move(-40);

// }


// void passiveFar() {
    

//     pros::Task clawyclosey(clawClose);
//     //pros::delay(100);

//     roller.move(127); 
//     chassis.setPose(1,0,180);

//     timeLift(127,250);
//     timeLift(-100,400);

//     pros::delay(100); 

    


//     chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
//     timeLift(90,300);

//     // go to first pin
//     chassis.turnToPoint(-10.65, 13.8, 300, {.forwards = false,.minSpeed = 60}, true); 
//     //pros::delay(20); 
//     chassis.moveToPoint(-10.65, 13.8, 475, {.forwards = false,.minSpeed = 45}, false);

//     timeLift(-50, 300); 
//     pros::delay(20); 
//     //roller.move(0); 
//     clawOpeny(); 


//     // back up to align with next pin
//     chassis.moveToPoint(-0.06, 16.5, 300, {.minSpeed = 60}, false);
//     // go to pick up pins



//     // //move to chompy pin
    
//     chassis.turnToPoint(-20, 7, 500, {.forwards = false});
//     clawClose(); 
//     timeLift(-50,150); 
//     chassis.moveToPoint(-20, 7, 800, {.forwards = false, .maxSpeed = 35}, false);


//     // chassis.turnToPoint(-20, 7, 500, {.forwards = false});
//     // chassis.moveToPoint(-20, 7, 800, {.forwards = false, .maxSpeed = 35}, false);


//     // move(-30, 0,0,500);

//     // rightMotors.move(-30); 
//     // pros::delay(600);
//     // clawClose(); 
//     // rightMotors.brake();
//     // roller.brake();
//     // clawy.move(-40);

// }

// void threeFar() {
//     pros::Task clawyclosey(clawClose);
//     //pros::delay(100);

//     roller.move(127); 
//     chassis.setPose(1,0,180);

//     timeLift(127,350);
//     timeLift(-100,350);

//     pros::delay(100); 

    


//     chassis.moveToPoint(0,7, 400, {.forwards = false, .minSpeed = 70}, false);
//     timeLift(90,300);

//     // go to first pin
//     chassis.turnToPoint(-10.65, 13.8, 300, {.forwards = false,.minSpeed = 60}, true); 
//     //pros::delay(20); 
//     chassis.moveToPoint(-10.65, 13.8, 475, {.forwards = false,.minSpeed = 45}, false);

//     timeLift(-50, 300); 
//     pros::delay(20); 
//     //roller.move(0); 
//     clawOpeny(); 


//     // back up to align with next pin
//     chassis.moveToPoint(-0.06, 16.5, 300, {.minSpeed = 60}, false);
//     // go to pick up pins

//     chassis.turnToHeading(165,200);
//     timeLift(-50,150); 

    

//     // get second PIN
//     roller.move(127);
//     chassis.turnToPoint(-13, 37,700, {.forwards = false}, true);
//     chassis.moveToPoint(-13, 37,1000, {.forwards = false, .maxSpeed = 60}, false); 

//     move(-25,0,0,400); 
//     clawClose(); 
//     //roller.move(0); 


//     chassis.turnToHeading(18,400); 
//     timeLift(80,500); 
//     chassis.turnToPoint(-17.86, 24, 450, {.forwards = false});
//     chassis.moveToPoint(-17.86, 24,600,{.forwards = false}, false); 

//     // // score second PIN
//     move(10,0,0,100); 
//     pros::delay(50);
//     timeLift(-40,300); 
//     clawOpeny(); 

//     // // move to Third PIN
//     chassis.moveToPoint(-14.4, 35.4, 700);
//     chassis.turnToHeading(76,500);


//     timeLift(-50,380); 

//     // // // take third PIN
//     roller.move(130);
//     chassis.turnToPoint(-42.7, 25.5, 400, {.forwards = false}); 
//     chassis.moveToPoint(-42.7, 25.5, 650, {.forwards = false}, false);
//     chassis.moveToPoint(-42.7, 25.5, 280, {.forwards = false, .maxSpeed = 30}, false);

//     // chassis.turnToPoint(38.25, 17.25, 400, {.forwards = false}); 
//     // chassis.moveToPoint(38.25, 17.25, 650, {.forwards = false}, false);
//     // chassis.moveToPoint(38.25, 17.25, 280, {.forwards = false, .maxSpeed = 30}, false);

//     clawClose(); 
//     //roller.move(0); 

//     timeLift(90,750); 

//     pros::delay(100); 


//     chassis.turnToHeading(-106,300); 


//     chassis.turnToPoint(-34,17.5, 300, {.forwards = false});
//     chassis.moveToPoint(-34,17.5, 300, {.forwards = false, .maxSpeed = 80}, false);
//     chassis.moveToPoint(-34,17.5, 300, {.forwards = false, .maxSpeed = 30}, false);

//     timeLift(-50,400); 
//     clawOpeny();
// }







