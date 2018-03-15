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
		//NOTE THIS WILL BE MOVED TO loadLevel() later
		//Spawn Thomas and Bob

		m_Thomas.spawn(Vector2f(0, 0), GRAVITY);
		m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		//initalise time and level boolean
		m_TimeRemaining = 10;
		m_NewLevelRequired = false;

	}



	if (m_Playing)
	{
		//update thomas and bob
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		//count down the time player has left
		m_TimeRemaining -= dtAsSeconds;

		//have thomas and bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}

	}//end if playing

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
