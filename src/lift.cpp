#include "main.h"
#include <cmath>
#include <cstdlib>
double error;

#include "main.h"
#include <cmath>


double kP = 2.0;
double kI = 0.0;
double kD = 0.1;

double integral = 0;
double lastError = 0;

void lift(double target) {

    integral = 0;
    lastError = 0;

    while (true) {

        double currentPosition = lift_motors.get_position();
        double error = target - currentPosition;

        // Integral
        integral += error;

        // Derivative
        double derivative = error - lastError;

        // PID
        double output =
            (kP * error) +
            (kI * integral) +
            (kD * derivative);

        //voltage limit
        if (output > 12000)
            output = 12000;

        if (output < -12000)
            output = -12000;

        lift_motors.move_voltage(output);

        lastError = error;

        //close enough
        if (fabs(error) < 5) {
            lift_motors.move_voltage(0);
            break;
        }

        pros::delay(20);
    }
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