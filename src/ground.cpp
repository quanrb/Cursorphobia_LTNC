#include <iostream>
#include <vector>
#include <stdlib.h>
#include "ground.h"
#include "groundtile.h"
using namespace std;

const int SCREEN_HEIGHT = 480;

Ground::Ground(SDL_Texture* left, SDL_Texture* center, SDL_Texture* trap, SDL_Texture* right, SDL_Texture* hole)
{
	groundTex[0] = left;
	groundTex[1] = center;
	groundTex[2] = trap;
	groundTex[3] = right;
	groundTex[4] = hole;

	for (int i = 0; i < 14; i++)
	{
		groundTiles.push_back(GroundTile(groundTex[1], i));
	}
} 

GroundTile& Ground::getTile(int p_index)
{
	return groundTiles[p_index];
}

int Ground::getStatus(int p_index)
{
	return groundTiles[p_index].getStatus();
}

int Ground::getLength()
{
	return groundTiles.size();
}

bool Ground::isTileBelow(float x, int width)
{
	for (int i = 0; i < getLength(); i++)
	{
		switch (getStatus(i)) 
		{
			case 0:
				if (x + width > groundTiles[i].getX() + 24 && x < groundTiles[i].getX() + 64)
				{
					return true;
				}
				break;
			case 1:
				if (x + width > groundTiles[i].getX() && x < groundTiles[i].getX() + 64)
				{
					return true;
				}
				break;
			case 3:
				if (x + width > groundTiles[i].getX() && x < groundTiles[i].getX() + 40)
				{
					return true;
				}
				break;
		}
	} 
	return false;
}

bool Ground::fallBelow(float y, int height)
{
	for(int i = 0; i < getLength(); i++)
	{
		switch(getStatus(i)) 
		{
			case 2:
				if (y + height > groundTiles[i].getX() && y < groundTiles[i].getX() + 64)
					return true;
		}
	}
	return false;
}


void Ground::reset()
{
	for (int i = 0; i < getLength(); i++)
	{
		groundTiles[i].setStatus(1, groundTex);
		groundTiles[i].setX(i * 64.0f);
	}
	lastStatus = 1;
	holeCount = 0;
}


//responding new random groundTile
void Ground::update(int score)
{
	for (int i = 0; i < getLength(); i++)
	{
		groundTiles[i].setX(groundTiles[i].getX() - 1);
		if (groundTiles[i].getX() + 64 < 0)
		{
			groundTiles[i].setX(64 * (getLength() - 1) - 1);
			switch (lastStatus) 
			{
				case 0:
				{
					groundTiles[i].setStatus(1, groundTex);
					lastStatus = 1;
					holeCount = 0;
					break;
				} 
				case 1:
				{
					int randomInt = rand()%3 + 1;
					groundTiles[i].setStatus(randomInt, groundTex);
					lastStatus = randomInt;
					holeCount = 0;
					break;
				} 
				case 2:
				{
					int randomInt = rand()%3 + 1;
					holeCount = 0;
					if(randomInt != 1) 
					{
						randomInt = 2;
						trapCount++;
					}
					else 
					{
						trapCount = 0;
					}
					if (trapCount > 2)
					{
						randomInt = 1;
						trapCount = 0;
					}
					groundTiles[i].setStatus(randomInt, groundTex);
					lastStatus = randomInt;
					break;
				} 
				case 3:
				{
					groundTiles[i].setStatus(4, groundTex);
					lastStatus = 4;
					holeCount = 0;
					break;
				}
				case 4:
				{
					int randomInt = rand()%3;
					if (randomInt == 1 || randomInt == 2)
					{
						randomInt = 4;
						holeCount++;
					}
					else 
					{
						holeCount = 0;
					}
					if ((holeCount > 3 && score > 89) || (holeCount > 2 && score < 90))
					{
						randomInt = 0;
						holeCount = 0;
					}
					groundTiles[i].setStatus(randomInt, groundTex);
					lastStatus = randomInt;
					break;
				}
			}
		}
	}
}