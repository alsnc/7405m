#include "main.h"
#include <cmath>
#include <cstdlib>
double error;

void lift(int lift_voltage){
    lift_motors.move_voltage(lift_voltage);
}

void liftMacro(double macroAngle, double lift_voltage,double kP,double kD,int toleranceInDegrees){
    error=lift_motors.get_position()-macroAngle;
    double last_time=error;
    double this_time;
    while(fabs(error)>toleranceInDegrees){
        error=lift_motors.get_position()-macroAngle;
        double this_time=error;
        double de=this_time-last_time;
        lift_motors.move_voltage(lift_voltage*(error*kP+kD*de/0.02));
        /* Be careful when filling the values because the voltage is measured in milivolts. 
        The voltage range is from 12000 to -12000. */
        double last_time=this_time;
    }
}