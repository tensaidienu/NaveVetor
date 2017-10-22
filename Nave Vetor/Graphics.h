#pragma once
#include "Objects.h"
#include "Constants.h"

class Graphics {

public:
	static void LoadSprites();
	static void LoadMenu();
	static void DestroySprites();
	static void DrawBackground(Star stars_background[][NUM_STARS], int background_size, int s_size);
	static void DrawShip(Ship &ship);
	static void DrawBullet(Bullet bullets[], int size);
	static void DrawComet(Comet comets[], int size);
	static void DrawBoss(Boss bosses[]);
	static void BossDrawBullet(Bullet bullets[], int size);
};