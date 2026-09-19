#pragma once

#include "pros/rotation.hpp"

void liftMacro(double angle);

void moveLift(int speed); 
void timeLift(int speed, int ms); 

extern pros::Rotation liftDeg;