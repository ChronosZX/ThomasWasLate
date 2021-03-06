#include "stdafx.h"
#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::populateEmitters(vector<Vector2f>& vSoundEmitters, int** arrayLevel)
{
	//make sure vector is empty
	vSoundEmitters.clear();

	//keep track of previous emitter
	//so we don't make too many
	FloatRect previousEmitter;

	//search through the level array fr fire
	for (int x = 0; x < m_LM.getLevelSize().x;x++)
	{
		for (int y = 0; y < m_LM.getLevelSize().y;y++)
		{
			if (arrayLevel[y][x] == 2) //2 = fire
			{
				FloatRect currentTile = FloatRect(x * TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
				if (!currentTile.intersects(previousEmitter))
				{
					vSoundEmitters.push_back(Vector2f(x*TILE_SIZE, y*TILE_SIZE));

					previousEmitter.left = x*TILE_SIZE;
					previousEmitter.top = y*TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;

				}

			}//end if
		}//end y
	}//end x
}