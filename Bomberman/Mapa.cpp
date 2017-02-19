#include "Mapa.h"


CMapa::CMapa(SDL_Renderer* Podany_Renderer, int podane_wiersze, int podane_kolumny)
{
	wiersze = podane_wiersze - 1;
	kolumny = podane_kolumny;
	Renderer = Podany_Renderer;


	Wczytaj_obrazki();

	Kafelki = new CSprite**[9];
	for (int i = 0; i < 9; i++)
		Kafelki[i] = new CSprite*[9];

	Kafelki2 = new int*[9];
	for (int i = 0; i < 9; i++)
		Kafelki2[i] = new int[9];



	int Kafelki3[9][9] = {
		/*{ 1, 1, 2, 2, 2, 2, 2, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 2, 1, 2, 2, 2, 1, 1, 2, 2 },
		{ 1, 0, 1, 0, 1, 0, 2, 0, 1 },
		{ 2, 1, 2, 1, 2, 1, 2, 1, 2 },
		{ 2, 0, 2, 0, 2, 0, 1, 0, 1 },
		{ 2, 1, 1, 2, 2, 1, 1, 1, 2 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1 },
		{ 1, 1, 2, 1, 1, 2, 2, 1, 1 }*/
		{ 1, 1, 1, 1, 1, 1, 2, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 1, 2, 2, 1, 1, 1, 2, 2 },
		{ 1, 0, 1, 0, 1, 0, 2, 0, 1 },
		{ 2, 1, 2, 1, 1, 1, 2, 1, 2 },
		{ 2, 0, 2, 0, 1, 0, 1, 0, 1 },
		{ 2, 1, 1, 2, 1, 1, 1, 1, 1 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1 },
		{ 1, 1, 1, 1, 1, 2, 2, 1, 1 }
	};

	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j < kolumny; j++)
		{
			Kafelki2[i][j] = Kafelki3[i][j];
			//	cout << Kafelki2[i][j] << " ";
		}
		//cout << endl;
	}


	licznik = 0;
	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j < kolumny; j++)
		{
			if (Kafelki2[i][j] == Dywan)
			{
				Kafelki[i][j] = new CSprite(Renderer, j * 64, (i + 1) * 64, 64, 64, Chodnik);
			}
			else if (Kafelki2[i][j] == Solidny_blok)
			{
				Kafelki[i][j] = new CSprite(Renderer, j * 64, (i + 1) * 64, 64, 64, Blok_solidny);
				Kafelki[i][j]->Ustaw_kolizje(j * 64, (i + 1) * 64, 64, 64);
				licznik++;
			}
			else
			{
				Kafelki[i][j] = new CSprite(Renderer, j * 64, (i + 1) * 64, 64, 64, Blok_niesolidny);
				Kafelki[i][j]->Ustaw_kolizje(j * 64, (i + 1) * 64, 64, 64);
				licznik++;
			}
		}
	}

	Kafelki_z_kolizja = new CSprite*[licznik];
	licznik = 0;
	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j < kolumny; j++)
		{
			if (Kafelki2[i][j] == Solidny_blok)
			{
				Kafelki_z_kolizja[licznik] = Kafelki[i][j];
				licznik++;
			}
			else if (Kafelki2[i][j] == Niesolidny_blok)
			{
				Kafelki_z_kolizja[licznik] = Kafelki[i][j];
				licznik++;
			}
		}
	}
	for (int i = 0; i < 15; i++)
	{

		NPC.push_back(new CNpc(Renderer, Kafelki2, 4, 4, Obrazek_NPC, &Bomby));
	}

}

CMapa::~CMapa()
{
	SDL_DestroyTexture(Chodnik);
	SDL_DestroyTexture(Blok_solidny);
	SDL_DestroyTexture(Blok_niesolidny);
	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j < kolumny; j++)
		{
			delete Kafelki[i][j];
		}
	}
	delete[] Kafelki;
	delete[] Kafelki2;
	SDL_DestroyTexture(Obrazek_Bomby);
	SDL_DestroyTexture(Obrazek_Wybuchu);
	for (vector<CNpc*>::iterator i = NPC.begin(); i < NPC.end(); i++)
		delete (*i);
	SDL_DestroyTexture(Obrazek_NPC);
}

