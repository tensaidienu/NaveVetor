#include "Graphics.h"
#include "Main.h"

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------LOAD---------------------------------------------------------------
void Graphics::LoadSprites() {
	if (mission == 1) {
		shipImage = al_load_bitmap("SpaceShooterRedux/PNG/playerShip2_green_horizontal.png");
		cometImage = al_load_bitmap("SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png");
		boss1Image = al_load_bitmap("SpaceShooterRedux/PNG/ufoRed.png");
		boss2Image = al_load_bitmap("boss2.png");
		boss3Image = al_load_bitmap("SpaceShooterRedux/PNG/Enemies/enemyBlack4Horizontal.png");
	} else {
		shipImage = al_load_bitmap("SpaceShooterRedux/PNG/playerShip1_green.png");
		cometImage = al_load_bitmap("SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png");
		boss1Image = al_load_bitmap("SpaceShooterRedux/PNG/Enemies/enemyBlack3.png");
		boss2Image = al_load_bitmap("SpaceShooterRedux/PNG/ufoYellow.png");
		boss3Image = al_load_bitmap("SpaceShooterRedux/PNG/Enemies/enemyBlack2.png");
	}
}

void Graphics::LoadMenu() {
	menuImage = al_load_bitmap("SpaceShooterRedux/Backgrounds/blue.png");
}

