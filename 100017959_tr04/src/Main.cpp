// @file   Main.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game entry point
//
// Implementation of a simple main class to initialize the game.

#include "ConfigParser.h"
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"

int main(int argc, char **argv)
{
    CFG_INIT("Configurations.cfg");

    Game game(CFG_GETS("WINDOW_TITLE"), CFG_GETI("WINDOW_WIDTH"),
        CFG_GETI("WINDOW_HEIGHT"));
    game.AddState(std::unique_ptr<State>(new TitleState()));
    game.Run();

    return 0;
}