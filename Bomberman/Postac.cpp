#include "Postac.h"

CPostac::CPostac(CSDL_Inicjalizacja* Dany_SDLIni, CMapa* Dana_Mapa, bool* dana_postac_zyje)
{
	SDLIni = Dany_SDLIni;
	Mapa = Dana_Mapa;
	Tekstura_Postaci = IMG_LoadTexture(SDLIni->Daj_Renderer(), "sprajty/Postac.png");
	Postac = new CSprite(SDLIni->Daj_Renderer(), 0, 0, 64, 128, Tekstura_Postaci);

	Postac->Ustaw_animacje(8, 4);
	Postac->Ustaw_kolizje(14, 128 - 32, 37, 26);

	ruch_prawo = false;
	ruch_lewo = false;
	ruch_gora = false;
	ruch_dol = false;
	animacja_trwa = false;

	czas = 0;
	czas_infa = 0;
	ruch = false;
	k = 0;
	postac_zyje = dana_postac_zyje;
	rekt_ekranu.x = 0;
	rekt_ekranu.y = 64;
	rekt_ekranu.w = 576;
	rekt_ekranu.h = 640;
	Obrazek_gameover = NULL;

	poz_x_postaci = div(Postac->Daj_X() + 32, 64).quot;
	poz_y_postaci = div(Postac->Daj_Y() + 32, 64).quot;
}


CPostac::~CPostac()
{
	delete Postac;
	SDL_DestroyTexture(Obrazek_gameover);
	SDL_DestroyTexture(Tekstura_Postaci);
}

void CPostac::Ustaw_wycinek()
{
	Postac->Ustaw_wycinek(0, 0, 64, 128);
}

void CPostac::Rysuj()
{
	Postac->Rysuj();
	//Postac->Rysuj_Kolizje();
}

