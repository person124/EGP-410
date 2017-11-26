#ifndef MOVEMENT_FUNCTIONS_H
#define	MOVEMENT_FUNCTIONS_H

#include "physics/weightedBehaviourDefine.h"

namespace move {
	WeightB face(UnitPhys* unit);

	WeightB seek(UnitPhys* unit);

	//To slow down SHA
	WeightB friction(UnitPhys* unit);
}

#endif