#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP

#include "DriversMotores.hpp"

MotorDriver ActuatorBrake_Driver("B", ActuatorBrake_Address);
MotorDriver ActuatorAccel_Driver("A", ActuatorAccel_Address);
MotorDriver ActuatorSteer_Driver("V", ActuatorSteer_Address);


#endif // ACTUATORS_HPP
