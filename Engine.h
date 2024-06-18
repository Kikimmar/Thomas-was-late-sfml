#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"

using namespace sf;

class Engine
{
private:
	TextureHolder th;

	Thomas m_Thomas;
	Bob m_Bob;

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

	bool m_NewLevelRequired = true;  //Is it time for a new/first level
	
	// Time left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

public:
	Engine();

	void run();  //Run will call all the private functions
};