#include "main.h"
#include <cmath>
#include <cstdlib>

//lift macro pid
double kp = 20;
double kd = 0.0;
int tolerance = 2;

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
    }

    //maybe change to prevent motor burnout?? Idk we'll see
    lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    lift_motors.brake();
}


