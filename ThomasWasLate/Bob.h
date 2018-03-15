#pragma once
#include "PlayableCharacter.h"

class Bob : public PlayableCharacter
{
public:
	Bob();

	//this will implement the pure virtual function from playable character
	bool virtual handleInput();


}; //end class