void CMapa::Wczytaj_obrazki()
{
	Chodnik = NULL;
	Blok_solidny = NULL;
	Blok_niesolidny = NULL;
	Chodnik = IMG_LoadTexture(Renderer, "sprajty/BackgroundTile.png");
	Blok_solidny = IMG_LoadTexture(Renderer, "sprajty/SolidBlock.png");
	Blok_niesolidny = IMG_LoadTexture(Renderer, "sprajty/ExplodableBlock.png");

	if (Chodnik == NULL)
	{
		cout << "Nie wczytano chodnika ERROR KOD: " << SDL_GetError();
	}

	if (Blok_solidny == NULL)
	{
		cout << "Nie wczytano blok_solidny ERROR KOD: " << SDL_GetError();
	}

	if (Blok_niesolidny == NULL)
	{
		cout << "Nie wczytano blok_niesolidny ERROR KOD: " << SDL_GetError();
	}

	Obrazek_Bomby = NULL;
	Obrazek_Bomby = IMG_LoadTexture(Renderer, "sprajty/Bomba.png");
	if (Obrazek_Bomby == NULL)
		cout << "obrazek bomby nie zostal wczytany bo cwel " << SDL_GetError();
	Obrazek_Wybuchu = NULL;

	Obrazek_Wybuchu = IMG_LoadTexture(Renderer, "sprajty/wybuch.png");
	if (Obrazek_Wybuchu == NULL)
		cout << "obrazek wybuchu nie zostal wczytany bo cwel " << SDL_GetError();
	Obrazek_NPC = NULL;
	Obrazek_NPC = IMG_LoadTexture(Renderer, "sprajty/Creep.png");
	if (Obrazek_NPC == NULL)
		cout << "obrazek NPC nie zostal wczytany bo cwel " << SDL_GetError();
}
void CMapa::RysujMape()
{


	for (int i = 0; i < wiersze; i++)
	{
		for (int j = 0; j < kolumny; j++)
		{
			Kafelki[i][j]->Rysuj();
			/*if (Kafelki2[i][j] == Solidny_blok || Kafelki2[i][j] == Niesolidny_blok)
			{
			Kafelki[i][j]->Ustaw_kolizje(j * 64, (i + 1) * 64, 64, 64);
			//	Kafelki[i][j]->Rysuj_Kolizje();
			}*/
		}
	}
	for (int i = 0; i < Bomby.size(); i++)
	{
		Bomby[i]->Dej_Sprite()->Nakurwiaj_animacje(0, 2, 100, 0);
		Bomby[i]->Rysuj_bombe();
		//Bomby[i]->Dej_Sprite()->Rysuj_Kolizje();
	}
	for (int i = 0; i < Wybuchy.size(); i++)
	{
		Wybuchy[i]->Dej_Sprite()->Nakurwiaj_animacje(0, 4, 100, 0);
		Wybuchy[i]->Rysuj_wybuch();
	}
	for (int i = 0; i < NPC.size(); i++)
	{
		NPC[i]->Rysuj();
		//NPC[i]->Dej_Sprajta()->Rysuj_Kolizje();
	}

}
void CMapa::Postaw_bombe(int i, int j)
{
	int size = Bomby.size();
	if (size <  3)
	{
		if (size == 0)
		{

			Bomby.push_back(new CBomba(Renderer, Obrazek_Bomby));
			Bomby.back()->Postaw_bombe(i, j + 1);
			Bomby.back()->Dej_Sprite()->Ustaw_animacje(3, 1);
			Bomby.back()->Dej_Sprite()->Ustaw_kolizje(i * 64 + 8, (j + 1) * 64 + 8, 48, 48);
		}
		else
		{


			if (Bomby.back()->Dej_Sprite()->Daj_X() / 64 != i || Bomby.back()->Dej_Sprite()->Daj_Y() / 64 - 1 != j)
			{
				Bomby.push_back(new CBomba(Renderer, Obrazek_Bomby));
				Bomby.back()->Postaw_bombe(i, j + 1);
				Bomby.back()->Dej_Sprite()->Ustaw_animacje(3, 1);
				Bomby.back()->Dej_Sprite()->Ustaw_kolizje(i * 64 + 8, (j + 1) * 64 + 8, 48, 48);
			}

		}

	}
	//cout << "Rozmiar bomb: " << Bomby.size() << endl;
}
void CMapa::Postaw_wybuch(int i, int j)
{
	Wybuchy.push_back(new CWybuch(Renderer, Obrazek_Wybuchu));
	Wybuchy.back()->Postaw_wybuch(i, j);
	Wybuchy.back()->Dej_Sprite()->Ustaw_animacje(5, 1);

}
void CMapa::OdswiezMape()
{
	for (int i = 0; i < Bomby.size(); i++)
	{
		if (Bomby[i]->Dej_czas() + 2000 < SDL_GetTicks())
		{
			int x = Bomby[i]->Dej_Sprite()->Dej_prostokat().x;
			int y = Bomby[i]->Dej_Sprite()->Dej_prostokat().y;
			Postaw_wybuch(x, y);
			if (x / 64 > 0)
			if (Kafelki2[y / 64 - 1][x / 64 - 1] != 0)
				Postaw_wybuch(x - 64, y);
			if (x / 64<8)
			if (Kafelki2[y / 64 - 1][x / 64 + 1] != 0)
				Postaw_wybuch(x + 64, y);
			if (y / 64 - 1 > 0)
			if (Kafelki2[y / 64 - 1 - 1][x / 64] != 0)
				Postaw_wybuch(x, y - 64);
			if (y / 64 - 1 < 8)
			if (Kafelki2[y / 64 - 1 + 1][x / 64] != 0)
				Postaw_wybuch(x, y + 64);






			delete Bomby[i];
			Bomby.erase(Bomby.begin() + i);
			Sprawdz_kolizje_wybuch_blok();
			i--;

		}
	}
	Sprawdz_kolizje_wybuch_bomba();
	Sprawdz_kolizje_wybuch_npc();
	for (int i = 0; i < Wybuchy.size(); i++)
	{
		if (Wybuchy[i]->Dej_czas() + 1500 < SDL_GetTicks())
		{
			delete Wybuchy[i];
			Wybuchy.erase(Wybuchy.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < NPC.size(); i++)
		NPC[i]->Odswiez_NPC();
}
void CMapa::Sprawdz_kolizje_wybuch_blok()
{
	for (int j = 0; j < Wybuchy.size(); j++)
	{
		int y = Wybuchy[j]->Dej_Sprite()->Daj_Y() / 64 - 1;
		int x = Wybuchy[j]->Dej_Sprite()->Daj_X() / 64;
		if (Kafelki2[y][x] == 2)
		{
			delete Kafelki[y][x];
			Kafelki2[y][x] = 1;
			Kafelki[y][x] = new CSprite(Renderer, x * 64, y * 64 + 64, 64, 64, Chodnik);

		}
	}
}
void CMapa::Sprawdz_kolizje_wybuch_bomba()
{
	for (int i = 0; i < Wybuchy.size(); i++)
	{
		for (int j = 0; j < Bomby.size(); j++)
		if (Wybuchy[i]->Dej_Sprite()->Daj_X() == Bomby[j]->Dej_Sprite()->Daj_X() && Wybuchy[i]->Dej_Sprite()->Daj_Y() == Bomby[j]->Dej_Sprite()->Daj_Y())
			Bomby[j]->Ustaw_czas(0);
	}
}
void CMapa::Sprawdz_kolizje_wybuch_npc()
{
	for (int i = 0; i < NPC.size(); i++)
	for (int j = 0; j < Wybuchy.size(); j++)
	if (NPC[i]->Dej_Sprajta()->Sprawdz_kolizje(Wybuchy[j]->Dej_Sprite()->Dej_Kolizje()))
	{
		delete NPC[i];
		NPC.erase(NPC.begin() + i);
		j = Wybuchy.size();
		i--;
	}
}