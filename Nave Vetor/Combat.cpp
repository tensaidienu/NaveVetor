#include "Combat.h"
#include "Main.h"

//__________________________________________________________________________________________________________________________________
//-----------------------------------------------------------SHOOT BULLETS----------------------------------------------------------
void Combat::ShootBullets(Bullet bullets[], int size, Ship ship) {
	if (mission == 1) {
		for (int i = 0; i < size; i++) {
			if (!bullets[i].active) {
				al_stop_sample_instance(inst_laser);
				al_play_sample_instance(inst_laser);
				bullets[i].x = ship.x + 70;
				bullets[i].y = ship.y + 55;
				bullets[i].active = true;
				break;
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (!bullets[i].active) {
				al_stop_sample_instance(inst_laser);
				al_play_sample_instance(inst_laser);
				bullets[i].x = ship.x + 50;
				bullets[i].y = ship.y + 15;
				bullets[i].active = true;
				break;
			}
		}
	}
}

void Combat::BossShootBullet(Bullet bulletsBoss[], int size, Boss bosses[]) {
	if (mission==1) {
		for (int c = 0; c < 10; c++) {
			for (int i = 0; i < size; i++) {
				if (!bulletsBoss[i].active) {
					if (bosses[c].active) {
						al_stop_sample_instance(inst_laser);
						al_play_sample_instance(inst_laser);
						bulletsBoss[i].x = bosses[c].x - 17;
						bulletsBoss[i].y = bosses[c].y+25;
						bulletsBoss[i].active = true;
						break;
					}
				}
			}
		}
	} else {
		for (int c = 0; c < 10; c++) {
			for (int i = 0; i < size; i++) {
				if (!bulletsBoss[i].active) {
					if (bosses[c].active) {
						al_stop_sample_instance(inst_laser);
						al_play_sample_instance(inst_laser);
						bulletsBoss[i].x = bosses[c].x + 15;
						bulletsBoss[i].y = bosses[c].y + 15;
						bulletsBoss[i].active = true;
						break;
					}
				}
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//-------------------------------------------------------------COLLIDERS------------------------------------------------------------
void Combat::BulletCollider(Bullet bullets[], int b_size, Comet comets[], int c_size, Ship &ship, Boss bosses[]) {
	for (int i = 0; i < b_size; i++) {
		for (int c = 0; c < b_size; c++) {
			if (bullets[i].active) {
				for (int x = 0; x < c_size; x++) {
					if (comets[x].active) {
						if (bullets[i].x > ((comets[x].x - comets[x].edge_x) + comets[i].edge_posX) &&
							bullets[i].x < ((comets[x].x + comets[x].edge_x) + comets[i].edge_posX) &&
							bullets[i].y > ((comets[x].y - comets[x].edge_y) + comets[i].edge_posY) &&
							bullets[i].y < ((comets[x].y + comets[x].edge_y) + comets[i].edge_posY)) {

								al_stop_sample_instance(inst_explosionMeteor);
								al_play_sample_instance(inst_explosionMeteor);
								bullets[i].active = false;
								comets[x].active = false;
								ship.points++;

						}
					}
				}

				if (bosses[c].active) {
					if (bullets[i].x > ((bosses[c].x - bosses[c].edge_x) + bosses[i].edge_posX) &&
						bullets[i].x < ((bosses[c].x + bosses[c].edge_x) + bosses[i].edge_posX) &&
						bullets[i].y > ((bosses[c].y - bosses[c].edge_y) + bosses[i].edge_posY) &&
						bullets[i].y < ((bosses[c].y + bosses[c].edge_y) + bosses[i].edge_posY)) {

						al_stop_sample_instance(inst_explosionBoss);
						al_play_sample_instance(inst_explosionBoss);
						bullets[i].active = false;
						ship.points += 2;
						bosses[c].life--;
					}
				}

			}
		}
	}
}

void Combat::CometCollider(Comet comets[], int c_size, Ship &ship) {
	for (int i = 0; i < c_size; i++) {
		if (comets[i].active) {
			if (((comets[i].x - comets[i].edge_x) + comets[i].edge_posX) < ((ship.x + ship.edge_x) + ship.edge_posX) &&
				((comets[i].x + comets[i].edge_x) + comets[i].edge_posX) > ((ship.x - ship.edge_x) + ship.edge_posX) &&
				((comets[i].y - comets[i].edge_y) + comets[i].edge_posY) < ((ship.y + ship.edge_y) + ship.edge_posY) &&
				((comets[i].y + comets[i].edge_y) + comets[i].edge_posY) > ((ship.y - ship.edge_y) + ship.edge_posY)) {
				comets[i].active = false;
				--ship.life;
				al_stop_sample_instance(inst_explosionMeteor);
				al_play_sample_instance(inst_explosionMeteor);
			}
			else if (comets[i].x < 0 || comets[i].y > height_w) {
				comets[i].active = false;
				--ship.life;
			}
		}
	}
}

void Combat::BossCollider(Boss bosses[], Ship &ship, Bullet bullets[]) {
	for (int i = 0; i < 10; i++) {
		if (bosses[i].active) {
			if (((bosses[i].x - bosses[i].edge_x) + bosses[i].edge_posX) < ((ship.x + ship.edge_x) + ship.edge_posX) &&
				((bosses[i].x + bosses[i].edge_x) + bosses[i].edge_posX) > ((ship.x - ship.edge_x) + ship.edge_posX) &&
				((bosses[i].y - bosses[i].edge_y) + bosses[i].edge_posY) < ((ship.y + ship.edge_y) + ship.edge_posY) &&
				((bosses[i].y + bosses[i].edge_y) + bosses[i].edge_posY) > ((ship.y - ship.edge_y) + ship.edge_posY)) {
				bosses[i].active = false;
				game_over = true;
				ship.life -= 50;
				al_stop_sample_instance(inst_explosionBoss);
				al_play_sample_instance(inst_explosionBoss);
			}
		}
	}
}

void Combat::BossBulletCollider(Bullet bullestBoss[], int b_size, Comet comets[], int c_size, Ship &ship, Boss bosses[]) {
	for (int c = 0; c < 10; c++) {
		for (int i = 0; i < b_size; i++) {
			if (bullestBoss[i].active) {
				for (int x = 0; x < c_size; x++) {
					if (comets[x].active) {
						if (bullestBoss[i].x > ((comets[x].x - comets[x].edge_x) + comets[i].edge_posX) &&
							bullestBoss[i].x < ((comets[x].x + comets[x].edge_x) + comets[i].edge_posX) &&
							bullestBoss[i].y > ((comets[x].y - comets[x].edge_y) + comets[i].edge_posY) &&
							bullestBoss[i].y < ((comets[x].y + comets[x].edge_y) + comets[i].edge_posY)) {

							al_stop_sample_instance(inst_explosionMeteor);
							al_play_sample_instance(inst_explosionMeteor);
							bullestBoss[i].active = false;
							comets[x].active = false;
							ship.points--;
						}
					}

				}

				if (bosses[c].active) {
					if (bullestBoss[i].x > ((ship.x - ship.edge_x) + ship.edge_posX) &&
						bullestBoss[i].x < ((ship.x + ship.edge_x) + ship.edge_posX) &&
						bullestBoss[i].y > ((ship.y - ship.edge_y) + ship.edge_posY) &&
						bullestBoss[i].y < ((ship.y + ship.edge_y) + ship.edge_posY)) {


						al_stop_sample_instance(inst_explosionBoss);
						al_play_sample_instance(inst_explosionBoss);
						bullestBoss[i].active = false;
						ship.points -= 2;
						ship.life--;
					}
				}
			}
		}
	}
}