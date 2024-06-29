#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::White);  // Rub out last frame

	if (!m_SplitScreen)
	{
		m_Window.setView(m_BGMainView);  // Switch to BG view
		m_Window.draw(m_BackgroundSprite);  // Draw the BG
		m_Window.setView(m_MainView);  // Switch to m_MainView

		m_Window.draw(m_VALevel, &m_TextureTiles);  // Draw the level
		
		m_Window.draw(m_Thomas.getSprite());  // draw Thomas
		m_Window.draw(m_Bob.getSprite());  // draw Bob

		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}
	}
	else
	{
		// First draw Thomas side of the screen
		m_Window.setView(m_BGLeftView);  // Switch to BG view
		m_Window.draw(m_BackgroundSprite); // Draw the BG
		m_Window.setView(m_LeftView);  // Switch to m_LeftView

		m_Window.draw(m_VALevel, &m_TextureTiles);  // Draw the level

		m_Window.draw(m_Bob.getSprite());  // draw Bob
		m_Window.draw(m_Thomas.getSprite());  // draw Thomas

		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

		// Now draw Bob's side of the screen
		m_Window.setView(m_BGRightView);  // Switch to BG view
		m_Window.draw(m_BackgroundSprite); // Draw the BG
		m_Window.setView(m_RightView);  // Switch to m_RightView

		m_Window.draw(m_VALevel, &m_TextureTiles);  // Draw the level

		m_Window.draw(m_Thomas.getSprite());  // draw Thomas
		m_Window.draw(m_Bob.getSprite());  // draw Bob

		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

	}

	//Draw the HUD
	m_Window.setView(m_HudView);  // Switch to m_HudView
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}

	m_Window.display();  // Show everything we have just draw
}