// @file   Main.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game entry point
//
// Implementation of a simple main class to initialize the game.

#include <iostream>

#include "Game.h"
#include "Config.h"

int main(int argc, char **argv)
{
    CFG_INIT("Configurations.cfg");

    Game game("Matheus Vieira Portela - 10/0017959", 1024, 600);
    game.Run();

    return 0;
}