void Graphics::DestroySprites() {
	al_destroy_bitmap(menuImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(boss1Image);
	al_destroy_bitmap(boss2Image);
	al_destroy_bitmap(boss3Image);
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------SHIP---------------------------------------------------------------
void Graphics::DrawShip(Ship &ship) {
	al_draw_bitmap(shipImage, ship.x, ship.y, 0);

	//Collider
	//al_draw_filled_rectangle((ship.x - ship.edge_x) + ship.edge_posX, (ship.y - ship.edge_y) + ship.edge_posY, (ship.x + ship.edge_x) + ship.edge_posX, (ship.y + ship.edge_y) + ship.edge_posY, al_map_rgba_f(.6, .6, .6, .6));
}

//__________________________________________________________________________________________________________________________________
//--------------------------------------------------------------BULLET--------------------------------------------------------------
void Graphics::DrawBullet(Bullet bullets[], int size) {
	if (mission==1) {
		for (int i = 0; i < size; i++) {
			if (bullets[i].active) {
				al_draw_line(bullets[i].x, bullets[i].y, bullets[i].x + 7, bullets[i].y, al_map_rgb(255, 50, 50), 3);
				//al_draw_filled_circle(bullets[i].x, bullets[i].y, 5, al_map_rgb(255, 50, 50));
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (bullets[i].active) {
				al_draw_line(bullets[i].x, bullets[i].y, bullets[i].x, bullets[i].y + 7, al_map_rgb(255, 50, 50), 3);
				//al_draw_filled_circle(bullets[i].x, bullets[i].y, 5, al_map_rgb(255, 50, 50));
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//--------------------------------------------------------------COMET---------------------------------------------------------------
void Graphics::DrawComet(Comet comets[], int size) {
	for (int i = 0; i < size; i++) {
		if (comets[i].active) {
			al_draw_bitmap(cometImage, comets[i].x, comets[i].y, 0);
			
			//Collider
			//al_draw_filled_rectangle((comets[i].x - comets[i].edge_x) + comets[i].edge_posX, (comets[i].y - comets[i].edge_y) + comets[i].edge_posY, (comets[i].x + comets[i].edge_x) + comets[i].edge_posX, (comets[i].y + comets[i].edge_y) + comets[i].edge_posY, al_map_rgba_f(.6,.6,.6,.6));
		}
	}
}

//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------BACKGROUND------------------------------------------------------------
void Graphics::DrawBackground(Star stars_background[][NUM_STARS], int background_size, int s_size) {
	for (int i = 0; i < background_size; i++) {
		for (int x = 0; x < s_size; x++) {
			if (i == 0) {
				al_draw_pixel(stars_background[i][x].x, stars_background[i][x].y, al_map_rgb(255, 255, 255));
			}
			else if (i == 1) {
				al_draw_pixel(stars_background[i][x].x, stars_background[i][x].y, al_map_rgb(255, 255, 255));
			}
			else if (i == 2) {
				al_draw_pixel(stars_background[i][x].x, stars_background[i][x].y, al_map_rgb(255, 255, 255));
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------BOSS---------------------------------------------------------------
void Graphics::DrawBoss(Boss bosses[]) {
	if (bosses[0].active) {
		al_draw_bitmap(boss1Image, bosses[0].x - 25, bosses[0].y - 20, 0);
		
		//Collider
		//al_draw_filled_rectangle((bosses[0].x - bosses[0].edge_x) + bosses[0].edge_posX, (bosses[0].y - bosses[0].edge_y) + bosses[0].edge_posY, (bosses[0].x + bosses[0].edge_x) + bosses[0].edge_posX,( bosses[0].y + bosses[0].edge_y) + bosses[0].edge_posY, al_map_rgba_f(.6, .6, .6, .6));
		
		//al_draw_filled_rectangle(bosses[0].x + 15, bosses[0].y - 17, bosses[0].x, bosses[0].y - 20, al_map_rgb(255, 255, 255));
		//al_draw_filled_rectangle(bosses[0].x + 15, bosses[0].y + 17, bosses[0].x, bosses[0].y + 20, al_map_rgb(255, 255, 255));
		//al_draw_filled_triangle(bosses[0].x + 18, bosses[0].y + 27, bosses[0].x - 11, bosses[0].y, bosses[0].x + 22, bosses[0].y - 27, al_map_rgb(0, 34, 255));
		//al_draw_filled_rectangle(bosses[0].x + 15, bosses[0].y + 2, bosses[0].x - 12, bosses[0].y + 2, al_map_rgb(0, 0, 255));		
	} else if (bosses[1].active) {
		al_draw_bitmap(boss2Image, bosses[1].x - 25, bosses[1].y - 20, 0);

		//Collider
		//al_draw_filled_rectangle((bosses[1].x - bosses[1].edge_x) + bosses[1].edge_posX, (bosses[1].y - bosses[1].edge_y) + bosses[1].edge_posY, (bosses[1].x + bosses[1].edge_x) + bosses[1].edge_posX, (bosses[1].y + bosses[1].edge_y) + bosses[1].edge_posY, al_map_rgba_f(.6,.6,.6,.6));
	} else if (bosses[2].active) {
		al_draw_bitmap(boss3Image, bosses[2].x - 25, bosses[2].y - 20, 0);

		//Collider
		//al_draw_filled_rectangle((bosses[2].x - bosses[2].edge_x) + bosses[2].edge_posX, (bosses[2].y - bosses[2].edge_y) + bosses[2].edge_posY, (bosses[2].x + bosses[2].edge_x) + bosses[2].edge_posX, (bosses[2].y + bosses[2].edge_y) + bosses[2].edge_posY, al_map_rgba_f(.6, .6, .6, .6));
	}
}

//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------BOSS BULLET-----------------------------------------------------------
void Graphics::BossDrawBullet(Bullet bulletsBoss[], int size) {
	if (mission==1) {
		for (int i = 0; i < size; i++) {
			if (bulletsBoss[i].active) {
				al_draw_line(bulletsBoss[i].x, bulletsBoss[i].y, bulletsBoss[i].x + 7, bulletsBoss[i].y, al_map_rgb(255, 30, 150), 3);
				//al_draw_filled_circle(bulletsBoss[i].x, bulletsBoss[i].y, 2, al_map_rgb(255, 255, 255));
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (bulletsBoss[i].active) {
				al_draw_line(bulletsBoss[i].x, bulletsBoss[i].y, bulletsBoss[i].x, bulletsBoss[i].y + 7, al_map_rgb(255, 30, 150), 3);
				//al_draw_filled_circle(bulletsBoss[i].x, bulletsBoss[i].y, 2, al_map_rgb(255, 255, 255));
			}
		}
	}
}