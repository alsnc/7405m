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
     
}
void fastBottomScore()
{
    intake.move(-110);
    intake2.move(-110);
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
}

void scoreTop() {
    flappier.set_value(false);
    flappy.set_value(false);
    intake2.move(127);
    intake.move(127);
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