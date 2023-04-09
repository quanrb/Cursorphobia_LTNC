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
	int getScoreInt();
	int getHighscoreInt();
	int isDead();
	void reset();
private:
	float vX, vY;
	bool grounded;
	int score = 0;
	int highscore = 0;
	int timer = 0;
	int dead = 0;
};