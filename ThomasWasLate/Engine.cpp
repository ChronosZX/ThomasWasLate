#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	//Get the Screen Res
	//Create an SFML view

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Thomas Was Late", Style::Fullscreen);

	m_MainView.setSize(resolution);
	m_HUDView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//initialise split screen view
	m_LeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_RightView.setViewport(FloatRect(0.5f, 0.001f, 0.498f, 0.998f));

	m_BGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	m_BGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.498f, 0.998f));

	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine::run()
{
	Clock clock;

	while (m_Window.isOpen())
	{
		
		Time dt = clock.restart();
		m_GameTimeTotal += dt;

		//make a decimal fraction
		float dtAsSeconds = dt.asSeconds();

		//call each part of the game loop
		input();
		update(dtAsSeconds);
		draw();
	}
}