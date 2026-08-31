#pragma once

#include "pros/rotation.hpp"
void liftPID();
void lift(int lift_voltage);
void liftMacro(double angle);

extern pros::Rotation liftDeg;