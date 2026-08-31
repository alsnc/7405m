#include "main.h"
#include <cmath>
#include <cstdlib>

//lift macro pid
double kp = 0.0;
double kd = 0.0;
int tolerance = 0;

pros::Rotation liftDeg(19); // replace with actual port number

void lift(int lift_voltage){
    lift_motors.move(lift_voltage);
}

// void liftMacro(double macroAngle, double lift_voltage,double kP,double kD,int toleranceInDegrees){
//     error=lift_motors.get_position()-macroAngle;
//     double last_time=error;
//     double this_time;
//     while(true){
//         error=lift_motors.get_position()-macroAngle;
//         double this_time=error;
//         double de=this_time-last_time;
//         lift_motors.move_voltage(lift_voltage*(error*kP+kD*de/0.02));
//         /* Be careful when filling the values because the voltage is measured in milivolts. 
//         The voltage range is from 12000 to -12000. */
//         double last_time=this_time;
//     }
// }

void liftMacro(double angle)
{
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
    lift_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift_motors.brake();
}