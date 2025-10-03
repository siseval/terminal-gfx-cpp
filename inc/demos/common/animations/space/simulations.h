#ifndef SIMULATIONS_H
#define SIMULATIONS_H

namespace demos::common::animations::space
{

class Body;
class SpaceDemo;

}

namespace demos::common::animations::space::simulations
{

void solar_system(SpaceDemo &demo);
void three_body_problem(SpaceDemo &demo);
void chaos(SpaceDemo &demo);

}

#endif // SIMULATIONS_H
