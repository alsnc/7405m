#include "main.h"
#include "pros/motors.h"
void lift(int lift_voltage){
    lift_motors.move_voltage(lift_voltage);
}