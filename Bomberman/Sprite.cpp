#include "Sprite.h"


CSprite::CSprite(SDL_Renderer* Dany_Renderer, int x, int y, int w, int h, SDL_Texture* Dany_Obrazek)
{
	Renderer = Dany_Renderer;

	Obrazek = Dany_Obrazek;

	/*Obrazek_kolizja = NULL;
	Obrazek_kolizja = IMG_LoadTexture(Renderer,"sprajty/Kolizje.png");

	if (Obrazek_kolizja == NULL)
	cout << " Obrazek kolizji: " << SDL_GetError();
	*/
	Prostokat.x = x;
	Prostokat.y = y;
	Prostokat.w = w;
	Prostokat.h = h;


	SDL_QueryTexture(Obrazek, NULL, NULL, &szerokosc_obrazka, &wysokosc_obrazka);

	Wycinek.x = 0;
	Wycinek.y = 0;
	Wycinek.w = szerokosc_obrazka;
	Wycinek.h = wysokosc_obrazka;

	aktualna_klatka = 0;
	ilosc_klatek_X = 0;
	ilosc_klatek_Y = 0;
	delay_animacji = 0;
}


CSprite::~CSprite()
{

}

void CSprite::Rysuj()
{
	SDL_RenderCopy(Renderer, Obrazek, &Wycinek, &Prostokat);
}

void CSprite::Rysuj_Kolizje()
{
	SDL_RenderCopy(Renderer, Obrazek_kolizja, 0, &Kolizja);
}

void CSprite::Ustaw_X(int x)
{
	Prostokat.x = x;
}

void CSprite::Ustaw_Y(int y)
{
	Prostokat.y = y;
}

void CSprite::Ustaw_animacje(int dana_ilosc_klatek_X, int dana_ilosc_klatek_Y)
{
	ilosc_klatek_X = dana_ilosc_klatek_X;
	ilosc_klatek_Y = dana_ilosc_klatek_Y;
}

void CSprite::Ustaw_prostokat(int x, int y)
{
	Prostokat.x = x;
	Prostokat.y = y;
}

void CSprite::Ustaw_wycinek(int x, int y, int w, int h)
{
	Wycinek.x = x;
	Wycinek.y = y;
	Wycinek.w = w;
	Wycinek.h = h;
}
void CSprite::Nakurwiaj_animacje(int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad)
{
	if (delay_animacji + predkosc < SDL_GetTicks())
	{
		if (aktualna_klatka >= koncowa_klatka)
			aktualna_klatka = poczatkowa_klatka;
		else
			aktualna_klatka++;

		Wycinek.x = aktualna_klatka*(szerokosc_obrazka / ilosc_klatek_X);
		Wycinek.y = rzad*(wysokosc_obrazka / ilosc_klatek_Y);
		Wycinek.w = szerokosc_obrazka / ilosc_klatek_X;
		Wycinek.h = wysokosc_obrazka / ilosc_klatek_Y;

		delay_animacji = SDL_GetTicks();
	}
}

void CSprite::Ustaw_kolizje(int x, int y, int w, int h)
{
	Kolizja.x = x;
	Kolizja.y = y;
	Kolizja.w = w;
	Kolizja.h = h;
}

void CSprite::Ustaw_X_Kolizji(int x)
{
	Kolizja.x = x;
}

void CSprite::Ustaw_Y_Kolizji(int y)
{
	Kolizja.y = y;
}
void CSprite::Ustaw_Obrazek(SDL_Texture* Obrazek)
{
	this->Obrazek = Obrazek;
	SDL_QueryTexture(Obrazek, NULL, NULL, &szerokosc_obrazka, &wysokosc_obrazka);

	Wycinek.x = 0;
	Wycinek.y = 0;
	Wycinek.w = szerokosc_obrazka;
	Wycinek.h = wysokosc_obrazka;
}
bool CSprite::Sprawdz_kolizje(SDL_Rect Kolidujacy)
{
	return!((Kolizja.x + Kolizja.w <= Kolidujacy.x || Kolizja.y + Kolizja.h <= Kolidujacy.y || Kolizja.x >= Kolidujacy.x + Kolidujacy.w || Kolizja.y >= Kolidujacy.y + Kolidujacy.h));
}