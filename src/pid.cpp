#include "lemlib/pose.hpp"
#include "main.h"
#include "autons.h"
#include "autonselector.h"
#include "intake.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//calculated using desmos calculator 
//y=-\left(4.15985\times10^{-8}\right)x^{4}+0.0000168105x^{3}-0.00222358x^{2}+0.0993382x+0.30445
double firstTerm = -0.0000000415985;
double secondTerm = 0.0000168105;
double thirdTerm = -0.00222358;
double fourthTerm = 0.0993382;
double intercept = 0.30445;

void calcKp(double angle)
{
    double first = firstTerm * std::pow(angle, 4);
    double second = secondTerm * std::pow(angle, 3);
    double third = thirdTerm * std::pow(angle, 2);
    double fourth = fourthTerm * angle;
    double equation = first + second + third + fourth + intercept;

    chassis.setAngularkP(equation);
}

constexpr double RAD_TO_DEG = 180.0 / M_PI;
double toDegrees(double radians) {
    return radians * RAD_TO_DEG;
}

//basically to prevent the angle from going above/below 180/-180 cuz if it does then it is less efficient
double normalize(double angle) {
  angle = toDegrees(angle);
  while (angle > 180) angle -= 360;
  while (angle < -180) angle += 360;
  return angle;
}

//gives the angle we need to turn (for point and for heading) - only one parameter THIS IS SOO COOOOOL BEANSSSSS
double calcAngle(std::variant<double, lemlib::Pose> target) 
{
    lemlib::Pose pose = chassis.getPose();
    //check if parameter is an angle, not a point
    if (std::holds_alternative<double>(target)) {
        return normalize(toDegrees(std::get<double>(target)) - pose.theta);
    } 
    //this means parameter is a point
    else 
    {
        auto& point = std::get<lemlib::Pose>(target);
        //aparently atan2 puts it in radians and that's what lemlib needs ig (it's superrr complicated)
        double targetAngle = std::atan2(point.y - pose.y, point.x - pose.x);
        return normalize(toDegrees(targetAngle) - pose.theta);
    }
}

void turnToPose(lemlib::Pose targetPose, int timeout, int maxSpeed) 
{
    double angleToTurn = calcAngle(targetPose);

    calcKp(angleToTurn);
    chassis.turnToHeading(angleToTurn, timeout, {.maxSpeed = maxSpeed});
}

void turnToHeading(double targetHeading, int timeout, int maxSpeed) 
{
    double angleToTurn = calcAngle(targetHeading);
    std::cout <<"angle: " << angleToTurn << std::endl;
    calcKp(angleToTurn);
    pros::delay(50);
    chassis.turnToHeading(angleToTurn, timeout, {.maxSpeed = maxSpeed});
}

