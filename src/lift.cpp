#include "main.h"
#include <cmath>
#include <cstdlib>

//lift macro pid
double kp = 27;
double kd = 0.0;
int tolerance = 1;

pros::Rotation liftDeg(10); // replace with actual port number

void liftMacro(double angle)
{
    clawWrist.set_value(false);
    double curr = ((double) liftDeg.get_angle())/100.0;
    double error;
    //to prevent weird huge derivative first time
    double prevError = angle - curr;
    double refreshRate = 20; // in milliseconds
    
    //movement
    while (curr < (angle - tolerance) || curr > (angle + tolerance))
    {
        //calculations
        //uhhh apparently pros gives it in centidegrees (SO WEIRD, but ok)
        curr = ((double) liftDeg.get_angle())/100.0;
        error = angle - curr;
        double derivative = (error - prevError) / (refreshRate / 1000.0);
        double speed = kp * error + kd * derivative;

        //move (limit too)
        if (speed > 127 || speed < -127) 
        {
            speed = (speed > 0) ? 127 : -127;
        }

        lift_motors.move(speed);

        prevError = error;
        pros::delay(refreshRate);
        while (curr< angle+5 && curr >angle -5) {
            lift_motors.move(25); 
        }
    }

   

    //maybe change to prevent motor burnout?? Idk we'll see
    
    
}


void moveLift(int speed)
{
    lift_motors.move(speed);
}

void timeLift(int speed, int ms)
{
    lift_motors.move(speed);
    pros::delay(ms);
    lift_motors.move(0);
}


