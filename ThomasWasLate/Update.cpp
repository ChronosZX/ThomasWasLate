#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	//TEMP CODE********
	if (m_NewLevelRequired)
	{
		loadLevel();

	}



	if (m_Playing)
	{
		//update thomas and bob
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		//detect collisions and see if the characters have reached the goal
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			//new level required
			m_NewLevelRequired = true;

			//todo play sound for reaching goal
		}
		else
		{
			//run bob collision detection
			detectCollisions(m_Bob);
		}

		//let bob and thomas jump on each others head
		if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
		{
			m_Bob.stopFalling(m_Thomas.getHead().top);
		}
		if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
		{
			m_Thomas.stopFalling(m_Bob.getHead().top);
		}

		//count down the time player has left
		m_TimeRemaining -= dtAsSeconds;

		//have thomas and bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}//end if playing

	for (auto it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		float posX = (*it).x;
		float posY = (*it).y;

		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		if (m_Thomas.getPosition().intersects(localRect))
		{
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}

	}

	//set view around the appropriate characters
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		if (m_Character1)//if we focus on thomas
		{
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else
		{
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}

}//end of update function
