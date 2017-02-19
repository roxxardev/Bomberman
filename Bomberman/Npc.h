#pragma once
#include "Bomba.h"

class CNpc
{
public:
	CNpc(SDL_Renderer* dany_renderer, int** dane_Kafelki2, int dana_pozycja_x, int dana_pozycja_y, SDL_Texture* dany_obrazek, vector<CBomba*>* dane_bomby);
	~CNpc();


	void Rysuj();
	void Odswiez_NPC();
	CSprite* Dej_Sprajta() { return NPC; }

private:
	SDL_Texture* Obrazek_NPC;
	CSprite* NPC;
	SDL_Renderer* Renderer;
	vector<CBomba*>* Bomby;

	int** Kafelki;
	int poz_x_postaci;
	int poz_y_postaci;

	enum kierunek
	{
		gora,
		dol,
		lewo,
		prawo,
		stoj
	};
	int kierunek;
	int kierunek_temp;
};

