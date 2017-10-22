#include "Sound.h"

void Sound::InitSound(float volume) {
	sound_level_1 = al_load_sample("music1.ogg");
	sound_level_2 = al_load_sample("music2.ogg");
	sound_level_3 = al_load_sample("music3.ogg");
	laser = al_load_sample("laser.wav");
	explosionMeteor = al_load_sample("explosion1.wav");
	explosionBoss = al_load_sample("explosion1.wav");
	menu = al_load_sample("success-menu.wav");
	sucess = al_load_sample("maxmakessounds__success.wav");
	menuOk = al_load_sample("kastenfrosch__gotitem.wav");

	inst_sound_level_1 = al_create_sample_instance(sound_level_1);
	inst_sound_level_2 = al_create_sample_instance(sound_level_2);
	inst_sound_level_3 = al_create_sample_instance(sound_level_3);
	inst_laser = al_create_sample_instance(laser);
	inst_explosionMeteor = al_create_sample_instance(explosionMeteor);
	inst_explosionBoss = al_create_sample_instance(explosionBoss);
	inst_menu = al_create_sample_instance(menu);
	inst_sucess = al_create_sample_instance(sucess);
	inst_menuOk = al_create_sample_instance(menuOk);

	al_attach_sample_instance_to_mixer(inst_sound_level_1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_sound_level_2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_sound_level_3, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_laser, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_explosionMeteor, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_explosionBoss, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_menu, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_sucess, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_menuOk, al_get_default_mixer());

	al_set_sample_instance_playmode(inst_sound_level_1, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(inst_sound_level_2, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(inst_sound_level_3, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(inst_menu, ALLEGRO_PLAYMODE_LOOP);

	al_set_sample_instance_gain(inst_sound_level_1, volume);
	al_set_sample_instance_gain(inst_sound_level_2, volume);
	al_set_sample_instance_gain(inst_sound_level_3, volume);
	al_set_sample_instance_gain(inst_menu, volume);
}

void Sound::DestroySound() {
	al_destroy_sample(sound_level_1);
	al_destroy_sample(sound_level_2);
	al_destroy_sample(sound_level_3);
	al_destroy_sample(laser);
	al_destroy_sample(explosionMeteor);
	al_destroy_sample(explosionBoss);
	al_destroy_sample(menu);
	al_destroy_sample(sucess);
	al_destroy_sample(menuOk);

	al_destroy_sample_instance(inst_sound_level_1);
	al_destroy_sample_instance(inst_sound_level_2);
	al_destroy_sample_instance(inst_sound_level_3);
	al_destroy_sample_instance(inst_laser);
	al_destroy_sample_instance(inst_explosionMeteor);
	al_destroy_sample_instance(inst_explosionBoss);
	al_destroy_sample_instance(inst_menu);
	al_destroy_sample_instance(inst_sucess);
	al_destroy_sample_instance(inst_menuOk);
}

void Sound::StopAllMusic() {
	al_stop_sample_instance(inst_sound_level_1);
	al_stop_sample_instance(inst_sound_level_2);
	al_stop_sample_instance(inst_sound_level_3);
	isPlaying[0] = false ;
	isPlaying[1] = false;
	isPlaying[2] = false;
}