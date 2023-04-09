#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "player.h"
#include "entity.h"
#include "ground.h"
using namespace std;

const float GRAVITY = 0.07f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int ALIVE = 0;
const int CURSOR_DEATH = 1;
const int HOLE_DEATH = 2;

Player::Player(float p_x, float p_y, vector<SDL_Texture*> p_tex)
	: Entity{ p_x, p_y, p_tex}
{
	setX(SCREEN_WIDTH/2 - getWidth()/2);
	setY(SCREEN_HEIGHT - getHeight() - 64);
}

float Player::distanceFromCursor()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	return sqrt(pow((getX() + getWidth()/2) - mouseX, 2) + pow((getY() + getHeight()/2) - mouseY, 2));
}

bool Player::jump()
{
	if (distanceFromCursor() < 100)
	{
		if (grounded)
		{
			vY = -(1/distanceFromCursor() * 200);
			grounded = false;
			return true;
		}
	}
	return false;
}

void Player::update(Ground& ground)
{
	timer++;
	score = timer/50; 
	if (score > highscore)
	{
		highscore = score;
	}
	setX(getX() - 1); //autoscroll
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (distanceFromCursor() < 100)
	{
		setAnimOffsetY(3, sin(SDL_GetTicks()/40) * vX - 2);
		setAnimOffsetY(4, -sin(SDL_GetTicks()/40) * vX - 2 );
		if (mouseX < getX())
		{
			vX = 1/distanceFromCursor() * 100;
		}
		else if (mouseX > getX() + getWidth())
		{
			vX = 1/distanceFromCursor() * -100;
		}
		else 
		{
			vX = 0;
			if (mouseY > getY() && mouseY < getY() + getHeight())
			{
				//kill player
				dead = CURSOR_DEATH; // dead = 1
			}
		}
	}
	else
	{
		vX = 0;
	}
	setX(getX() + vX);
	setY(getY() + vY);

	if(getY() > SCREEN_HEIGHT) 
	{
		dead = HOLE_DEATH;
	}

	if (ground.isTileBelow(getX(), getWidth()))
	{
		if (getY() + getHeight() < SCREEN_HEIGHT - 64)
		{
			vY += GRAVITY;
			grounded = false;
		}
		else 
		{
			setY(SCREEN_HEIGHT - getHeight() - 64);
			grounded = true;
		}
	}
	else //hole
	{
			vY += GRAVITY;
			grounded = false;
			if (getY() > SCREEN_HEIGHT)
			{
				dead = HOLE_DEATH; //2
			}
	}
	
}

const char* Player::getScore()
{
	string s = to_string(score);
	s = "SCORE: " + s;
	return s.c_str();
}

const char* Player::getHighscore()
{
	string s = to_string(highscore);
	s = "BEST: " + s;
	return s.c_str();
}

int Player::getScoreInt()
{
	return score;
}

int Player::isDead()
{
	return dead;
}

void Player::reset()
{
	setX(SCREEN_WIDTH/2 - getWidth()/2);
	setY(SCREEN_HEIGHT - getHeight() - 64);
	score = 0;
	timer = 0;
	vX = 0;
	vY = 0;
	dead = 0;
}
