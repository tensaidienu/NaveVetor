#include "Main.h"
#include <cstdlib>
#include <ctime>
#include "Objects.h"
#include "Constants.h"
#include "Graphics.h"
#include "Moviment.h"
#include "Combat.h"
#include "Sound.h"
#include <string>
#include <ctime>

//__________________________________________________________________________________________________________________________________
//-----------------------------------------------------VARIABLES INITIALIZATION-----------------------------------------------------
int direction = 1;
int dir = 0;
int cont = 0;
int difficulty = 1100;
bool stopt1 = false;
bool stopt2 = true;
int attchefe = 0;
int attchefe2 = 0;
int attchefe3 = 0;
int attchefe4 = 0;
int attchefe5 = 0;
int level = 1;
int mission = 1;
bool game_over = false;
bool isPlaying[3] = { false, false, false };

ALLEGRO_BITMAP  *menuImage = NULL;
ALLEGRO_BITMAP  *shipImage = NULL;
ALLEGRO_BITMAP  *cometImage = NULL;
ALLEGRO_BITMAP  *boss1Image = NULL;
ALLEGRO_BITMAP  *boss2Image = NULL;
ALLEGRO_BITMAP  *boss3Image = NULL;
ALLEGRO_BITMAP  *displayIcon = NULL;

ALLEGRO_SAMPLE *sound_level_1 = NULL;
ALLEGRO_SAMPLE *sound_level_2 = NULL;
ALLEGRO_SAMPLE *sound_level_3 = NULL;
ALLEGRO_SAMPLE *laser = NULL;
ALLEGRO_SAMPLE *explosionMeteor = NULL;
ALLEGRO_SAMPLE *explosionBoss = NULL;
ALLEGRO_SAMPLE *menu = NULL;
ALLEGRO_SAMPLE *sucess = NULL;
ALLEGRO_SAMPLE *menuOk = NULL;

ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_1 = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_2 = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_3 = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_laser = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_explosionMeteor = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_explosionBoss = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_menu = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_sucess = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_menuOk = NULL;

ALLEGRO_EVENT ev;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *font13 = NULL;
ALLEGRO_FONT *font15 = NULL;
ALLEGRO_FONT *font20 = NULL;
ALLEGRO_FONT *font30 = NULL;
ALLEGRO_COLOR missionSanaColor;
ALLEGRO_COLOR missionShitakeColor;
ALLEGRO_DISPLAY *display = NULL;

Ship ship;
Bullet bullets[NUM_BULLETS];
Bullet bulletsBoss[NUM_BULLETS_BOSS];
Comet comets[NUM_COMETS];
Star stars_background[NUM_LAYERS][NUM_STARS];
Boss bosses[10];

//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------PROTOTYPE-------------------------------------------------------------
void InitShip (Ship &ship);
void InitBullet (Bullet bullets[], int size);
void InitComet(Comet comets[], int size);
void InitBackground(Star stars_background[][NUM_STARS], int background_size, int s_size);
void InitBoss(Boss bosses[]);
void BossInitBullet(Bullet bulletsBoss[], int size);

void ReleaseComet(Comet comets[], int size);
void ReleaseBoss(Boss bosses[], Ship &ship, int numBoss);

