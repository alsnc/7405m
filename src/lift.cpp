#include "main.h"
#include <cmath>
#include <cstdlib>
double error;

void lift(int lift_voltage){
    lift_motors.move_voltage(lift_voltage);
}

void liftMacro(double macroAngle, double lift_voltage,double kP,int toleranceInDegrees){
    error=lift_motors.get_position()-macroAngle;
    while(fabs(error)<toleranceInDegrees){
        error=lift_motors.get_position()-macroAngle;
        lift_motors.move_voltage(lift_voltage*error*kP+120); 
        /* Be careful when filling the values because the voltage is measured in milivolts. 
        The voltage range is from 12000 to -12000. */
    }
}