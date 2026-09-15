#include "main.h"
#include <cmath>
#include <cstdlib>

//lift macro pid
double kp = 0.0;
double kd = 0.0;
int tolerance = 0;

pros::Rotation liftDeg(10); // replace with actual port number


#include "main.h"
#include <cmath>


double kP = 0.92;
double kI = 0.00; 
double kD = 0.0;
double kG = 1200; // Gravity constant in mV (~1.2V to hold the lift up)

double INTEGRAL_CAP = 3000; // Limits integral output to prevent windup

double integral = 0;
double lastError = 0;

void lift(double target) {

    integral = 0;
    lastError = 0;

    while (true) {

        double currentPosition = liftDeg.get_position();
        double error = target - currentPosition;

        // 1. Integral calculation with cap
        integral += error;
        if (integral * kI > INTEGRAL_CAP) {
            integral = INTEGRAL_CAP / kI;
        } else if (integral * kI < -INTEGRAL_CAP) {
            integral = -INTEGRAL_CAP / kI;
        }

        // 2. Derivative calculation
        double derivative = error - lastError;

        // 3. PID + Gravity Feedforward
        double output =
            (kP * error) +
            (kI * integral) +
            (kD * derivative) +
            kG; // Holds lift against gravity at all times

        // Voltage limit clamping (-12000 mV to +12000 mV)
        if (output > 8000) //12000 max
            output = 8000;

        if (output < -8000)
            output = -8000;

        lift_motors.move_voltage(output);

        lastError = error;

        // Close enough check
        if (fabs(error) < 5) {
            // Apply kG instead of 0 so gravity doesn't drag the lift down
            lift_motors.move_voltage(kG);
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


// }
