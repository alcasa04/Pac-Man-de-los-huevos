#include "PacManError.h"



PacManError::PacManError(string error) : logic_error(error)
{
}

void PacManError::what(){}


PacManError::~PacManError()
{
}
