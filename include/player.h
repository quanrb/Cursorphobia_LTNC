#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include "entity.h"
#include "ground.h"
using namespace std;

class Player : public Entity {
public:
	Player(float p_x, float p_y, vector<SDL_Texture*> p_tex);
	float distanceFromCursor();
	bool jump();
	void update(Ground& ground);
	const char* getScore();
	const char* getHighscore();
	int getScoreInt();
	int isDead();
	void reset();
private:
	float vX, vY;
	bool grounded;
	void animEyes();
	float clamp(float p_value, float p_min, float p_max);
	int score = 0;
	int highscore = 0;
	int timer = 0;
	int dead = 0;
};