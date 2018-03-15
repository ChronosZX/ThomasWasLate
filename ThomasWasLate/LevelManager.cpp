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

}//end function nextlevel