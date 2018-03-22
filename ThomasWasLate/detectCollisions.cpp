#include "stdafx.h"
#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	//initialise reachedGoal to false by default
	bool reachedGoal = false;

	//make a rectangle for the characters collision
	FloatRect detectionZone = character.getPosition();

	//Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;

	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3; //thomas is quite tall

	//Make sure we dn't test positions lower than 0
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;

	//make sure we don't test positions greater than our level size
	if (endX > m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY > m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	//Handle player falling out of level
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);

	if (!detectionZone.intersects(level))
	{
		//respawn character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	//loop through all nearby blocks
	for (int x = startX; x < endX; ++x)
	{
		for (int y = startY;y < endY;++y)
		{
			//set up current block
			block.left = x* TILE_SIZE;
			block.top = y*TILE_SIZE;

			//have we hit water or lava
			//use the head collider on the charcter as this allowes the player to sink a bit into the lava or water
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					//they are in the water/lava
					character.spawn(m_LM.getStartPosition(), GRAVITY);

					if (m_ArrayLevel[y][x] == 2)//FIRE FIRE FIRE
					{
						//TODO Play Sound
					}
					else //water
					{
						//TODO PLAY SOUND
					}
				}
			}//end water/lava test

			//is character colliding with a regular block

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

				//more collisions when we learn particles

				//have we reached the goal

				if (m_ArrayLevel[y][x] == 4)
				{
					//character reached goal
					reachedGoal = true;
				}
			}

		}
	}


	//return whether or not our characters have done that
	return reachedGoal;

}//end dectectCollisions()