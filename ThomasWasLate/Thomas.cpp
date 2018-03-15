#include "stdafx.h"
#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{

	//associate a texture with a sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/thomas.png"));

	m_JumpDuration = 0.45f;


}//end Thomas() Function

//====================================================

bool Thomas::handleInput()
{
	//always start assuming not jumping
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
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
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	//check right
	if (Keyboard::isKeyPressed(Keyboard::D))
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