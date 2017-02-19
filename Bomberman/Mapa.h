#pragma once
#include "Wybuch.h"
#include "Npc.h"

class CMapa
{
public:
	CMapa(SDL_Renderer* Podany_Renderer, int wiersze, int kolumny);
	~CMapa();

	void RysujMape();
	CSprite*** Dej_Kafelki() { return Kafelki; }
	CSprite** Dej_Kafelki_z_kolizja() { return Kafelki_z_kolizja; }
	int Dej_licznik() { return licznik; }
	void Postaw_bombe(int i, int j);
	void Postaw_wybuch(int i, int j);
	void OdswiezMape();
	void Wczytaj_obrazki();
	vector<CNpc*> Dej_NPC() { return NPC; }
	void Sprawdz_kolizje_wybuch_blok();
	void Sprawdz_kolizje_wybuch_bomba();
	void Sprawdz_kolizje_wybuch_npc();
	vector<CBomba*> Dej_Bomby() { return Bomby; }
	vector<CWybuch*> Dej_Wybuchy() { return Wybuchy; }
private:
	enum Bloki
	{
		Solidny_blok,
		Dywan,
		Niesolidny_blok
	};

	SDL_Texture* Chodnik;
	SDL_Texture* Blok_solidny;
	SDL_Texture* Blok_niesolidny;
	SDL_Texture* Obrazek_Bomby;
	SDL_Texture* Obrazek_Wybuchu;
	SDL_Texture* Obrazek_NPC;

	SDL_Renderer* Renderer;

	vector<CBomba*> Bomby;
	vector<CWybuch*> Wybuchy;

	CSprite** Kafelki_z_kolizja;
	CSprite*** Kafelki;
	vector<CNpc*> NPC;


	int** Kafelki2;
	int licznik;
	int wiersze;
	int kolumny;
};