#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_acodec.h>


extern int direction;
extern int dir;
extern int cont;
extern int mission;
extern bool game_over;
extern bool isPlaying[3];

extern ALLEGRO_BITMAP  *menuImage;
extern ALLEGRO_BITMAP  *shipImage;
extern ALLEGRO_BITMAP  *cometImage;
extern ALLEGRO_BITMAP  *boss1Image;
extern ALLEGRO_BITMAP  *boss2Image;
extern ALLEGRO_BITMAP  *boss3Image;

extern ALLEGRO_SAMPLE *sound_level_1;
extern ALLEGRO_SAMPLE *sound_level_2;
extern ALLEGRO_SAMPLE *sound_level_3;
extern ALLEGRO_SAMPLE *laser;
extern ALLEGRO_SAMPLE *explosionMeteor;
extern ALLEGRO_SAMPLE *explosionBoss;
extern ALLEGRO_SAMPLE *menu;
extern ALLEGRO_SAMPLE *sucess;
extern ALLEGRO_SAMPLE *menuOk;

extern ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_1;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_2;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sound_level_3;
extern ALLEGRO_SAMPLE_INSTANCE *inst_laser;
extern ALLEGRO_SAMPLE_INSTANCE *inst_explosionMeteor;
extern ALLEGRO_SAMPLE_INSTANCE *inst_explosionBoss;
extern ALLEGRO_SAMPLE_INSTANCE *inst_menu;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sucess;
extern ALLEGRO_SAMPLE_INSTANCE *inst_menuOk;