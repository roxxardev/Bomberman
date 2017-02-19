#pragma once
#include "Sprite.h"

class CBomba
{
public:
	CBomba(SDL_Renderer* Dany_Renderer, SDL_Texture* dany_obrazek);
	~CBomba();

	void Postaw_bombe(int i, int j);
	void Rysuj_bombe();
	CSprite* Dej_Sprite() { return Bomba; }
	int Dej_czas() { return czas; }
	void Ustaw_czas(int dany_czas) { czas = dany_czas; }
	void Ustaw_k(int i) { k = i; }
	int Dej_k() { return k; }
	void Ustaw_poza_bomba(bool i) { poza_bomba = i; }
	bool Dej_poza_bomba() { return poza_bomba; }

private:

	SDL_Renderer* Renderer;
	CSprite* Bomba;

	SDL_Texture* Obrazek_Bomby;

	int czas;
	bool poza_bomba;
	int k;
};

