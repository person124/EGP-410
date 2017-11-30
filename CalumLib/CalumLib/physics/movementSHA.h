#ifndef MOVEMENT_SHA_H
#define MOVEMENT_SHA_H

class UnitSHA;

typedef void(*moveSHAFunc)(UnitSHA*);

namespace moveSHA
{
	void calculateMovement(UnitSHA* unit);
}

#endif