// @file   Main.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game entry point
//
// Implementation of a simple main class to initialize the game.

#include "Game.h"
#include "ConfigParser.h"

int main(int argc, char **argv)
{
    CFG_INIT("Configurations.cfg");

    Game game(CFG_GETS("WINDOW_TITLE"), CFG_GETI("WINDOW_WIDTH"),
        CFG_GETI("WINDOW_HEIGHT"));
    game.Run();

    return 0;
}