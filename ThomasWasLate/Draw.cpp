#include "stdafx.h"
#include "Engine.h"

void Engine::draw()
{
	//erase the last frame
	m_Window.clear(Color::White);

	//single screen
	if (!m_SplitScreen)
	{
		//Switch to background view
		m_Window.setView(m_BGMainView);
		//draw background
		m_Window.draw(m_BackgroundSprite);
		//set main view
		m_Window.setView(m_MainView);
		//TODO: DRAW ALL THE STUFF

		//draw thomas and bob
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());


	}//end single screen
	//split screen
	else
	{
		//***Draw Thomas screen***
		//switch to background
		m_Window.setView(m_BGLeftView);
		//draw background
		m_Window.draw(m_BackgroundSprite);
		//switch to main view for left
		m_Window.setView(m_LeftView);
		//TODO: DRAW ALL THE STUFF

		//draw thomas and bob
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		//***Draw Bob screen***
		//switch to background
		m_Window.setView(m_BGRightView);
		//draw background
		m_Window.draw(m_BackgroundSprite);
		//switch to main view for left
		m_Window.setView(m_RightView);
		//TODO - DRAW ALL THE STUFF
		//draw thomas and bob
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

	}//end split screen

	//Draw HUD
	//Switch to HUD View
	m_Window.setView(m_HUDView);
	//TODO: DRAW HUD

	//show everything we have drawn
	m_Window.display();

}//end of draw function