#pragma once

#include "Sprite.h"


class CWybuch
{
public:
	CWybuch(SDL_Renderer* Dany_Renderer, SDL_Texture* dany_obrazek);
	~CWybuch();

	void Postaw_wybuch(int i, int j);
	void Rysuj_wybuch();
	CSprite* Dej_Sprite() { return Wybuch; }
	int Dej_czas() { return czas; }

private:

	int dlugosc_plomienia;

	SDL_Renderer* Renderer;
	CSprite* Wybuch;

	SDL_Texture* Obrazek_wybuchu;

	int czas;
};

