#include "Bomba.h"


CBomba::CBomba(SDL_Renderer* Dany_Renderer, SDL_Texture* dany_obrazek)
{
	Renderer = Dany_Renderer;

	Obrazek_Bomby = dany_obrazek;
	czas = SDL_GetTicks();
	poza_bomba = false;
	k = 0;
}


CBomba::~CBomba()
{
	delete Bomba;
}

void CBomba::Rysuj_bombe()
{
	Bomba->Rysuj();
}
void CBomba::Postaw_bombe(int i, int j)
{
	Bomba = new CSprite(Renderer, i * 64 + 8, j * 64 + 8, 48, 48, Obrazek_Bomby);
	Bomba->Ustaw_kolizje(i + 8, j + 8, 48, 48);
}

