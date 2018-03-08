#include "stdafx.h"
#include "PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f startPosition, float gravity)
{
	//place player at starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	//initialise the gravity
	m_Gravity = gravity;

	//move the sprite to the position
	m_Sprite.setPosition(m_Position);


}//end spawn

void PlayableCharacter::update(float elapsedTime) //in fractions of a second
{
	//check if moving left or right
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	//Handle Jumping
	if (m_isJumping)
	{
		//update how long this jump has been going
		m_TimeThisJump += elapsedTime;

		//if we are still jumping upwards...
		if (m_TimeThisJump < m_JumpDuration)
		{
			//move up at twice the speed of gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		//if jump duration has ended...
		else
		{
			m_isJumping = false;
			m_isFalling = true;
		}

	}//end if jumping

	//Apply gravity
	if (m_isFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	//update rect position for all body parts
	FloatRect r = getPosition();

	//feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;


	//Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * 0.3f);
	m_Head.width = r.width;
	m_Head.height = 1;

	//Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * 0.35;
	m_Right.width = 1;
	m_Right.height = r.height * 0.3;

	//Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * 0.35;
	m_Left.width = 1;
	m_Left.height = r.height * 0.3;


	//move sprite into position
	m_Sprite.setPosition(m_Position);
}//end update

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
		);
}

FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}
FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}

void PlayableCharacter::stopFalling(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_isFalling = false;
}

void PlayableCharacter::stopRight(float position)
{
	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);

}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump()
{
	m_isJumping = false;
	m_isFalling = true;
}