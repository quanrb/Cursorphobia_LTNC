#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "player.h"
#include "entity.h"
#include "ground.h"
using namespace std;

const float GRAVITY = 0.08f;
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
	return sqrt((getX() + getWidth()/2 - mouseX) * (getX() + getWidth()/2 - mouseX) + (getY() + getHeight()/2 - mouseY) * (getY() + getHeight()/2 - mouseY));
}

bool Player::jump()
{
	if (distanceFromCursor() < 100)
	{
		if (grounded) {
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
	if (score > highscore) {
		highscore = score;
	}
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	setX(getX() - 1); //autoscroll
	if (distanceFromCursor() < 100) {
		setAnimOffsetY(3, sin(SDL_GetTicks()/40) * vX - 1);
		setAnimOffsetY(4, -sin(SDL_GetTicks()/40) * vX -  1);
		if (mouseX < getX())
		{
			vX = 1/distanceFromCursor() * 100;
		}
		else if (mouseX > getX() + getWidth())
		{
			vX = 1/distanceFromCursor() * -100;
		}
		else {
			vX = 0;
			if (mouseY > getY() && mouseY < getY() + getHeight()) {
				dead = CURSOR_DEATH; // dead = 1
			}
		}
	}
	else 
		vX = 0;
	setX(getX() + vX);
	setY(getY() + vY);

	if(getY() > SCREEN_HEIGHT) //bugged
		dead = HOLE_DEATH;

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

int Player::getScoreInt()
{
	return score;
}

int Player::getHighscoreInt()
{
	return highscore;
}

int Player::checkDead()
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
