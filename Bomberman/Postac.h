#pragma once
#include "SDL_Inicjalizacja.h"
#include "Mapa.h"

class CPostac
{
private:
	CSprite* Postac;
	SDL_Texture* Tekstura_Postaci;
	CSDL_Inicjalizacja* SDLIni;
	CMapa* Mapa;
	SDL_Texture* Obrazek_gameover;
	CSprite* GameOver;

	unsigned czas;
	unsigned czas_infa;

	bool ruch_prawo;
	bool ruch_lewo;
	bool ruch_gora;
	bool ruch_dol;
	bool animacja_trwa;

	int poz_x_postaci;
	int poz_y_postaci;
	bool poza_bomba;
	int k;
	bool ruch;
	bool* postac_zyje;
	bool aaa;
	SDL_Rect rekt_ekranu;

public:
	CPostac(CSDL_Inicjalizacja* Dany_SDLIni, CMapa* Dana_Mapa, bool* dana_postac_zyje);

	void Ustaw_wycinek();
	void Rysuj();
	void Obsluz_klawiature();
	void Wyswietl_info(unsigned czestotliwosc);
	void Obsluz_klawisze();
	void Sprawdz_kolizje_z_npc();
	void Obsluz_ruch();
	void Obsluz_ruch_strony_poziomo(int pixel, int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad, bool krawedz);
	void Obsluz_ruch_strony_pionowo(int pixel, int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad, bool krawedz);

	bool Sprawdz_kolizje(SDL_Rect Kolider, SDL_Rect Kolidujacy);
	void Wczytaj_stworz_gameover();
	CSprite* Dej_Gejmower() { return GameOver; }
	~CPostac();
};

