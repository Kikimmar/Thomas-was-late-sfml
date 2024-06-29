#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine
{
private:
	TextureHolder th;

	ParticleSystem m_PS;

	Thomas m_Thomas;
	Bob m_Bob;

	LevelManager m_LM;

	SoundManager m_SM;

	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	const int GRAVITY = 300;  // the force pushing the characters down

	RenderWindow m_Window;  // A regular RenderWindow

	// The main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	// Sprite and Texture for BG
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	bool m_Playing = true;  //Is the game currently playing

	bool m_Character1 = true;  //Is character 1 or 2 current focus

	bool m_SplitScreen = false;  //Start in full screen mode

	// Time left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	bool m_NewLevelRequired = true;  //Is it time for a new/first level

	VertexArray m_VALevel;  // the vertex array for the level tiles

	int** m_ArrayLevel = NULL;  // the 2D array with the map for the level, a pointer to a pointer

	Texture m_TextureTiles;  // texture for the level tiles
	
	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	void loadLevel(); // load a new level

	bool detectCollisions(PlayableCharacter& character);

	// Make a vector of the best plasec to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);

	// A vector of Vector2f for the fire emitter locations
	vector <Vector2f> m_FireEmittets;

public:
	Engine();

	void run();  //Run will call all the private functions
};