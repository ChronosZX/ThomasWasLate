#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
	//these variables are shared with subclass children
protected:
	Sprite m_Sprite;
	
	//how long does a jump last
	float m_JumpDuration;
	
	//is the character jumping or falling?
	bool m_isJumping;
	bool m_isFalling;

	//which direction is the character moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	//How long has this jump lasted for
	float m_TimeThisJump;

	//Has the player just initiated a jump?
	bool m_JustJumped = false;

//these variables can only be edited and viewed by THIS class, not subclasses
private:

	//What is Gravity?
	float m_Gravity;

	//How fast is the character?
	float m_Speed = 400;

	//Position of Player?
	Vector2f m_Position;

	//where are the character's body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	Texture m_Texture;

//public functions available to EVERYTHING in this program
public:
	void spawn(Vector2f startPosition, float gravity);

	//This is a pure, virtual function
	//This means this class becomes an abstract class
	//Meaning we cannot create an instant of this class, only subclasses
	//Sub Classes MUST implement this function in order to create instances
	bool virtual handleInput() = 0;

	//WHERE IS THE PLAYER?!
	FloatRect getPosition();

	//a rectangle representing the position of different parts of the spirte
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getLeft();
	FloatRect getRight();

	//Get a copy of the sprite
	Sprite getSprite();

	//Prevent the character from moving
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	//Where is the center of the character
	Vector2f getCenter();

	//we will call this function once every frame
	void update(float elapsedTime);

}; //end PlayableCharacter class