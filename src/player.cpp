#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
#include <sstream>
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
const int FRAME_DEATH = 3;
const int TRAP_DEATH = 4;

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

float Player::clamp(float value, float p_min, float p_max)
{
	if (value > p_max)
		return p_max;
	if (value < p_min)
		return p_min;
	return value;
}

void Player::eyes()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	setAnimOffsetX(0, clamp(mouseX - getX() - getWidth()/2, -2, 2));
	setAnimOffsetY(0, clamp(mouseY - getY() - getHeight()/2 + 15, -2, 2));
}

void Player::getscoreInt(int score)
{
	ofstream outFile("res/highScore.txt", ios::app);
	outFile << score << endl;
	ifstream inFile("res/highScore.txt");
	vector<int> Scores;
	while(!inFile.eof())
	{
		int getScore;
		inFile >> getScore;
		Scores.push_back(getScore);
	}
	sort(Scores.begin(), Scores.end(), greater<int>());
	highscore = Scores[0];
}

void Player::update(Ground& ground)
{
	timer++;
	score = timer/50; 
	getscoreInt(score);
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	setX(getX() - 1);

	eyes();

	if (distanceFromCursor() < 100) {
		setAnimOffsetY(3, sin(SDL_GetTicks()/40) * vX - 2);
		setAnimOffsetY(4, -sin(SDL_GetTicks()/40) * vX - 2);
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
				dead = CURSOR_DEATH;
			}
		}
	}
	else 
		vX = 0;
		
	setX(getX() + vX);
	setY(getY() + vY);

	if(getY() > SCREEN_HEIGHT)
		dead = HOLE_DEATH;

	else if (getX() + getWidth() <= 0) 
		dead = FRAME_DEATH;

	if (ground.isTileBelow(getX(), getWidth()))
	{
		if (getY() + getHeight() < SCREEN_HEIGHT - 55)
		{
			vY += GRAVITY;
			grounded = false;
		}
		else 
		{
			setY(SCREEN_HEIGHT - getHeight() - 55);
			grounded = true;
		}
	}

	else 
	{
		if (ground.fallBelow(getX(), getWidth()))
		{
			if(getY() + getHeight() >= SCREEN_HEIGHT - 64)
			{
				dead = TRAP_DEATH;
			}
			else
			{
				vY += GRAVITY;
				grounded = false;
			}
		}
		else
		{
			vY += GRAVITY;
			grounded = false;
			if (getY() > SCREEN_HEIGHT)
			{
				dead = HOLE_DEATH;
			}
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
	setY(SCREEN_HEIGHT - getHeight() - 55);
	score = 0;
	timer = 0;
	vX = 0;
	vY = 0;
	dead = 0;
}
