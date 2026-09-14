#pragma once

#include "pros/rotation.hpp"
void liftPID();
void lift(double target);
void liftMacro(double angle);

extern pros::Rotation liftDeg;