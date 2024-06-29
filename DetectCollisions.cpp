#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;

	FloatRect detectionZone = character.getPosition();  // make a rect for all his parts

	FloatRect block;  // make a FloatRect to test each block
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around Thomas to detected collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero or higher than the end of the array
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	// Has the character fallen out of the map?
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	
	if (!character.getPosition().intersects(level))
		character.spawn(m_LM.getStartPosition(), GRAVITY);

	// Loop through all the local blocks
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Has character been burnt or drowned?
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);

					if (m_ArrayLevel[y][x] == 2)  // fire
					{
						// Play sound
						m_SM.playFallInFire();
					}
					else  // water
					{
						// play a sound
						m_SM.playFallInWater();
					}
				}
			}

			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}

				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}
			// More collision detected here once we have
			// learned about particle effect

			// Have the character's feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is alreade running
			if (!m_PS.running())
			{
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());
					}
				}
			}

			// Has the charater reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				reachedGoal == true;
			}
		}
	}

	return reachedGoal;
}