#include "Glowna.h"

CGlowna::CGlowna(int dana_szerokosc_ekranu, int dana_wysokosc_ekranu)
{
	szerokosc_okna = dana_szerokosc_ekranu;
	wysokosc_okna = dana_wysokosc_ekranu;
	gra_trwa = true;
	postac_zyje = true;
	SDLIni = new CSDL_Inicjalizacja(szerokosc_okna, wysokosc_okna, &gra_trwa);
	Mapa = new CMapa(SDLIni->Daj_Renderer(), wysokosc_okna / 64, szerokosc_okna / 64);
	Glowna_Postac = new CPostac(SDLIni, Mapa, &postac_zyje);

	waittime = 1000.0f / FPS;
	framestarttime = 0;

}

CGlowna::~CGlowna()
{
	delete SDLIni;
	delete Glowna_Postac;
	delete Mapa;
}

void CGlowna::PetlaGlowna()
{
	Glowna_Postac->Ustaw_wycinek();
	while (gra_trwa && SDLIni->Dej_Event()->type != SDL_QUIT)
	{
		SDLIni->PollEvent();
		SDLIni->Czyszczenie_Renderera();

		Mapa->RysujMape();
		Glowna_Postac->Rysuj();
		if (!postac_zyje)
		{
			Glowna_Postac->Dej_Gejmower()->Rysuj();
			Obsluz_deadscreen();
		}

		SDLIni->Odswiezanie();
		
		if (postac_zyje)
		{
			Glowna_Postac->Obsluz_klawiature();
			if (postac_zyje)
				Glowna_Postac->Obsluz_klawiature();
		}
		Mapa->OdswiezMape();
	}
}

void CGlowna::FPSY()
{
	delaytime = waittime - (SDL_GetTicks() - framestarttime);
	if (delaytime > 0)
		SDL_Delay((Uint32)delaytime);
	framestarttime = SDL_GetTicks();
}
void CGlowna::Obsluz_deadscreen()
{
	switch (SDLIni->Dej_Event()->type)
	{
	case SDL_KEYDOWN:
		switch (SDLIni->Dej_Event()->key.keysym.sym)
		{
		case SDLK_z:
			if (!postac_zyje)
			{
				delete Mapa;
				delete Glowna_Postac;
				postac_zyje = true;
				Mapa = new CMapa(SDLIni->Daj_Renderer(), wysokosc_okna / 64, szerokosc_okna / 64);
				Glowna_Postac = new CPostac(SDLIni, Mapa, &postac_zyje);
				Glowna_Postac->Ustaw_wycinek();
			}
			break;
		}
	}
}
