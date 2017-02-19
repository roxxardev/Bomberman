#include "SDL_Inicjalizacja.h"

CSDL_Inicjalizacja::CSDL_Inicjalizacja(int szerokosc_okna, int wysokosc_okna, bool* gra_trwa)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		// Tworzenie okna
		Okno = NULL;
		Okno = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc_okna, wysokosc_okna, SDL_WINDOW_SHOWN);

		if (Okno == NULL)
		{
			cout << "B³¹d inicjalizacji okna SDL." << endl;
			*gra_trwa = false;
		}
	}
	else
	{
		cout << "blad: " << SDL_GetError();
		*gra_trwa = false;
	}
	// Tworzenie renderera
	Renderer = NULL;
	Renderer = SDL_CreateRenderer(Okno, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == NULL)
	{
		cout << "B³¹d inicjalizacji renderera" << endl;
		*gra_trwa = false;
	}

	Event = new SDL_Event();
}

CSDL_Inicjalizacja::~CSDL_Inicjalizacja()
{
	SDL_DestroyWindow(Okno);
	SDL_DestroyRenderer(Renderer);
	delete Event;
}

void CSDL_Inicjalizacja::Czyszczenie_Renderera()
{
	SDL_RenderClear(Renderer);
}

void CSDL_Inicjalizacja::Odswiezanie()
{
	SDL_RenderPresent(Renderer);
}

void CSDL_Inicjalizacja::PollEvent()
{
	SDL_PollEvent(Event);
}
