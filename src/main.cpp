#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "renderwindow.h"
#include "ground.h"
#include "entity.h"
#include "player.h"
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int ALIVE = 0;
const int CURSOR_DEATH = 1;
const int HOLE_DEATH = 2;
const int FRAME_DEATH = 3;
const int TRAP_DEATH = 4;
const Uint8 *keyState;

RenderWindow window;
vector<SDL_Texture*> playerTex; 
SDL_Texture* groundTex[5];
SDL_Texture* arrow;
SDL_Texture* highscoreBox;
SDL_Texture* deathOverlay;
SDL_Texture* logo;
TTF_Font* font32;
TTF_Font* font32_outline;
TTF_Font* font24;
TTF_Font* font16;
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
Mix_Chunk* jumpSfx;
Mix_Chunk* fallSfx;
Mix_Chunk* hitSfx;
Mix_Chunk* clickSfx;

bool gameRunning = true;
bool playedDeathSFX = false;
bool mainMenu = true;
bool instruction = true;

bool init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	window.create("Cursorphobia", SCREEN_WIDTH, SCREEN_HEIGHT);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	srand((unsigned)time(0));

	playerTex.push_back(window.loadTexture("res/textures/player/player_0.png"));
	playerTex.push_back(window.loadTexture("res/textures/player/player_1.png"));
	playerTex.push_back(window.loadTexture("res/textures/player/player_2.png"));
	playerTex.push_back(window.loadTexture("res/textures/player/player_3.png"));
	playerTex.push_back(window.loadTexture("res/textures/player/player_4.png"));
	groundTex[0] = window.loadTexture("res/textures/ground/left.png");
	groundTex[1] = window.loadTexture("res/textures/ground/center.png");
	groundTex[2] = window.loadTexture("res/textures/ground/trap.png");
	groundTex[3] = window.loadTexture("res/textures/ground/right.png");
	groundTex[4] = window.loadTexture("res/textures/ground/hole.png");
	arrow = window.loadTexture("res/textures/arrow.png");
	highscoreBox = window.loadTexture("res/textures/highscore_box.png");
	deathOverlay = window.loadTexture("res/textures/death_overlay.png");
	logo = window.loadTexture("res/textures/logo.png");
	font32 = TTF_OpenFont("res/fonts/cocogoose.ttf", 32);
	font32_outline = TTF_OpenFont("res/fonts/cocogoose.ttf", 32);
	font24 = TTF_OpenFont("res/fonts/cocogoose.ttf", 24);
	font16 = TTF_OpenFont("res/fonts/cocogoose.ttf", 16);
	TTF_SetFontOutline(font32_outline, 3); 

	jumpSfx = Mix_LoadWAV("res/sounds/jump.wav");
	fallSfx = Mix_LoadWAV("res/sounds/fall.wav");
	hitSfx = Mix_LoadWAV("res/sounds/hit.wav");
	clickSfx = Mix_LoadWAV("res/sounds/click.wav");
	Mix_PlayChannel(-1, jumpSfx, 0);

	return true;
}

bool load = init();
Player player(0, 0, playerTex);
Ground ground(groundTex[0], groundTex[1], groundTex[2], groundTex[3], groundTex[4]);

void reset()
{
	player.reset();
	ground.reset();
}

