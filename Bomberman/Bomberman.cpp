#include "Glowna.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	CGlowna* Bomberman = new CGlowna(576, 640);
	Bomberman->PetlaGlowna();
	delete Bomberman;
	return 0;
}