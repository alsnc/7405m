#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"

extern void turnToHeading(double targetHeading, int timeout, int maxSpeed);
extern void turnToPose(lemlib::Pose targetPose, int timeout, int maxSpeed);