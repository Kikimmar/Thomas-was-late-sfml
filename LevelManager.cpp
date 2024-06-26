#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include "TextureHolder.h"
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	m_CurrentLevel++;  // get the next level

	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	string levelToLoad;
	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;

	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;

	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	}//end switch

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}
	m_LevelSize.x = s.length();  // store the length of the rows

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2D array to hold the int values from the file
	int** arrayLevel = new int* [m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2D array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++)
		{
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}
		y++;
	}

	inputFile.close();	// close the file

	rVaLevel.setPrimitiveType(Quads);  // whats type of primitive are we using?

	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);  // set the size of the vertex array

	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = 
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position =
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Whitch tile from the sprite sheet should we use
			int vericalOfset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords =
				Vector2f(0, 0 + vericalOfset);

			rVaLevel[currentVertex + 1].texCoords =
				Vector2f(TILE_SIZE, 0 + vericalOfset);

			rVaLevel[currentVertex + 2].texCoords =
				Vector2f(TILE_SIZE, TILE_SIZE + vericalOfset);

			rVaLevel[currentVertex + 3].texCoords =
				Vector2f(0, TILE_SIZE + vericalOfset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
} // end of nextLevel function
//================================================================================

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}
//================================================================================

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}
//================================================================================

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}
//================================================================================

Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}