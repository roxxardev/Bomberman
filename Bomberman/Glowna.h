#pragma once
#include "SDL_Inicjalizacja.h"
#include "Postac.h"
#define FPS 60

class CGlowna
{
private:
	int wysokosc_okna;
	int szerokosc_okna;

	bool gra_trwa;
	bool postac_zyje;

	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;


	CSDL_Inicjalizacja* SDLIni;
	CMapa* Mapa;
	CPostac* Glowna_Postac;

public:
	CGlowna(int dana_szerokosc_ekranu, int dana_wysokosc_ekranu);
	~CGlowna();
	void PetlaGlowna();
	void FPSY();
	void Obsluz_deadscreen();
};

