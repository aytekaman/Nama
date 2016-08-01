#include "game.h"

int main()
{
	Game* game = Game::GetInstance();

	game->LoadScene( "Main.lua" );

	game->Run();
}