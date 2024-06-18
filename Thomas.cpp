#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/thomas.png"));
	m_JumpDuration = .45;
}

//==========================================================================================
//Virtual function
bool Thomas::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		// Start a hump if not already jumping
		// but only if standing on a blick (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimerThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}
	return m_JustJumped;  // need to play a jumping sound
}