void InitAll();
void DestroyAll();
void InitGame();
//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------MAIN---------------------------------------------------------------
int main(){
	//_______________________________________________________________________________________________________________________________
	//--------------------------------------------------------LOCAL VARIABLES--------------------------------------------------------

	bool end = false;
	bool draw = true;
	bool keys[] = {false, false, false, false, false, false};
	bool menu = true;
	bool gameInit = true;
	bool createNewEventQueue = false;
	clock_t countTime = 0;
	char* missionSanaString = "MISSION KAITEN";
	char* missionShitakeString = "MISSION SHITAKE";

	//_______________________________________________________________________________________________________________________________
	//-----------------------------------------------ALLEGRO AND DISPLAY INITIALIZATION----------------------------------------------

	if(!al_init()){
		al_show_native_message_box(NULL,"WARNING!","ERROR","ERROR TO INITIALIZE ALLEGRO!",NULL,ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	//ALLEGRO_MONITOR_INFO info;
	int res_x_comp,res_y_comp;
	//al_get_monitor_info(0, &info);
	//res_x_comp = info.x2 - info.x1;
	//res_y_comp = info.y2 - info.y1;
	res_x_comp = 800;
	res_y_comp = 600;
	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(res_x_comp,res_y_comp);

	if(!display){
		al_show_native_message_box(NULL,"WARNING!","ERROR","ERROR TO CREATE DISPLAY!",NULL,ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_set_window_title(display,"NAVE VETOR");
	
	float red_x = res_x_comp / (float) width_w;
	float red_y = res_y_comp / (float) height_w;

	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_scale_transform(&transform,red_x,red_y);
	al_use_transform(&transform);

	//_______________________________________________________________________________________________________________________________
	//-------------------------------------------------------ADDONS INITIALIZATION---------------------------------------------------
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_reserve_samples(10);

	//_______________________________________________________________________________________________________________________________
	//---------------------------------------------QUEUE CREATION AND OTHERS INITIALIZATIONS-----------------------------------------
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	font13 = al_load_font("SpaceShooterRedux/Bonus/kenvector_future.ttf", 13, NULL);
	font15 = al_load_font("SpaceShooterRedux/Bonus/kenvector_future.ttf", 15, NULL);
	font20 = al_load_font("SpaceShooterRedux/Bonus/kenvector_future.ttf", 20, NULL);
	font30 = al_load_font("SpaceShooterRedux/Bonus/kenvector_future.ttf", 30, NULL);

	al_hide_mouse_cursor(display);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(font30, al_map_rgb(255,255,255), width_w / 2, height_w / 2, ALLEGRO_ALIGN_CENTRE, "LOADING.....");
	al_flip_display();

	missionSanaColor = al_map_rgb(255, 255, 0);
	missionShitakeColor = al_map_rgb(255, 255, 255);

	Sound::InitSound(0.7);
	Graphics::LoadMenu();

	displayIcon = al_load_bitmap("ship.png");
	if (!displayIcon) {
		al_show_native_message_box(NULL, "WARNING!", "ERROR", "ERROR CANNOT LOAD ICON!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_display_icon(display, displayIcon);

	//_______________________________________________________________________________________________________________________________
	//-------------------------------------------------------REGISTER EVENT SOURCE---------------------------------------------------
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//_______________________________________________________________________________________________________________________________
	//-------------------------------------------------------------MAIN LOOP---------------------------------------------------------
	al_start_timer(timer);

	while(!end) {

		al_wait_for_event(event_queue, &ev);
		
		while (menu && !end) {
			al_play_sample_instance(inst_menu);
			//al_draw_bitmap(menuImage, 0, 0, 0);
			al_draw_scaled_bitmap(menuImage, 0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage), 0, 0, width_w, height_w, 0);
			al_draw_textf(font30, al_map_rgb(255, 255, 255), width_w / 2, 50, ALLEGRO_ALIGN_CENTER, "NAVE VETOR");
			al_draw_textf(font20, missionSanaColor, width_w / 2, 250, ALLEGRO_ALIGN_CENTER, missionSanaString);
			al_draw_textf(font20, missionShitakeColor, width_w / 2, 350, ALLEGRO_ALIGN_CENTER, missionShitakeString);

			clock_t endTime = clock();
			double elapsed_secs = double(endTime - countTime) / CLOCKS_PER_SEC;
			if (elapsed_secs > 3 || countTime == 0) {
				al_wait_for_event(event_queue, &ev);
				countTime = 0;

				if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					DestroyAll();
					return 0;
				} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
					switch (ev.keyboard.keycode) {
						ALLEGRO_COLOR temp;
					case ALLEGRO_KEY_ESCAPE:
						DestroyAll();
						return 0;
						break;
					case ALLEGRO_KEY_UP:
						al_stop_sample_instance(inst_menuOk);
						al_play_sample_instance(inst_menuOk);
						temp = missionShitakeColor;
						missionShitakeColor = missionSanaColor;
						missionSanaColor = temp;
						mission = (mission % 2) + 1;
						break;
					case ALLEGRO_KEY_DOWN:
						al_stop_sample_instance(inst_menuOk);
						al_play_sample_instance(inst_menuOk);
						temp = missionShitakeColor;
						missionShitakeColor = missionSanaColor;
						missionSanaColor = temp;
						mission = (mission % 2) + 1;
						break;
					case ALLEGRO_KEY_RIGHT:
						al_stop_sample_instance(inst_menuOk);
						al_play_sample_instance(inst_menuOk);
						temp = missionShitakeColor;
						missionShitakeColor = missionSanaColor;
						missionSanaColor = temp;
						mission = (mission % 2) + 1;
						break;
					case ALLEGRO_KEY_LEFT:
						al_stop_sample_instance(inst_menuOk);
						al_play_sample_instance(inst_menuOk);
						temp = missionShitakeColor;
						missionShitakeColor = missionSanaColor;
						missionSanaColor = temp;
						mission = (mission % 2) + 1;
						break;
					case ALLEGRO_KEY_D:
						al_stop_sample_instance(inst_menu);
						if ((mission == 1 && missionSanaString != "MISSION KAITEN - COMPLETE") || (mission == 2 && missionShitakeString != "MISSION SHITAKE - COMPLETE")) {
							menu = false;
							Graphics::LoadSprites();
							if (!boss2Image || !shipImage) {
								al_show_native_message_box(NULL, "WARNING!", "ERROR", "ERROR LOADING SPRITES", NULL, ALLEGRO_MESSAGEBOX_ERROR);
								return -1;
							}
							InitAll();
							InitGame();
						} 
						break;
					case ALLEGRO_KEY_N:
						al_stop_sample_instance(inst_menu);
						if ((mission == 1 && missionSanaString != "MISSION KAITEN - COMPLETE") || (mission == 2 && missionShitakeString != "MISSION SHITAKE - COMPLETE")) {
							menu = false;
							Graphics::LoadSprites();
							if (!boss2Image || !shipImage) {
								al_show_native_message_box(NULL, "WARNING!", "ERROR", "ERROR LOADING SPRITES", NULL, ALLEGRO_MESSAGEBOX_ERROR);
								return -1;
							}
							InitAll();
							InitGame();
						}
						break;
					case ALLEGRO_KEY_ENTER:
						al_stop_sample_instance(inst_menu);
						if ((mission == 1 && missionSanaString != "MISSION KAITEN - COMPLETE") || (mission == 2 && missionShitakeString != "MISSION SHITAKE - COMPLETE")) {
							menu = false;
							Graphics::LoadSprites();
							if (!boss2Image || !shipImage) {
								al_show_native_message_box(NULL, "WARNING!", "ERROR", "ERROR LOADING SPRITES", NULL, ALLEGRO_MESSAGEBOX_ERROR);
								return -1;
							}
							InitAll();
							InitGame();
						}
						break;
					}
				}
			} else {
				al_destroy_event_queue(event_queue);
				event_queue = al_create_event_queue();
				al_register_event_source(event_queue, al_get_display_event_source(display));
				al_register_event_source(event_queue, al_get_keyboard_event_source());
				al_register_event_source(event_queue, al_get_timer_event_source(timer));
				createNewEventQueue = false;
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		//___________________________________________________________________________________________________________________________
		//---------------------------------------------------------LOAD SPRITES------------------------------------------------------

		//___________________________________________________________________________________________________________________________
		//-----------------------------------------------------EVENTS AND GAME LOGIC-------------------------------------------------
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			end = true;
		}else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					end = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;			
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_D:
					Combat::ShootBullets(bullets, NUM_BULLETS, ship);
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_N:
					Combat::ShootBullets(bullets, NUM_BULLETS, ship);
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = true;
					break;	
			}
		}else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_ENTER:
					keys[ENTER] = false;
					break;	
			}	
		}else if (ev.type == ALLEGRO_EVENT_TIMER){
			draw = true;
			if(keys[UP])
				Moviment::MoveShipUp(ship);
			if(keys[DOWN])
				Moviment::MoveShipDown(ship);
			if(keys[RIGHT])
				Moviment::MoveShipRight(ship);
			if(keys[LEFT])
				Moviment::MoveShipLeft(ship);
			if(keys[SPACE])
				Moviment::RefreshBullet(bullets, NUM_BULLETS);
				
			
			if(!game_over){

				switch (level) {
					case 1:
						if (!isPlaying[0]) {
							Sound::StopAllMusic();
							isPlaying[0] = true;
							al_play_sample_instance(inst_sound_level_2);
						}
						break;
					case 2:
						if (!isPlaying[1]) {
							Sound::StopAllMusic();
							isPlaying[1] = true;
							al_play_sample_instance(inst_sound_level_1);
						}
						break;
					case 3:
						if (!isPlaying[2]) {
							Sound::StopAllMusic();
							isPlaying[2] = true;
							al_play_sample_instance(inst_sound_level_3);
						}
						break;
				}

				Moviment::RefreshBackground(stars_background, NUM_LAYERS, NUM_STARS);
				
				//BOOS1
				if(bosses[0].release){
					ReleaseBoss(bosses,ship, 0);
					dir = 0;
				}
				
				//BOOS2
				if(bosses[1].release && !bosses[0].active && !bosses[2].active){
					ReleaseBoss(bosses,ship, 1);
					dir = 0;
				}

				//BOOS3
				if (bosses[2].release && !bosses[0].active && !bosses[1].active) {
					ReleaseBoss(bosses, ship, 2);
					dir = 0;
				}
					
				ReleaseComet(comets, NUM_COMETS);
				Moviment::RefreshComet(comets, NUM_COMETS);
				Combat::BulletCollider(bullets, NUM_BULLETS, comets, NUM_COMETS, ship,bosses);
				Combat::CometCollider(comets, NUM_COMETS, ship);

				if(ship.life <= 0){
					game_over = true;
				}

				////BOSS1
				if(bosses[0].active) {

					Combat::BossCollider(bosses, ship, bullets);

					if (dir == 0) {
						if (mission == 1) {
							Moviment::RefreshBoss(bosses, 0);
						}
						else {
							Moviment::RefreshBossVertical(bosses, 0);
						}
					} else {
						if (mission == 1) {
							Moviment::RefreshUpBoss(bosses, 0);
						}
						else {
							Moviment::RefreshUpBossVertical(bosses, 0);
						}
					}

					Combat::BossBulletCollider(bulletsBoss,NUM_BULLETS_BOSS,comets,NUM_COMETS,ship,bosses);
					attchefe = rand() % 35;
					attchefe2 = rand() % 50;
					attchefe3 = rand() % 100;
					attchefe4 = rand() % 200;
					attchefe5 = rand() % 500;

					if(attchefe % 2 == 0 && attchefe2 % 2 == 0 && attchefe3 % 2 == 0 && attchefe4 % 2 == 0 && attchefe5 % 2 == 0){
						Combat::BossShootBullet(bulletsBoss,NUM_BULLETS_BOSS,bosses);
					}
					Moviment::BossRefreshBullet(bulletsBoss,NUM_BULLETS_BOSS);

					if(bosses[0].life <= 0 && bosses[0].active){
						bosses[0].active = false;
						ship.points += 25;
						difficulty = 650;
						stopt1 = true;
						stopt2 = false;
						level++;
						BossInitBullet(bulletsBoss, NUM_BULLETS_BOSS);
						ship.life += 5;
					}
				}
				
				//BOSS2
				if(bosses[1].active) {

					Combat::BossCollider(bosses, ship, bullets);

					if (dir == 0) {
						if (mission == 1) {
							Moviment::RefreshBoss(bosses, 1);
						}
						else {
							Moviment::RefreshBossVertical(bosses, 1);
						}
					} else {
						if (mission == 1) {
							Moviment::RefreshUpBoss(bosses, 1);
						}
						else {
							Moviment::RefreshUpBossVertical(bosses, 1);
						}
					}

					Combat::BossBulletCollider(bulletsBoss,NUM_BULLETS_BOSS,comets,NUM_COMETS,ship,bosses);
					attchefe = rand() % 35;
					attchefe2 = rand() % 50;
					attchefe3 = rand() % 100;
					attchefe4 = rand() % 200;
					attchefe5 = rand() % 500;

					if(attchefe % 2 == 0 && attchefe2 % 2 == 0 && attchefe3 % 2 == 0 && attchefe4 % 2 == 0 && attchefe5 % 2 == 0){
						Combat::BossShootBullet(bulletsBoss,NUM_BULLETS_BOSS,bosses);
					}
					Moviment::BossRefreshBullet(bulletsBoss,NUM_BULLETS_BOSS);

					if(bosses[1].life <= 0 && bosses[1].active){
						bosses[1].active = false;
						ship.points += 70;
						difficulty = 350;
						stopt1 = true;
						stopt2 = false;
						level++;
						BossInitBullet(bulletsBoss, NUM_BULLETS_BOSS);
						ship.life += 30;
					}
				}

				//BOSS3
				if (bosses[2].active) {

					Combat::BossCollider(bosses, ship, bullets);

					if (dir == 0) {
						if (mission == 1) {
							Moviment::RefreshBoss(bosses, 2);
						}
						else {
							Moviment::RefreshBossVertical(bosses, 2);
						}
					} else {
						if (mission == 1) {
							Moviment::RefreshUpBoss(bosses, 2);
						}
						else {
							Moviment::RefreshUpBossVertical(bosses, 2);
						}
					}

					Combat::BossBulletCollider(bulletsBoss, NUM_BULLETS_BOSS, comets, NUM_COMETS, ship, bosses);
					attchefe = rand() % 35;
					attchefe2 = rand() % 50;
					attchefe3 = rand() % 100;
					attchefe4 = rand() % 200;
					attchefe5 = rand() % 500;

					if (attchefe % 2 == 0 && attchefe2 % 2 == 0 && attchefe3 % 2 == 0 && attchefe4 % 2 == 0 && attchefe5 % 2 == 0) {
						Combat::BossShootBullet(bulletsBoss, NUM_BULLETS_BOSS, bosses);
					}
					Moviment::BossRefreshBullet(bulletsBoss, NUM_BULLETS_BOSS);

					if (bosses[2].life <= 0 && bosses[2].active) {
						bosses[2].active = false;
						ship.points += 1000;
						difficulty = 150;
						stopt1 = true;
						stopt2 = false;
						level++;
						BossInitBullet(bulletsBoss, NUM_BULLETS_BOSS);
						ship.life += 100;
						menu = true;
						if(mission==1){
							Sound::StopAllMusic();
							missionSanaString = "MISSION KAITEN - COMPLETE";
							al_play_sample_instance(inst_sucess);
						} else {
							Sound::StopAllMusic();
							missionShitakeString = "MISSION SHITAKE - COMPLETE";
							al_play_sample_instance(inst_sucess);
						}
						countTime = clock();
					}
				}
			
			}else{
				al_stop_sample_instance(inst_sound_level_1);
				al_stop_sample_instance(inst_sound_level_2);
				al_stop_sample_instance(inst_sound_level_3);
				al_stop_sample_instance(inst_explosionBoss);
				al_stop_sample_instance(inst_explosionMeteor);
				al_stop_sample_instance(inst_laser);

				if(keys[ENTER]){
					InitGame();
				}
			}
		}
		
		//___________________________________________________________________________________________________________________________
		//-------------------------------------------------------------DRAW----------------------------------------------------------
		if(draw && al_is_event_queue_empty(event_queue)){
			draw = false;
			
			if(!game_over){
				Graphics::DrawBoss(bosses);
				Graphics::DrawBackground(stars_background, NUM_LAYERS, NUM_STARS);
				Graphics::DrawShip(ship);
				Graphics::DrawBullet(bullets, NUM_BULLETS);
				Graphics::BossDrawBullet(bulletsBoss,NUM_BULLETS_BOSS);
				Graphics::DrawComet(comets, NUM_COMETS);
				al_draw_textf(font15, al_map_rgb(255,255,255), 15, 0, ALLEGRO_ALIGN_LEFT,"LIFE: %d", ship.life);
				al_draw_textf(font15, al_map_rgb(255, 255, 255), width_w / 2, 0, ALLEGRO_ALIGN_CENTER, "SCORE: %d", ship.points);
				al_draw_textf(font15, al_map_rgb(255, 255, 255), width_w-15, 0, ALLEGRO_ALIGN_RIGHT, "LEVEL:%d", level);
			}else{
				al_draw_textf(font20, al_map_rgb(255,255,255), width_w / 2, (height_w / 2) - 30, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_textf(font15, al_map_rgb(255, 255, 255), width_w / 2, (height_w / 2), ALLEGRO_ALIGN_CENTRE, "Your Score: %d", ship.points);
				al_draw_textf(font13, al_map_rgb(255, 255, 255), width_w / 2, (height_w / 2) + 30, ALLEGRO_ALIGN_CENTRE, "Press ENTER to play again or ESC to exit");
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}

		//___________________________________________________________________________________________________________________________
		//-----------------------------------------------------------END LOOP--------------------------------------------------------
	}

	//___________________________________________________________________
	//----------------------------Ending Game----------------------------
	DestroyAll();
	return 0;
}

//__________________________________________________________________________________________________________________________________
//----------------------------------------------------------BASIC FUNCTIONS---------------------------------------------------------

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------SHIP---------------------------------------------------------------
void InitShip (Ship &ship){
	ship.x = 20;
	ship.y = height_w/2;
	ship.ID = PLAYER;
	ship.life = 15;
	ship.velocity = 7;
	if (mission==1) {
		ship.edge_x = 27;
		ship.edge_y = 56;
		ship.edge_posX = 25;
		ship.edge_posY = 55;
	} else {
		ship.edge_x = 50;
		ship.edge_y = 27;
		ship.edge_posX = 50;
		ship.edge_posY = 55;
	}
	ship.points = 0;
}

//__________________________________________________________________________________________________________________________________
//--------------------------------------------------------------BULLET--------------------------------------------------------------
void InitBullet (Bullet bullets[], int size){
	for(int i = 0; i < size; i++){
		bullets[i].ID = BULLET;
		bullets[i].velocity = 10;
		bullets[i].active = false;
	}
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------COMET--------------------------------------------------------------
void InitComet (Comet comets[], int size){
	for(int i = 0; i < size; i++){
		comets[i].ID = ENEMY;
		comets[i].velocity = 5;
		comets[i].edge_x = 20;
		comets[i].edge_y = 20;
		comets[i].active = false;
		if (mission == 1) {
			comets[i].edge_posX = 21;
			comets[i].edge_posY = 21;
		} else {
			comets[i].edge_posX = 21;
			comets[i].edge_posY = 21;
		}
	}
}

void ReleaseComet (Comet comets[], int size){
	if (mission==1) {
		for (int i = 0; i < size; i++) {
			if (!comets[i].active) {
				if (rand() % int(float(difficulty) / 1.0f) == 0) {
					comets[i].x = width_w;
					comets[i].y = 55 + rand() % (height_w - 125);
					//comets[i].y = 5 + rand() % 395;
					comets[i].active = true;
					break;
				}
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (!comets[i].active) {
				if (rand() % int(float(difficulty) / 1.3f) == 0) {
					comets[i].x = 55 + rand() % (width_w - 125);
					comets[i].y = 0;
					//comets[i].y = 5 + rand() % 395;
					comets[i].active = true;
					break;
				}
			}
		}
	}
}
 
//__________________________________________________________________________________________________________________________________
//------------------------------------------------------------BACKGROUND------------------------------------------------------------
void InitBackground(Star stars_background[][NUM_STARS], int background_size, int s_size) {
	for (int i = 0; i < background_size; i++) {
		for (int x = 0; x < s_size; x++) {
			if (i == 0) {
				stars_background[i][x].ID = STAR;
				stars_background[i][x].x = 5 + rand() % (width_w - 10);
				stars_background[i][x].y = 5 + rand() % (width_w - 10);
				stars_background[i][x].velocity = 8;
			}
			else if (i == 1) {
				stars_background[i][x].ID = STAR;
				stars_background[i][x].x = 5 + rand() % (width_w - 10);
				stars_background[i][x].y = 5 + rand() % (width_w - 10);
				stars_background[i][x].velocity = 3;
			}
			else if (i == 2) {
				stars_background[i][x].ID = STAR;
				stars_background[i][x].x = 5 + rand() % (width_w - 10);
				stars_background[i][x].y = 5 + rand() % (width_w - 10);
				stars_background[i][x].velocity = 1;
			}
		}
	}
}

//__________________________________________________________________________________________________________________________________
//---------------------------------------------------------------BOSS---------------------------------------------------------------
void InitBoss (Boss bosses[]){
		bosses[0].ID = ENEMY;
		bosses[0].velocity = 2;
		bosses[0].edge_x = 35;
		bosses[0].edge_y = 40;
		bosses[0].active = false;
		bosses[0].life = 5;
		bosses[0].release = true;
		bosses[0].points = 10;
		bosses[1].ID = ENEMY;
		bosses[1].velocity = 4;
		bosses[1].active = false;
		bosses[1].life = 10;
		bosses[1].release = true;
		bosses[1].points = 75;
		bosses[2].ID = ENEMY;
		bosses[2].velocity = 5;
		bosses[2].edge_x = 35;
		bosses[2].edge_y = 35;
		bosses[2].active = false;
		bosses[2].life = 15;
		bosses[2].release = true;
		bosses[2].points = 175;

		if (mission == 1) {
			bosses[0].edge_posX = 10;
			bosses[0].edge_posY = 25;
			bosses[1].edge_x = 25;
			bosses[1].edge_y = 23;
			bosses[1].edge_posX = 1;
			bosses[1].edge_posY = 1;
			bosses[2].edge_posX = 20;
			bosses[2].edge_posY = 21;
		} else {
			bosses[0].edge_posX = 25;
			bosses[0].edge_posY = 25;
			bosses[1].edge_x = 35;
			bosses[1].edge_y = 30;
			bosses[1].edge_posX = 21;
			bosses[1].edge_posY = 30;
			bosses[2].edge_posX = 25;
			bosses[2].edge_posY = 21;
		}
}

void BossInitBullet (Bullet bulletsBoss[], int size){
	for(int i = 0; i < size; i++){
		bulletsBoss[i].ID = BULLET;
		bulletsBoss[i].velocity = 12;
		bulletsBoss[i].active = false;
	}
}

void ReleaseBoss(Boss bosses[], Ship &ship, int numBoss) {
	if (mission==1) {
		if (ship.points >= bosses[numBoss].points) {
			bosses[numBoss].x = width_w - 75;
			bosses[numBoss].y = 300;
			bosses[numBoss].active = true;
			bosses[numBoss].release = false;
		}
	} else {
		if (ship.points >= bosses[numBoss].points) {
			bosses[numBoss].x = width_w/2;
			bosses[numBoss].y = 0;
			bosses[numBoss].active = true;
			bosses[numBoss].release = false;
		}
	}
}

void InitAll() {
	//_______________________________________________________________________________________________________________________________
	//----------------------------------------------------------INITI FUNCTIONS------------------------------------------------------
	srand(time(NULL));
	InitShip(ship);
	InitBullet(bullets, NUM_BULLETS);
	InitComet(comets, NUM_COMETS);
	InitBackground(stars_background, NUM_LAYERS, NUM_STARS);
	InitBoss(bosses);
	BossInitBullet(bulletsBoss, NUM_BULLETS_BOSS);
}

void DestroyAll() {
	al_destroy_bitmap(displayIcon);
	Sound::DestroySound();
	Graphics::DestroySprites();	
	al_destroy_font(font13);
	al_destroy_font(font15);
	al_destroy_font(font20);
	al_destroy_font(font30);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

void InitGame() {
	//al_play_sample_instance(inst_menuOk);
	srand(time(NULL));
	InitShip(ship);
	InitBullet(bullets, NUM_BULLETS);
	BossInitBullet(bulletsBoss, NUM_BULLETS_BOSS);
	InitComet(comets, NUM_COMETS);
	InitBoss(bosses);
	InitBackground(stars_background, NUM_LAYERS, NUM_STARS);
	game_over = false;
	bosses[0].active = false;
	bosses[1].active = false;
	direction = 1;
	cont = 0;
	difficulty = 1100;
	dir = 0;
	stopt1 = false;
	stopt2 = true;
	level = 1;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
}