void CPostac::Obsluz_klawiature()
{
	Obsluz_klawisze();
	Sprawdz_kolizje_z_npc();
	Obsluz_ruch();
}
void CPostac::Obsluz_ruch()
{
	if (ruch)
		//if (czas + 1 < SDL_GetTicks() && ruch)
	{
		aaa = false;
		poz_x_postaci = div(Postac->Daj_X() + 32, 64).quot;
		poz_y_postaci = div(Postac->Daj_Y() + 32, 64).quot;

		if (ruch_gora)
		{
			Obsluz_ruch_strony_pionowo(-1, 0, 7, 100, 3, (Postac->Daj_Y_Kolizji() <= 64));
		}
		if (ruch_dol)
		{
			Obsluz_ruch_strony_pionowo(1, 0, 7, 100, 0, (Postac->Daj_Y_Kolizji() >= 640 - Postac->Dej_Kolizje().h));
		}
		if (ruch_lewo)
		{
			Obsluz_ruch_strony_poziomo(-1, 0, 7, 100, 2, (Postac->Daj_X_Kolizji() <= 0));
		}
		if (ruch_prawo)
		{
			Obsluz_ruch_strony_poziomo(1, 0, 7, 100, 1, (Postac->Daj_X_Kolizji() >= 576 - Postac->Dej_Kolizje().w));
		}
		//czas = SDL_GetTicks();
	}
}
void CPostac::Obsluz_ruch_strony_pionowo(int pixel, int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad, bool krawedz)
{
	Postac->Ustaw_Y(Postac->Daj_Y() + pixel);
	Postac->Ustaw_Y_Kolizji(Postac->Daj_Y_Kolizji() + pixel);

	aaa = krawedz;
	for (int i = 0; i < Mapa->Dej_licznik(); i++)
	if (!(Sprawdz_kolizje(Postac->Dej_Kolizje(), Mapa->Dej_Kafelki_z_kolizja()[i]->Dej_Kolizje())))
	{
		aaa = true;
		i = Mapa->Dej_licznik();
	}


	for (int i = 0; i < Mapa->Dej_Bomby().size(); i++)
	{
		if (Postac->Sprawdz_kolizje(Mapa->Dej_Bomby()[i]->Dej_Sprite()->Dej_Kolizje()))
		{
			if (Mapa->Dej_Bomby()[i]->Dej_poza_bomba())
				aaa = true;
		}
		else
		if (Mapa->Dej_Bomby()[i]->Dej_k() == 0)
		{
			Mapa->Dej_Bomby()[i]->Ustaw_poza_bomba(true);
			Mapa->Dej_Bomby()[i]->Ustaw_k(1);
		}
	}


	if (!aaa)
	{
		Postac->Nakurwiaj_animacje(poczatkowa_klatka, koncowa_klatka, predkosc, rzad);
	}
	else
	{
		Postac->Ustaw_Y(Postac->Daj_Y() - pixel);
		Postac->Ustaw_Y_Kolizji(Postac->Daj_Y_Kolizji() - pixel);
	}

}
void CPostac::Obsluz_ruch_strony_poziomo(int pixel, int poczatkowa_klatka, int koncowa_klatka, int predkosc, int rzad, bool krawedz)
{
	Postac->Ustaw_X(Postac->Daj_X() + pixel);
	Postac->Ustaw_X_Kolizji(Postac->Daj_X_Kolizji() + pixel);
	aaa = krawedz;

	for (int i = 0; i < Mapa->Dej_licznik(); i++)
	if (!(Sprawdz_kolizje(Postac->Dej_Kolizje(), Mapa->Dej_Kafelki_z_kolizja()[i]->Dej_Kolizje())))
	{
		aaa = true;
		i = Mapa->Dej_licznik();
	}
	for (int i = 0; i < Mapa->Dej_Bomby().size(); i++)
	{
		if (Postac->Sprawdz_kolizje(Mapa->Dej_Bomby()[i]->Dej_Sprite()->Dej_Kolizje()))
		{
			if (Mapa->Dej_Bomby()[i]->Dej_poza_bomba())
				aaa = true;
		}
		else
		if (Mapa->Dej_Bomby()[i]->Dej_k() == 0)
		{
			Mapa->Dej_Bomby()[i]->Ustaw_poza_bomba(true);
			Mapa->Dej_Bomby()[i]->Ustaw_k(1);
		}
	}
	if (!aaa)

	{
		Postac->Nakurwiaj_animacje(poczatkowa_klatka, koncowa_klatka, predkosc, rzad);
	}
	else
	{
		Postac->Ustaw_X(Postac->Daj_X() - pixel);
		Postac->Ustaw_X_Kolizji(Postac->Daj_X_Kolizji() - pixel);
	}

}
void CPostac::Obsluz_klawisze()
{
	switch (SDLIni->Dej_Event()->type)
	{
	case SDL_KEYDOWN:
		switch (SDLIni->Dej_Event()->key.keysym.sym)
		{
		case SDLK_w:
			ruch_gora = true;
			ruch = true;
			break;

		case SDLK_s:
			ruch_dol = true;
			ruch = true;
			break;

		case SDLK_a:
			ruch_lewo = true;
			ruch = true;
			break;

		case SDLK_d:
			ruch_prawo = true;
			ruch = true;
			break;
		case SDLK_SPACE:
			Mapa->Postaw_bombe(poz_x_postaci, poz_y_postaci);

			break;
		}
		break;

	case SDL_KEYUP:
		switch (SDLIni->Dej_Event()->key.keysym.sym)
		{
		case SDLK_w:
			ruch_gora = false;
			if (!ruch_dol && !ruch_lewo && !ruch_prawo)
			{
				Postac->Nakurwiaj_animacje(0, 0, 100, 3);
				ruch = false;
			}
			break;

		case SDLK_s:
			ruch_dol = false;
			if (!ruch_gora && !ruch_lewo && !ruch_prawo)
			{
				Postac->Nakurwiaj_animacje(0, 0, 100, 0);
				ruch = false;
			}
			break;

		case SDLK_a:
			ruch_lewo = false;
			if (!ruch_dol && !ruch_gora && !ruch_prawo)
			{
				Postac->Nakurwiaj_animacje(0, 0, 100, 2);
				ruch = false;
			}
			break;

		case SDLK_d:
			ruch_prawo = false;
			if (!ruch_dol && !ruch_lewo && !ruch_gora)
			{
				Postac->Nakurwiaj_animacje(0, 0, 100, 1);
				ruch = false;
			}
			break;


		default:

			break;
		}
		break;

	default:

		break;
	}
}
void CPostac::Sprawdz_kolizje_z_npc()
{
	for (int i = 0; i < Mapa->Dej_NPC().size(); i++)
	if (!Sprawdz_kolizje(Postac->Dej_Kolizje(), Mapa->Dej_NPC()[i]->Dej_Sprajta()->Dej_Kolizje()))
	{
		*postac_zyje = false;
		if (Obrazek_gameover == NULL)
			Wczytaj_stworz_gameover();
		GameOver->Rysuj();
	}
	for (int i = 0; i < Mapa->Dej_Wybuchy().size(); i++)
	if (!Sprawdz_kolizje(Postac->Dej_Kolizje(), Mapa->Dej_Wybuchy()[i]->Dej_Sprite()->Dej_Kolizje()))
	{
		*postac_zyje = false;
		if (Obrazek_gameover == NULL)
			Wczytaj_stworz_gameover();
		GameOver->Rysuj();
	}

}
void CPostac::Wczytaj_stworz_gameover()
{
	Obrazek_gameover = IMG_LoadTexture(SDLIni->Daj_Renderer(), "sprajty/gameover.png");
	if (Obrazek_gameover == NULL)
		cout << "Nie wczytano gameover" << endl;
	GameOver = new CSprite(SDLIni->Daj_Renderer(), 150, 300, 400, 185, Obrazek_gameover);

}
void CPostac::Wyswietl_info(unsigned czestotliwosc)
{
	if (czas_infa + czestotliwosc < SDL_GetTicks())
	{
		cout << endl << "(" << poz_x_postaci << "," << poz_y_postaci << ")";
		czas_infa = SDL_GetTicks();
	}
}

bool CPostac::Sprawdz_kolizje(SDL_Rect Kolider, SDL_Rect Kolidujacy)
{
	return((Kolider.x + Kolider.w <= Kolidujacy.x || Kolider.y + Kolider.h <= Kolidujacy.y || Kolider.x >= Kolidujacy.x + Kolidujacy.w || Kolider.y >= Kolidujacy.y + Kolidujacy.h));
}
