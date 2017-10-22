#pragma once
#include "Objects.h"
#include "Constants.h"

class Moviment {

public:
	static void MoveShipUp(Ship &ship);
	static void MoveShipDown(Ship &ship);
	static void MoveShipRight(Ship &ship);
	static void MoveShipLeft(Ship &ship);
	static void RefreshBullet(Bullet bullets[], int size);
	static void RefreshComet(Comet comets[], int size);
	static void RefreshBackground(Star stars_background[][NUM_STARS], int background_size, int s_size);
	static void RefreshBoss(Boss bosses[], int numBoss);
	static void RefreshUpBoss(Boss bosses[], int numBoss);
	static void RefreshBossVertical(Boss bosses[], int numBoss);
	static void RefreshUpBossVertical(Boss bosses[], int numBoss);
	static void RefreshBoss2(Boss bosses[]);
	static void RefreshUpBoss2(Boss bosses[]);
	static void BossRefreshBullet(Bullet bullets[], int size);
};