#pragma once
#include<exception>
#include<iostream>

using namespace std;

class PacManError: public logic_error
{
public:
	PacManError(string error);
	~PacManError();
	virtual void what();
	
};

