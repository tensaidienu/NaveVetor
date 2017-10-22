#include "Moviment.h"
#include "Main.h"

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------SHIP---------------------------------------------------------------
void Moviment::MoveShipUp(Ship &ship) {
	ship.y -= ship.velocity;
	if (ship.y < 20)
		ship.y = 20;
}

void Moviment::MoveShipDown(Ship &ship) {

	ship.y += ship.velocity;
	if (ship.y > height_w - 115)
		ship.y = height_w - 115;

}

void Moviment::MoveShipRight(Ship &ship) {

	ship.x += ship.velocity;
	if (ship.x > width_w - 100)
		ship.x = width_w - 100;

}

void Moviment::MoveShipLeft(Ship &ship) {

	ship.x -= ship.velocity;
	if (ship.x < 12)
		ship.x = 12;

}

//__________________________________________________________________________________________________________________________________
//--------------------------------------------------------------BULLET--------------------------------------------------------------
void Moviment::RefreshBullet(Bullet bullets[], int size) {
	if (mission==1) {
		for (int i = 0; i < size; i++) {
			if (bullets[i].active) {
				bullets[i].x += bullets[i].velocity;

				if (bullets[i].x > width_w)
					bullets[i].active = false;
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (bullets[i].active) {
				bullets[i].y -= bullets[i].velocity;

				if (bullets[i].y < 0)
					bullets[i].active = false;
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------COMET--------------------------------------------------------------
void Moviment::RefreshComet(Comet comets[], int size) {
	if (mission==1) {
		for (int i = 0; i < size; i++) {
			if (comets[i].active) {
				comets[i].x -= comets[i].velocity;
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (comets[i].active) {
				comets[i].y += comets[i].velocity;
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------BACKGROUND------------------------------------------------------------
void Moviment::RefreshBackground(Star stars_background[][NUM_STARS], int background_size, int s_size) {
	if (mission == 1) {
		for (int i = 0; i < background_size; i++) {
			for (int x = 0; x < s_size; x++) {
				if (i == 0) {
					stars_background[i][x].x -= stars_background[i][x].velocity;
					if (stars_background[i][x].x < 0)
						stars_background[i][x].x = width_w;
				} else if (i == 1) {
					stars_background[i][x].x -= stars_background[i][x].velocity;
					if (stars_background[i][x].x < 0)
						stars_background[i][x].x = width_w;
				} else if (i == 2) {
					stars_background[i][x].x -= stars_background[i][x].velocity;
					if (stars_background[i][x].x < 0)
						stars_background[i][x].x = width_w;
				}
			}
		}
	} else {
		for (int i = 0; i < background_size; i++) {
			for (int x = 0; x < s_size; x++) {
				if (i == 0) {
					stars_background[i][x].y += stars_background[i][x].velocity;
					if (stars_background[i][x].y > height_w)
						stars_background[i][x].y = 5 + rand() % (25 - 10);
				} else if (i == 1) {
					stars_background[i][x].y += stars_background[i][x].velocity;
					if (stars_background[i][x].y > height_w)
						stars_background[i][x].y = 5 + rand() % (25 - 10);

				} else if (i == 2) {
					stars_background[i][x].y += stars_background[i][x].velocity;
					if (stars_background[i][x].y > height_w)
						stars_background[i][x].y = 5 + rand() % (25 - 10);
				}
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------BOSS---------------------------------------------------------------
void Moviment::RefreshBoss(Boss bosses[], int numBoss) {
	if (bosses[numBoss].active && bosses[numBoss].x <= 100) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}
	if (bosses[numBoss].active && bosses[numBoss].x >= width_w - 100) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}

	if (direction == 1) {
		bosses[numBoss].x -= bosses[numBoss].velocity;
	}

	if (direction == 2) {
		bosses[numBoss].x += bosses[numBoss].velocity;
	}

}

void Moviment::RefreshBossVertical(Boss bosses[], int numBoss) {
	if (bosses[numBoss].active && bosses[numBoss].x == 100) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}
	if (bosses[numBoss].active && bosses[numBoss].x == (width_w - 100)) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}

	if (direction == 1) {
		bosses[numBoss].x -= bosses[numBoss].velocity;

	}

	if (direction == 2) {
		bosses[numBoss].x += bosses[numBoss].velocity;
	}

}

void Moviment::RefreshBoss2(Boss bosses[]) {
	if (bosses[1].active && bosses[1].x == 300) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}
	if (bosses[1].active && bosses[1].x == 700) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 1;
			cont = 0;
		}
	}

	if (direction == 1) {
		bosses[1].x -= bosses[1].velocity;

	}

	if (direction == 2) {
		bosses[1].x += bosses[1].velocity;
	}

}

void Moviment::RefreshUpBoss(Boss bosses[], int numBoss) {

	if (bosses[numBoss].active && bosses[numBoss].y == 100) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}
	if (bosses[numBoss].active && bosses[numBoss].y == 700) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}

	if (direction == 1) {
		bosses[numBoss].y -= bosses[numBoss].velocity;
	}

	if (direction == 2) {
		bosses[numBoss].y += bosses[numBoss].velocity;
	}

}

void Moviment::RefreshUpBossVertical(Boss bosses[], int numBoss) {
	if (bosses[numBoss].active && bosses[numBoss].y >= height_w - 100) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}
	if (bosses[numBoss].active && bosses[numBoss].y <= 100) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}

	if (direction == 2) {
		bosses[numBoss].y -= bosses[numBoss].velocity;
		if (bosses[numBoss].y < 0)
			bosses[numBoss].y = 0;
	}

	if (direction == 1) {
		bosses[numBoss].y += bosses[numBoss].velocity;
		if (bosses[numBoss].y > height_w - 100)
			bosses[numBoss].y = height_w - 100;
	}
}

void Moviment::RefreshUpBoss2(Boss bosses[]) {

	if (bosses[1].active && bosses[1].y == 100) {
		direction = 2;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}
	if (bosses[1].active && bosses[1].y == 700) {
		direction = 1;
		cont++;
		if (cont > 3) {
			dir = 0;
		}
	}

	if (direction == 1) {
		bosses[1].y -= bosses[1].velocity;
	}

	if (direction == 2) {
		bosses[1].y += bosses[1].velocity;
	}

}

//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------BOOS BULLET-----------------------------------------------------------
void Moviment::BossRefreshBullet(Bullet bulletsBoss[], int size) {
	if (mission == 1) {
		for (int i = 0; i < size; i++) {
			if (bulletsBoss[i].active) {
				bulletsBoss[i].x -= bulletsBoss[i].velocity;

				if (bulletsBoss[i].x > width_w)
					bulletsBoss[i].active = false;
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (bulletsBoss[i].active) {
				bulletsBoss[i].y += bulletsBoss[i].velocity;

				if (bulletsBoss[i].y > height_w)
					bulletsBoss[i].active = false;
			}
		}
	}
}