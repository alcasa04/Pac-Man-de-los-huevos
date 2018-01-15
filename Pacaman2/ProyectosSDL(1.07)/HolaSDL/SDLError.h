#pragma once
#include"PacManError.h"

class SDLError : public PacManError
{
public:
	SDLError(string error);
	~SDLError();
	virtual void what();
};

