#include "autons.h"
#include "intake.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "autonselector.h"
#include "distanceReset.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include <cstdio>
#include <source_location>




void middleTimed(){
    scoreMiddle();
    pros::delay(500);
    stopIntake();
}

void middleTimeOptical() {
    intaking = true;
    while(intaking) {
        scoreMiddle();
        if(opticalSensor.get_proximity() > 50) { //need to tune this value - 0 (far) & 255 (near)
            stopIntake();
            intaking = false;
        }
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


void lowGoal(){
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    storageIn();
    chassis.moveToPoint(0, 36, 1000);
    // chassis.turnToPoint(10, 37.2, 650);
    // chassis.turnToHeading(90, 750, {}, false);
    // chassis.turnToPoint(4.9, 38, 700);
    chassis.turnToPoint(6.5, 39, 700, {}, false);



    
    scraper.set_value(true);
    // chassis.moveToPoint(4.9, 39, 700, {},false);
    chassis.moveToPoint(6.5, 39, 700, {},false);
    move(63, 0, false, 700);
    


    // chassis.moveToPoint(-20.22, 38.5, 1000, {.forwards=false}, false);
    // chassis.moveToPoint(-20.22, 40, 1000, {.forwards=false}, false);
    chassis.moveToPoint(-20.22, 39.7, 1000, {.forwards=false}, false);
    scraper.set_value(false);
    move(-50,0,false,250);
    scoreTop();
    pros::delay(1050);
    chassis.moveToPoint(2, 39.1, 1000);

    chassis.turnToPoint(-31.31, 1.62, 750,{}, false);
    storageIn();
    chassis.moveToPoint(-31.31, 1.62, 1000,{});
    // pros::delay(250);
    // bottomGoal();

    pros::delay(550);
    scraper.set_value(true);
    pros::delay(250);
    scraper.set_value(false);
    pros::delay(1000);
    chassis.turnToHeading(225, 500);
    fastBottomScore();
    pros::delay(500);

    
    // chassis.moveToPoint(-1.96, 27.61, 1000, {.forwards = false});
    // chassis.turnToPoint(-41.15, 22.7, 750);
    // chassis.moveToPoint(-41.15, 22.7, 1000);
    chassis.moveToPoint(-1.96, 25.6, 1000, {.forwards = false});
    chassis.turnToPoint(-41.63, 25.6, 750);
    chassis.moveToPoint(-41.63, 25.6, 1000);
    chassis.turnToHeading(-90, 750);


}

void soloAWPCedar() {
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    storageIn();
    chassis.moveToPoint(0, 36, 1000);
    // chassis.turnToPoint(10, 37.2, 650);
    // chassis.turnToHeading(90, 750, {}, false);
    // chassis.turnToPoint(4.9, 38, 700);
    chassis.turnToPoint(6.5, 39, 500,{},false);



    
    scraper.set_value(true);
    // chassis.moveToPoint(4.9, 39, 700, {},false);
    chassis.moveToPoint(6.5, 39, 500, {},false);
    move(63, 0, false, 700);
    


    // chassis.moveToPoint(-20.22, 38.5, 1000, {.forwards=false}, false);
    // chassis.moveToPoint(-20.22, 40, 1000, {.forwards=false}, false);
    chassis.moveToPoint(-20.22, 39.7, 1000, {.forwards=false}, false);
    scoreTop();
    scraper.set_value(false);
    move(-50,0,false,250);
    pros::delay(1050);
    chassis.moveToPoint(2, 39.1, 700);

    chassis.turnToPoint(-23.6, 9.5,750,{}, false);
    storageIn();
    chassis.moveToPoint(-23.6, 9.5,1000);
    pros::delay(700);
    scraper.set_value(true);
    pros::delay(200);
    scraper.set_value(false);
    chassis.turnToPoint(-23.17, -39.25, 450);
    chassis.moveToPoint(-23.17, -39.25, 1500);
    pros::delay(750);
    scraper.set_value(true);
    pros::delay(200);
    scraper.set_value(false);

    chassis.turnToPoint(-38.07, -25.38, 550,{.forwards = false});
    chassis.moveToPoint(-38.07, -25.38, 1000, {.forwards =false},false);
    // bottomGoal();
    move(-50,0,false,200);
    scoreMiddle();
    pros::delay(350);
   


    // chassis.turnToHeading(135, 700);
    // chassis.turnToPoint(-0.25, -60.1, 700);
    chassis.moveToPoint(-0.25, -60.1, 900, {});

    storageIn();
    // bottomGoal();
    // pros::delay(150);
    // storageIn();
    // chassis.turnToHeading(90, 750,{},false);
    // scraper.set_value(true);
    // chassis.moveToPoint(11.85, -61.07,1000, {}, false);

    // move(67, 0, false, 600);


    chassis.turnToPoint(-14.4, -63.6,600, {.forwards = false});
    chassis.moveToPoint(-14.4, -63.6,1000, {.forwards = false});
    pros::delay(1000);
    scraper.set_value(false);
    scoreTop();
    move(-50,0,false,250);
    // pros::delay(1300);
    // move(60,0,false,250);
    // pros::delay(200);
    // move(-70,0,false,250);





}


void leftSide3Plus4(){
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    storageIn();
    chassis.moveToPoint(-9.28, 29.41, 1000, {});
    pros::delay(600);
    scraper.set_value(true);
    // pros::delay(200);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false}, false);
    scraper.set_value(false);
    chassis.moveToPoint(7.38, 44.3, 1000, {.forwards = false}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(500);
    // fastBottomScore();
    // pros::delay(150);
    stopIntake();
    flappier.set_value(false);
    flappy.set_value(false);

    chassis.turnToHeading(-135, 300);
    chassis.moveToPoint(-36.5, 3.7, 1300, {});
    storageIn();
    chassis.turnToHeading(-177, 500, {}, false);
    scraper.set_value(true);
    pros::delay(175);
    chassis.moveToPoint(-38.2, -4.5, 1000);

    // //empty match loader 1
    chassis.cancelAllMotions();
    move(55, 0, false, 900);
    pros::delay(100);




    // // go back to goal 
    chassis.moveToPoint(-37.49, 23.99, 1000, {.forwards = false}, false);
    scraper.set_value(false);
    scoreTop();
    move(-50,0,false,250);
    pros::delay(1150);

    // move(50,0,false,350);
    // pros::delay(300);
    // move(-70,0,false,200);

    
    chassis.moveToPoint(-37, 9.62, 600, {},false);
    chassis.turnToPoint(-24.7, 21.02, 500, {.forwards = false});
    chassis.moveToPoint(-24.7, 21.02, 600, {.forwards = false});
    chassis.turnToPoint(-26, 43.39, 500, {.forwards = false});
    chassis.moveToPoint(-26, 43.39, 700, {.forwards = false});
    chassis.turnToHeading(-180, 200);





}



void bottomControl(){
    flingBlue = false;
    //descore.set_value(false);
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});
    chassis.turnToPoint(31.76, 17.53, 700, {.forwards = false});
    chassis.moveToPoint(31.76, 17.53, 2800,{.forwards = false, .maxSpeed = 75});
    //pros::delay(1000000);

    chassis.turnToHeading(-195.5, 1000);
    scraper.set_value(true);
    stopIntake();
    storageIn();

    chassis.moveToPoint(36.4,3.63, 1200, {}, false);

    chassis.cancelAllMotions();
    move(70, 0, false, 750);
    // pros::delay(750);
    //move(50, 0, false, 750);
    //pros::delay(1000);
    // move(50, 0.5,false, 500);
    // //back up
    // move(-75, 0, false, 300);
    
    chassis.moveToPoint(29.4, 29.9, 1000, {.forwards = false});
    // chassis.moveToPoint(29, 32.47, 1000, {.forwards = false});

    scoreTopAuto();
    scraper.set_value(false);

    pros::delay(2750);

    stopIntake();
    //move forward
    chassis.moveToPoint(31.7,22.54,700);
    chassis.turnToHeading(-73, 700);
    chassis.moveToPoint(9.7, 49.4, 700);


    chassis.moveToPoint(-50,15.1, 1000, {.forwards = false, .maxSpeed = 80});




}

void workskills() {
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    wing.set_value(true);
    storageIn();

    //moving to middle goal
    chassis.moveToPoint(-9.28, 29.41, 1000);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false});
    chassis.moveToPoint(7.38, 44.3, 800, {.forwards = false, .maxSpeed = 90}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(1500);
    // stopIntake();
    flappier.set_value(false);
    flappy.set_value(false);
    // score();

    //go to match loader
    chassis.turnToHeading(-135, 700);
    chassis.moveToPoint(-36.5, 3.7, 1500, {});
    chassis.turnToHeading(-177, 700, {}, false);
    scraper.set_value(true);
    pros::delay(450);
    storageIn();
    chassis.moveToPoint(-38.2, -4.5, 1000);

    // //empty match loader 1
    chassis.cancelAllMotions();
    move(50, 0, false, 1250);
    pros::delay(700);

    // go backwards for turn
    chassis.moveToPoint(-41.15, 3.2, 1000, {.forwards = false}, false);
    scraper.set_value(false);

    // chassis.turnToPoint(-50,15.1, 750, {.forwards = false}, false);
    // stopIntake();

    // chassis.moveToPoint(-50,15.1, 1000, {.forwards = false, .maxSpeed = 80});

    // //go to other side
    // chassis.turnToPoint(-46.73, 96.59, 750, {.forwards = false});
    // chassis.moveToPoint(-46.73, 96.59, 2500, {.forwards = false, .maxSpeed = 80}, false);


    chassis.turnToPoint(-51.5,15.1, 750, {.forwards = false}, false);
    stopIntake();


    chassis.moveToPoint(-51.5,15.1, 1000, {.forwards = false});
    
    // go to other side 
    chassis.turnToPoint(-45.5, 96.59, 750, {.forwards = false});
    chassis.moveToPoint(-45.5, 96.59, 2500, {.forwards = false}, false);


    // chassis.moveToPoint(-51.5,15.1, 1000, {.forwards = false, .maxSpeed = 80});
    
    // // go to other side 
    // chassis.turnToPoint(-45, 96.59, 750, {.forwards = false});
    // chassis.moveToPoint(-45, 96.59, 2500, {.forwards = false, .maxSpeed = 80}, false);





    // //score in long goal 1st time
    
    // OLD CODE 
    chassis.turnToPoint(-32.39, 94.79, 1000, {.forwards = false});
    chassis.moveToPoint(-32.39, 94.79, 1000, {.forwards = false});
    chassis.turnToPoint(-35, 83.20, 750, {.forwards = false});
    chassis.moveToPoint(-35, 83.20, 1000, {.forwards = false},false);



    // chassis.turnToPoint(-35, 94.79, 1000, {.forwards = false});
    // chassis.moveToPoint(-35, 94.79, 1000, {.forwards = false});
    // chassis.turnToPoint(-35, 83.20, 750, {.forwards = false});
    // chassis.moveToPoint(-35, 83.20, 1000, {.forwards = false},false);


    move(-50,0,false,300);
    // aligned to goal
    scoreTop();
    pros::delay(2500);

    // // //unload match loader 2
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(-35.5, 107, 1000, {}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(50,0,false, 1500);
    pros::delay(250);

    // //score in long goal again
    chassis.turnToPoint(-35, 83.20, 750, {.forwards = false});
    chassis.moveToPoint(-35, 83.20, 1000, {.forwards = false}, false);
    // stopIntake();     
    move(-60,0,false,400);
    pros::delay(100);
    scoreTop();
    pros::delay(2500);
    stopIntake();
    move(50,0,false,350);
    pros::delay(300);
    move(-60,0,false,200);

    chassis.moveToPoint(-33.4, 93.3, 1000);
    scraper.set_value(false);

    // chassis.turnToHeading(90, 750);

    chassis.turnToPoint(66, 97.2, 750);
    //loooong

    // MADE FASTER
    chassis.moveToPoint(66, 97.2, 2300, {}, false);

    chassis.turnToHeading(0.83,750);
    scraper.set_value(true);
    storageIn();

    chassis.moveToPoint(66, 108, 1000);
    // // //unload match loader 3
    
    pros::delay(250);
    chassis.cancelAllMotions();
    move(50,0,false, 1250);
    pros::delay(700);


    stopIntake();
    chassis.moveToPoint(65.6, 98.36, 1000, {.forwards = false},false);
    scraper.set_value(false);


    // MAYBE CHANGE HERE
    // chassis.turnToPoint(79.7, 85.6, 750, {.forwards = false});
    // chassis.moveToPoint(79.7, 85.6, 1000, {.forwards = false}, false);
    chassis.turnToPoint(81.3, 87.5, 750, {.forwards = false});
    chassis.moveToPoint(81.3, 87.5, 1000, {.forwards = false}, false);


    //moving backwards to score in long goal

    chassis.turnToPoint(78.72, 10.5, 750, {.forwards = false});

    // MADE FASTER
    chassis.moveToPoint(78.72, 10.5, 2500, {.forwards = false}, false);

    
    
    chassis.turnToHeading(-90, 750);
    chassis.moveToPoint(67,10.4,1000);
    chassis.turnToPoint(67, 28.61, 750,{.forwards = false});
    chassis.moveToPoint(67, 28.61,1000,{.forwards = false}, false);
    
    //score top 
    move(-70,0,false,200);
    pros::delay(100);
    scoreTop();
    pros::delay(3000);
    stopIntake();

    //unload match loader 4
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(64, -9.75, 1000, {.maxSpeed = 100}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(40,0,false, 1250);
    pros::delay(500);

    // //score in long goal again 2nd time
    chassis.moveToPoint(67, 28.61, 1000, {.forwards = false, .maxSpeed = 100}, false);
    stopIntake();     
    move(-50,0,false,200);
    pros::delay(100);
    scoreTop();
    pros::delay(3300);
    move(50,0,false,200);
    pros::delay(250);
    move(-50,0,false,200);

    // scraper.set_value(false);    
    // chassis.moveToPose(30, -17, -90, 1500, {.lead = .3});
    // move(120,0,false,2000);





}

void skills(){
    horLift.set_value(false);
    verLift.set_value(false);
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    wing.set_value(true);
    storageIn();

    //moving to middle goal
    chassis.moveToPoint(-9.28, 29.41, 1000);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false});
    chassis.moveToPoint(7.38, 44.3, 800, {.forwards = false, .maxSpeed = 90}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(1500);
    // flappier.set_value(false);
    // flappy.set_value(false);

    //go to match loader
    chassis.turnToHeading(-135, 700);
    chassis.moveToPoint(-36, 3.7, 1500, {});
    chassis.turnToHeading(-177, 700, {}, false);
    scraper.set_value(true);
    pros::delay(600);
    storageIn();
    chassis.moveToPoint(-37.2, -4.5, 1000);

    //empty match loader 1
    chassis.cancelAllMotions();
    move(60, 0, false, 1250);
    pros::delay(710);

    // go backwards for turn
    chassis.moveToPoint(-41.15, 3.2, 1000, {.forwards = false}, false);
    scraper.set_value(false);

    chassis.turnToPoint(-51.5,15.1, 750, {.forwards = false}, false);
    stopIntake();
    chassis.moveToPoint(-51.5,15.1, 1000, {.forwards = false});
    
    // go to other side 
    chassis.turnToPoint(-49.44, 91, 750, {.forwards = false});
    chassis.moveToPoint(-49.44, 91, 2500, {.forwards = false}, false);
    // // chassis.turnToPoint(-47.5, 96.59, 750, {.forwards = false});
    // // chassis.moveToPoint(-47.5, 96.59, 2500, {.forwards = false}, false);

    // //score in long goal 1st time
    
    // // OLD CODE 
    chassis.turnToPoint(-39.26, 91, 1000, {.forwards = false});
    chassis.moveToPoint(-39.26, 91, 1000, {.forwards = false});

    chassis.turnToPoint(-39.26, 81, 750, {.forwards = false});
    chassis.moveToPoint(-39.26, 81, 1000, {.forwards = false},false);
    



    move(-50,0,false,300);
    // aligned to goal
    scoreTop();
    pros::delay(2500);

    chassis.turnToHeading(0,300);

    // //unload match loader 2
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(-39.26, 107, 1000, {}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(40,0,false, 1500);
    pros::delay(250);

    //score in long goal again
    chassis.turnToPoint(-39.26, 83.20, 750, {.forwards = false});
    chassis.moveToPoint(-39.26, 83.20, 1000, {.forwards = false}, false);
    stopIntake();     
    move(-60,0,false,400);
    pros::delay(100);
    scoreTop();
    pros::delay(2500);
    stopIntake();
    chassis.moveToPoint(-39.26, 89, 700,{},false);
    scraper.set_value(false);
    pros::delay(300);
    move(-70,0,false,200);
    
    chassis.moveToPoint(-39.26,98,800, {},false);

    // chassis.turnToPoint(-13.9,121.1, 750);
    // chassis.moveToPoint(-13.9,121.1, 1000);
    storageIn();
    chassis.moveToPose(-13.9, 120.7, 82, 1500, {.lead = .3},false);
    //chassis.turnToHeading(82,500);
    horLift.set_value(true);
    verLift.set_value(true);
   
    
    move(120,0,false,1500);
    resetAllPositions();

}


void startAuton(){
    if (getSelectedAuton() == 0 || getSelectedAuton() == 4)
    {
        fastBottomGoals();
    }
    else if (getSelectedAuton() == 5 || getSelectedAuton() == 1)
    {
        fastTopGoals();
    }
    else if (getSelectedAuton() == 2 || getSelectedAuton() == 6)
    {
        bottomControl();
    }
}