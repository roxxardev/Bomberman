#include "Npc.h"


CNpc::CNpc(SDL_Renderer* dany_renderer, int** dane_Kafelki2, int dana_pozycja_x, int dana_pozycja_y, SDL_Texture* dany_obrazek, vector<CBomba*>* dane_bomby)
{
	poz_x_postaci = dana_pozycja_x;
	poz_y_postaci = dana_pozycja_y;
	Bomby = dane_bomby;
	Renderer = dany_renderer;
	Kafelki = dane_Kafelki2;
	Obrazek_NPC = dany_obrazek;
	NPC = new CSprite(Renderer, 0, 0, 64, 64, Obrazek_NPC);
	NPC->Ustaw_X(dana_pozycja_x * 64);
	NPC->Ustaw_Y(dana_pozycja_y * 64 + 64);
	NPC->Ustaw_animacje(6, 4);
	NPC->Ustaw_kolizje(dana_pozycja_x * 64 + 8, dana_pozycja_y * 64 + 8 + 64, 48, 48);
}


CNpc::~CNpc()
{
	delete NPC;
}

void CNpc::Rysuj()
{
	NPC->Rysuj();
}

void CNpc::Odswiez_NPC()
{
	kierunek_temp = kierunek;
	bool losuj = (NPC->Daj_X() % 64 == 0 && NPC->Daj_Y() % 64 == 0);


	bool ruch = false;
	if (losuj)
	{
		do
		{
			kierunek = rand() % 11;

			if (kierunek>4)
			{
				kierunek = kierunek_temp;
			}


			switch (kierunek)
			{
			case gora:

				if ((NPC->Daj_Y() - 64) / 64 > 0)
					ruch = (Kafelki[(NPC->Daj_Y() - 64) / 64 - 1][NPC->Daj_X() / 64] == 1);
				if (ruch)
				for (int i = 0; i < Bomby->size(); i++)
				{
					if (Bomby[0][i]->Dej_Sprite()->Daj_X() == NPC->Daj_X() + 8 && Bomby[0][i]->Dej_Sprite()->Daj_Y() == NPC->Daj_Y() - 64 + 8)
					{
						ruch = false;
					}
				}
				break;
			case dol:
				if ((NPC->Daj_Y() - 64) / 64 < 8)
					ruch = (Kafelki[(NPC->Daj_Y() - 64) / 64 + 1][NPC->Daj_X() / 64] == 1);
				if (ruch)
				for (int i = 0; i < Bomby->size(); i++)
				{
					if (Bomby[0][i]->Dej_Sprite()->Daj_X() == NPC->Daj_X() + 8 && Bomby[0][i]->Dej_Sprite()->Daj_Y() == NPC->Daj_Y() + 64 + 8)
					{
						ruch = false;
					}
				}
				break;
			case lewo:
				if (NPC->Daj_X() / 64 > 0)
					ruch = (Kafelki[(NPC->Daj_Y() - 64) / 64][NPC->Daj_X() / 64 - 1] == 1);
				if (ruch)
				for (int i = 0; i < Bomby->size(); i++)
				{
					if (Bomby[0][i]->Dej_Sprite()->Daj_X() == NPC->Daj_X() + 8 - 64 && Bomby[0][i]->Dej_Sprite()->Daj_Y() == NPC->Daj_Y() + 8)
					{
						ruch = false;
					}
				}
				break;
			case prawo:
				if (NPC->Daj_X() / 64 < 8)
					ruch = (Kafelki[(NPC->Daj_Y() - 64) / 64][NPC->Daj_X() / 64 + 1] == 1);
				if (ruch)
				for (int i = 0; i < Bomby->size(); i++)
				{
					if (Bomby[0][i]->Dej_Sprite()->Daj_X() == NPC->Daj_X() + 64 + 8 && Bomby[0][i]->Dej_Sprite()->Daj_Y() == NPC->Daj_Y() + 8)
					{
						ruch = false;
					}
				}
				break;

			case stoj:
				ruch = true;
				break;
			}
		} while (!ruch);



		//	cout << kierunek << endl;
	}


	switch (kierunek)
	{
	case gora:
		NPC->Ustaw_Y(NPC->Daj_Y() - 1);
		NPC->Ustaw_Y_Kolizji(NPC->Daj_Y_Kolizji() - 1);
		NPC->Nakurwiaj_animacje(0, 5, 100, 1);
		break;
	case dol:
		NPC->Ustaw_Y(NPC->Daj_Y() + 1);
		NPC->Ustaw_Y_Kolizji(NPC->Daj_Y_Kolizji() + 1);
		NPC->Nakurwiaj_animacje(0, 5, 100, 0);
		break;
	case lewo:
		NPC->Ustaw_X(NPC->Daj_X() - 1);
		NPC->Ustaw_X_Kolizji(NPC->Daj_X_Kolizji() - 1);
		NPC->Nakurwiaj_animacje(0, 5, 100, 3);
		break;
	case prawo:
		NPC->Ustaw_X(NPC->Daj_X() + 1);
		NPC->Ustaw_X_Kolizji(NPC->Daj_X_Kolizji() + 1);
		NPC->Nakurwiaj_animacje(0, 5, 100, 2);
		break;
	case stoj:
		break;

	}
}