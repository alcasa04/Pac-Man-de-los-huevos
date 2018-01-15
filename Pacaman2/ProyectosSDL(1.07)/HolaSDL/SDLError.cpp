#include "SDLError.h"



SDLError::SDLError(string error):PacManError(error)
{
}


SDLError::~SDLError()
{
}

void SDLError::what(){}

/*
jerarquia de excepciones de comportamiento vacio
soo hace falta constructor que llama al constructor de la superclase
constructor con string llama a la superclase
what devuelve el string

sobre todo los errores estan en carga de archivos y en tema de sdl*/