void gameLoop()
{
	SDL_Event event;
 	while (SDL_PollEvent(&event)) 
 	{
    	switch (event.type) {
    	case SDL_QUIT: 
    	{
      		gameRunning = false;
      		break;
    	}
    	case SDL_MOUSEBUTTONDOWN:
    	{
    		if (mainMenu)
    		{
    			if (event.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 1500)
    			{
    				mainMenu = false;
					instruction = false;
    				Mix_PlayChannel(-1, clickSfx, 0);
    			}
    		}

			else if(instruction)
			{
    			Mix_PlayChannel(-1, clickSfx, 0);
				instruction = false;
			}

    		else
    		{
    			if (event.button.button == SDL_BUTTON_LEFT && player.checkDead() == ALIVE)
    			{
					if (player.jump())
					{
						Mix_PlayChannel(-1, jumpSfx, 0);
					}
				} 
				else if (player.checkDead() != ALIVE)
				{
					Mix_PlayChannel(-1, clickSfx, 0);
					reset();
					playedDeathSFX = false;
				}
    		}
    		break;
    	}
		case SDL_KEYDOWN:
		{
			if(event.key.keysym.sym == SDLK_i) 
			{
				if(mainMenu)
				{
					mainMenu = false;
					Mix_PlayChannel(-1, clickSfx, 0);
				}
				break;
			}
			else if(event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameRunning = false;
				break;
			}
		}
    	}
	}
	if (mainMenu)
	{
		if (SDL_GetTicks() < 2000)
		{
			window.clear();
			window.renderCenter(0, sin(SDL_GetTicks()/100)*2 - 4, "LTNC", font24, white);
			window.display();
		}
		else {
			window.clear();
			window.render( SCREEN_WIDTH/2 - 234, SCREEN_HEIGHT/2 - 90 - 34, logo);
			window.renderCenter( 0, 90 + sin(SDL_GetTicks()/100) * 2, "Press 'i' for instructions, or", font24, white);
			window.renderCenter( 0, 124 + sin(SDL_GetTicks()/100) * 2, "Click to start", font24, white);
			window.renderCenter( 0, 154 + sin(SDL_GetTicks()/100) * 2, "(Or press 'ESC' to quit)", font16, white);
		    window.render(650, sin(SDL_GetTicks()/100) + 25, "22028290", font24, white);
			for (int i = 0; i < ground.getLength(); i++)
			{
				window.render(ground.getTile(i));
			}
			window.display();
		}
	}

	else if(instruction)
	{
		window.clear();
		// window.render(deathOverlay);
		window.renderCenter(0, -64, "Just... use your mouse. There are some ground rules:", font24, white);
		window.renderCenter(0, -24, "1. You fall, you die.", font24, white);
		window.renderCenter(0, 16, "2. You land on the trap, you die.", font24, white);
		window.renderCenter(0, 56, "3. You got touched by the cursor, you die.", font24, white);
		window.renderCenter(0, 96, "(And I really mean it)", font16, white);
		window.render(560, 450 + sin(SDL_GetTicks()/100) * 2, "Ready to start? Just click.", font16, white);
		window.display();
	}

	else
	{
		if (player.checkDead() != CURSOR_DEATH && player.checkDead() != TRAP_DEATH)
		{
			ground.update(player.getScoreInt());
		}

		if (player.checkDead() == ALIVE)
		{
			player.update(ground);
		}
		else if (!playedDeathSFX) 
		{
			if (player.checkDead() == CURSOR_DEATH  || player.checkDead() == TRAP_DEATH)
			{
				Mix_PlayChannel(-1, hitSfx, 0);
			} 
			else if (player.checkDead() == HOLE_DEATH || player.checkDead() == FRAME_DEATH)
			{
				Mix_PlayChannel(-1, fallSfx, 0);
			}
			playedDeathSFX = true;
		}

		window.clear();
		window.render(player);

		for (int i = 0; i < ground.getLength(); i++) {
			window.render(ground.getTile(i));
		}
	    window.render(650, sin(SDL_GetTicks()/100) + 25, "22028290", font24, white);
		window.render(25, 30, arrow);
        window.render(62, 20, ("SCORE: " + to_string(player.getScoreInt())).c_str(), font32_outline, black);
        window.render(65, 23, ("SCORE: " + to_string(player.getScoreInt())).c_str(), font32, white);
        window.render(0, 65, highscoreBox);
        window.render(65, 64, ("BEST: " + to_string(player.getHighscoreInt())).c_str(), font16, white);

		if (player.checkDead() != ALIVE)
		{
			window.render(deathOverlay);
			if (player.checkDead() == CURSOR_DEATH)
			{
				window.renderCenter(0, -24, "The cursor is poisonous...", font24, white);
				window.renderCenter(0, 12, "Still want to beat it? Click to revenge.", font16, white);
			}
			else if(player.checkDead() == FRAME_DEATH) 
			{
				window.renderCenter(0, -24, "Are you a snail?", font24, white);
				window.renderCenter(0, 12, "Boosted up your engine? Click to retry.", font16, white);
			}
			else if (player.checkDead() == HOLE_DEATH)
			{
				window.renderCenter(0, -24, "The hole had its meal...", font24, white);
				window.renderCenter(0, 12, "The hole could not eat you all? Click to retry.", font16, white);
			}
			else if(player.checkDead() == TRAP_DEATH)
			{
				window.renderCenter(0, -24, "I told you...", font24, white);
				window.renderCenter(0, 12, "The hole could not eat you all? Click to retry.", font16, white);
			}
		}
		window.display();
	}
}

int main(int argc, char* args[])
{
	while (gameRunning) 
	{
    	gameLoop();
    	if (player.getScoreInt() < 25)
		{
			SDL_Delay(15);
		}
		else if (player.getScoreInt() < 50) 
		{
			SDL_Delay(13);
		}
		else if(player.getScoreInt() < 100)
		{
			SDL_Delay(11);
		}
		else {
			SDL_Delay(5);
		}
	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font32_outline);
	TTF_CloseFont(font24);
	TTF_CloseFont(font16);
	TTF_Quit();
	SDL_Quit();

	return 0;
}