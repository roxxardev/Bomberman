#pragma once

#include "Biblioteki.h"

class CSDL_Inicjalizacja
{
private:
	SDL_Window* Okno;
	SDL_Renderer* Renderer;
	SDL_Texture* Tekstura;
	SDL_Event* Event;

public:
	CSDL_Inicjalizacja(int szerokosc_okna, int wysokosc_okna, bool* gra_trwa);
	~CSDL_Inicjalizacja();

	void Czyszczenie_Renderera();
	void Odswiezanie();
	SDL_Renderer* Daj_Renderer() { return Renderer; }
	SDL_Event* Dej_Event(){ return Event; }
	void PollEvent();
};

