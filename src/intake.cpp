#include "intake.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"


pros::Motor intake (1); //top & middle
pros::Motor intake2 (-12); //self explanatory 

pros::adi::DigitalOut flappy ('A', false);
pros::adi::DigitalOut flappier ('B', false);

pros::Optical opticalSensor(11);

bool flingBlue = false;
bool intaking = false;

bool moving = false;

void updateIntake() 
{
    extern pros::Controller controller;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        //Put in storage
        storageIn();
        
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        //Score in middle goal
        scoreMiddle();
      
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        //Score in long goal
        scoreTop();
       
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        //Outake into bottom goal
        bottomGoal();       
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        //Outake into bottom goal
        bottomGoal();       
    }
    else
    {
        intake.brake();
        intake2.brake();
    }
}

void storageIn()
{
    //Put in storage
    flappy.set_value(false);
    flappier.set_value(true);
    intake.move (127);
    intake2.move (127);
    moving = true;
}

void slowerStorageIn()
{
    // huh
}

void bottomGoal()
{
    //tune
    intake.move(-127);
    intake2.move(-127);
    moving = true;
     
}
void fastBottomScore()
{
    intake.move(-110);
    intake2.move(-110);
    moving = true;

}

void weirdBottom()
{   
    flappy.set_value(false);
    flappier.set_value(true);
    intake.move(-127);
    intake2.move(-127);
}

void stopIntake() {
    intake.brake();
    intake2.brake();
    moving = false;

}

void scoreTop() {
    flappier.set_value(false);
    flappy.set_value(false);
    intake2.move(127);
    intake.move(127);
    moving = true;

}

void scoreTopAuto() {
    //huh
}

void scoreMiddle() {
    //intaking = true;
    flappy.set_value(true);
    flappier.set_value(true);
    intake.move(127); 
    intake2.move(127);
    moving = true;

}

void middleTime(int time) {
    //huh
}

void load()
{
    
}

void colorSort()
{
    if (flingBlue)
    {
        if (opticalSensor.get_hue() > 75)
        {
            scoreMiddle();
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else if (opticalSensor.get_hue() < 30)
        {
            scoreTop();
            pros::lcd::set_text(1, "RED: " + std::to_string(opticalSensor.get_hue()));
        }
        else
        {
            pros::lcd::set_text(1, "NONE: " + std::to_string(opticalSensor.get_hue()));
        }
    }
    else
    {
        if (opticalSensor.get_hue() > 50)
        {
            scoreTop();
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
        }
        else if (opticalSensor.get_hue() < 45)
        {
            scoreMiddle(); 
            pros::lcd::set_text(1, "RED: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else
        {
            pros::lcd::set_text(1, "NONE: " + std::to_string(opticalSensor.get_hue()));
        }
    }
}

void antiJam()
{
    while (intake.get_power() < 10 || intake2.get_power() < 10)
    {
        if (moving)
        {
            intake.move(-50);
            intake2.move(-50);
        }
    }

    intake.move(127);
    intake2.move(127);

    pros::delay(20);
}