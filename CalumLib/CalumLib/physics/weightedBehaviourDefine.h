#ifndef WEIGHTED_BEHAVIOUR_DEFINE_H
#define WEIGHTED_BEHAVIOUR_DEFINE_H

class UnitPhys;
struct WeightB;

typedef WeightB(*SteeringFunc)(UnitPhys* unit);

#endif