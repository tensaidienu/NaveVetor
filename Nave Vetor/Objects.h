#pragma once

//------------------------ OBJECTS ------------------------
enum IDS {PLAYER, BULLET, ENEMY, STAR, POWER, BOSS, LEVEL};

enum TECLAS { UP, DOWN, LEFT, RIGHT, SPACE, ENTER };

struct Ship{
	int ID;
	int x;
	int y;
	int life;
	int velocity;
	int edge_x;
	int edge_y;
	int points;
	int edge_posX;
	int edge_posY;
};

struct Bullet{
	int ID;
	int x;
	int y;
	int velocity;
	bool active;
};

struct Comet{
	int ID;
	int x;
	int y;
	int velocity;
	int edge_x;
	int edge_y;
	bool active;
	int edge_posX;
	int edge_posY;
};

struct Star{
	int ID;
	int x;
	int y;
	int velocity;
};

struct Power{


};

struct Boss{
	int ID;
	int x;
	int y;
	int velocity;
	int life;
	int edge_x;
	int edge_y;
	bool active;
	bool release;
	bool bot;
	int edge_posX;
	int edge_posY;
	int points;
};

struct Level{

};