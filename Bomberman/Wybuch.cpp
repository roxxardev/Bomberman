#include "Wybuch.h"

CWybuch::CWybuch(SDL_Renderer* Dany_Renderer, SDL_Texture* dany_obrazek)
{
	Renderer = Dany_Renderer;

	Obrazek_wybuchu = dany_obrazek;
	czas = SDL_GetTicks();
}


CWybuch::~CWybuch()
{
	delete Wybuch;
}

void CWybuch::Rysuj_wybuch()
{
	Wybuch->Rysuj();
}
void CWybuch::Postaw_wybuch(int i, int j)
{
	Wybuch = new CSprite(Renderer, i, j, 48, 48, Obrazek_wybuchu);
	Wybuch->Ustaw_kolizje(i, j, 64, 64);
}

