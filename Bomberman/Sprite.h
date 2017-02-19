#pragma once
#include "Biblioteki.h"

class CSprite
{
private:
	int wysokosc_obrazka;
	int szerokosc_obrazka;
	int delay_animacji;
	int aktualna_klatka;
	int ilosc_klatek_X;
	int ilosc_klatek_Y;

	SDL_Rect Wycinek;
	SDL_Rect Prostokat;
	SDL_Rect Kolizja;
	SDL_Texture* Obrazek;
	SDL_Texture* Obrazek_kolizja;
	SDL_Renderer* Renderer;



public:
	CSprite(SDL_Renderer* Dany_Renderer, int x, int y, int w, int h, SDL_Texture* Dany_Obrazek);
	~CSprite();

	void Ustaw_X(int x);
	void Ustaw_Y(int y);
	int Daj_X(){ return Prostokat.x; }
	int Daj_Y(){ return Prostokat.y; }

	void Ustaw_animacje(int dana_ilosc_klatek_X, int dana_ilosc_klatek_Y);
	void Ustaw_prostokat(int x, int y);
	void Ustaw_wycinek(int x, int y, int w, int h);
	void Nakurwiaj_animacje(int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad);
	void Rysuj();
	void Rysuj_Kolizje();
	void Ustaw_kolizje(int x, int y, int w, int h);
	int Daj_X_Kolizji(){ return Kolizja.x; }
	int Daj_Y_Kolizji(){ return Kolizja.y; }
	void Ustaw_X_Kolizji(int x);
	void Ustaw_Y_Kolizji(int y);
	void Ustaw_Obrazek(SDL_Texture* Obrazek);

	SDL_Rect Dej_wycinek(){ return Wycinek; }
	SDL_Rect Dej_prostokat() { return Prostokat; }
	SDL_Rect Dej_Kolizje() { return Kolizja; }
	bool Sprawdz_kolizje(SDL_Rect Kolidujacy);
};

