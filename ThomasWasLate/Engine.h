#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"

using namespace sf;
//CALLUM NO DON'T USE USING IN .h FILES
//IT'S FUCKING HORRIBLE

class Engine
{
private: //cannot be seen by other classes and subclasses
	TextureHolder th;
	//CALLUM DON'T NAME THINGS "th" (SINGLE LETTER ABBREVIATIONS)

	//our playable characters
	Thomas m_Thomas;
	Bob m_Bob;
	
	//a class to manage levels
	LevelManager m_LM;
	SoundManager m_SM;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	const int GRAVITY = 300;

	//a regular render window
	RenderWindow m_Window;

	//The Main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	//three views for background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HUDView;

	//sprite and texture for background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	//Is the game currently playing
	bool m_Playing = false;

	//is character one or two the current focus
	bool m_Character1 = true;
	//CALLUM NO USE enum INSTEAD, NAME BETTER TOOOOOOOOOOO

	//Full or split screen
	bool m_SplitScreen = false;

	//time left in current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;
	
	//is it time for a new first level?
	bool m_NewLevelRequired = true;

	//vertex array for level tiles
	VertexArray m_VALevel;
	//2D Array with the map for the level (data) (0-3)
	//a pointer to a point (aka 2D Array)
	int** m_ArrayLevel = NULL;
	//texture for the level files
	Texture m_TextureTiles;

	//private functions for internal use
private:
	void input();
	void update(float dtAsSeconds);
	void draw();

	//load level
	void loadLevel();

	//detect collisions
	//POLYMORPHISM
	bool detectCollisions(PlayableCharacter& character);

	//Make a vector of the best places to emit sounds from
	void populateEmitters(vector<Vector2f>& vSoundEmitters, int** arrayLevel);

	//a list (vector) of Vector2f to contain the fire emmiter locations
	vector<Vector2f> m_FireEmitters;

public:
	//Constructor
	Engine();
	//run will call all the private functions in the loop

	void run();
};