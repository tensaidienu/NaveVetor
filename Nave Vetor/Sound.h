#pragma once
#include "Objects.h"
#include "Constants.h"
#include "Main.h"

class Sound {

public:
	static void InitSound(float volume);
	static void DestroySound();
	static void StopAllMusic();
};