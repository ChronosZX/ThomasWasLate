#include "stdafx.h"
#include "LevelManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{

	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	//get next level
	m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVEL)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= 0.1f;
	}

	//load appropriate level from text file
	string leveltoLoad;
	switch (m_CurrentLevel)
	{
	case 1:
		leveltoLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;
	case 2:
		leveltoLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;
	case 3:
		leveltoLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;
	case 4:
		leveltoLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	}//end switch

	ifstream inputFile(leveltoLoad);
	string s;

	//count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	//store length of the rows (number of columns)
	m_LevelSize.x = s.length();

	//go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	//prep 2d array to hold int values from file
	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	//loop through file and store all the values in the 2D Array
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
	//close file when done
	inputFile.close();

	//what type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	//set size of vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	//start at beginning of vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x;++x)
	{
		for (int y = 0; y < m_LevelSize.y; ++y)
		{
			//position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = Vector2f(
				x*TILE_SIZE,
				y*TILE_SIZE);
			rVaLevel[currentVertex + 1].position = Vector2f(
				x*TILE_SIZE + TILE_SIZE,
				y*TILE_SIZE);
			rVaLevel[currentVertex + 2].position = Vector2f(
				x*TILE_SIZE + TILE_SIZE,
				y*TILE_SIZE + TILE_SIZE);
			rVaLevel[currentVertex + 3].position = Vector2f(
				x*TILE_SIZE,
				y*TILE_SIZE + TILE_SIZE);

			//which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			//set up texture coords
			rVaLevel[currentVertex + 0].texCoords = Vector2f(
				0, 
				0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords = Vector2f(
				TILE_SIZE,
				0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords = Vector2f(
				TILE_SIZE,
				TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(
				0,
				TILE_SIZE + verticalOffset);

			//update current vertex so we can draw the next quad
			currentVertex = currentVertex + VERTS_IN_QUAD;

		}//end y loop
	}//end x loop

	return arrayLevel;

}//end function nextlevel

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}
int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}
float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}
Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}