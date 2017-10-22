#pragma once
#include "Objects.h"
#include "Constants.h"

class Combat {

public:
	static void ShootBullets(Bullet bullets[], int size, Ship ship);
	static void BossShootBullet(Bullet bullets[], int size, Boss bosses[]);
	static void BulletCollider(Bullet bullets[], int b_size, Comet comets[], int c_size, Ship &ship, Boss bosses[]);
	static void CometCollider(Comet comets[], int c_size, Ship &ship);
	static void BossCollider(Boss bosses[], Ship &ship, Bullet bullets[]);
	static void BossBulletCollider(Bullet bulletsBoss[], int b_size, Comet comets[], int c_size, Ship &ship, Boss bosses[]);
};