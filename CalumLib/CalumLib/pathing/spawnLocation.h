#ifndef SPAWN_LOCATION_H
#define SPAWN_LOCATION_H

enum SpawnType
{
	PLAYER,
	ENEMY_BLUE,
	ENEMY_RED,
	ENEMY_YELLOW,
	CANDY
};

struct SpawnLocation
{
	SpawnLocation(SpawnType st, int xp, int yp)
	{
		type = st;
		x = xp;
		y = yp;
	}
	SpawnType type;
	int x, y;
};

#endif