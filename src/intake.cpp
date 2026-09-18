#include "intake.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "autons.h"
#include "pros/motors.hpp"
#include "main.h"

pros::Motor intake (-3);


void runIntake() {

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake.move(127); 
            clawWrist.set_value(true);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(-127); 
            clawWrist.set_value(true);
        } else {
            intake.move(0); // stop the lift
        }
}