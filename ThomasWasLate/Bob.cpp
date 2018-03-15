#include "stdafx.h"
#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{

	//associate a texture with a sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bob.png"));

	m_JumpDuration = 0.25f;


}//end Bob() Function

 //====================================================

bool Bob::handleInput()
{
	//always start assuming not jumping
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		//start a jump if not already jumping/falling
		if (!m_isFalling && !m_isJumping)
		{
			//perform jump
			m_isJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}//end not jumping/falling
	}//end keyboard W
	else
	{
		//stop jump early if W isn't held down
		m_isJumping = false;
		m_isFalling = true;
	}//end w not pressed

	 //check left
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	//check right
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	//return whether we just jumped or not
	return m_JustJumped;

}//end function handleInput