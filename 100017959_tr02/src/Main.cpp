// @file   Main.cpp
// @author Matheus Vieira Portela
// @date   25/03/2015
//
// @brief Game entry point
//
// Implementation of a simple main class to initialize the game.

#include "Game.h"
#include "ConfigParser.h"

// Deletes after testing
#include "Point.h"
#include "Rect.h"

int main(int argc, char **argv)
{
    CFG_INIT("Configurations.cfg");

    // Game game(CFG_GETS("WINDOW_TITLE"), CFG_GETI("WINDOW_WIDTH"),
    //     CFG_GETI("WINDOW_HEIGHT"));
    // game.Run();

    Point p(10, 10);
    Rect r;
    r.SetCenter(p, 5, 5);
    p = r.GetCenter();
    
    std::cout << p.ToString() << r.ToString() << std::endl;

    return 0;
}