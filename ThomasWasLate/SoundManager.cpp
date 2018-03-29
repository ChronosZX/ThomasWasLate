#include "stdafx.h"
#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager()
{
	//Load sound into buffers from file
	m_FireBuffer.loadFromFile("sound/fire1.wav");
	m_FallInFireBuffer.loadFromFile("sound/fallinfire.wav");
	m_FallInWaterBuffer.loadFromFile("sound/fallinwater.wav");
	m_JumpBuffer.loadFromFile("sound/jump.wav");
	m_ReachGoalBuffer.loadFromFile("sound/reachgoal.wav");

	//associate the sounds with the buffer
	m_Fire1Sound.setBuffer(m_FireBuffer);
	m_Fire2Sound.setBuffer(m_FireBuffer);
	m_Fire3Sound.setBuffer(m_FireBuffer);
	m_FallInFireSound.setBuffer(m_FallInFireBuffer);
	m_FallInWaterSound.setBuffer(m_FallInWaterBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

	//When the player is 50 pixels away or closer, the sound is at full volume
	float minDistance = 150;

	//The sound steadily reduces as the player moves away
	float attenuation = 15;

	//Set attenation levels for sounds
	m_Fire1Sound.setAttenuation(attenuation);
	m_Fire2Sound.setAttenuation(attenuation);
	m_Fire3Sound.setAttenuation(attenuation);

	//Set Min Distance
	m_Fire1Sound.setMinDistance(minDistance);
	m_Fire2Sound.setMinDistance(minDistance);
	m_Fire3Sound.setMinDistance(minDistance);

	//loop all fire sounds
	m_Fire1Sound.setLoop(true);
	m_Fire2Sound.setLoop(true);
	m_Fire3Sound.setLoop(true);

}//End SoundManager()

void SoundManager::playFire(Vector2f emitterLocation, Vector2f listenerLocation)
{
	//Set listener position
	Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.0f);

	//Choose Which sound to use
	switch (m_NextSound)
	{

	case 1:
		//locate/move source of the sound
		m_Fire1Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
		if (m_Fire1Sound.getStatus() == Sound::Status::Stopped)
		{
			//play the sound if it is not already playing
			m_Fire1Sound.play();
		}
		break;

	case 2:
		//locate/move source of the sound
		m_Fire2Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
		if (m_Fire2Sound.getStatus() == Sound::Status::Stopped)
		{
			//play the sound if it is not already playing
			m_Fire2Sound.play();
		}
		break;

	case 3:
		//locate/move source of the sound
		m_Fire3Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
		if (m_Fire3Sound.getStatus() == Sound::Status::Stopped)
		{
			//play the sound if it is not already playing
			m_Fire3Sound.play();
		}
		break;

	}//end Switch(m_NextSound)

	//increment to next fire sound
	m_NextSound++;

	//Go back to 1 when the 3rd sound has been started
	if (m_NextSound > 3)
	{
		m_NextSound = 1;
	}

}//end playFire()

void SoundManager::playFallInFire()
{
	m_FallInFireSound.setRelativeToListener(true);
	m_FallInFireSound.play();
}

void SoundManager::playFallInWater()
{
	m_FallInWaterSound.setRelativeToListener(true);
	m_FallInWaterSound.play();
}

void SoundManager::playJump()
{
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}

void SoundManager::playReachGoal()
{
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}
