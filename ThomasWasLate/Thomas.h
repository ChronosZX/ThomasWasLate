#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	Thomas();

	//this will implement the pure virtual function from playable character
	bool virtual handleInput();


}; //end class
