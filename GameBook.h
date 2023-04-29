//
// Created by josh on 4/29/23.
//

#ifndef TURINGTEXT_GAMEBOOK_H
#define TURINGTEXT_GAMEBOOK_H


#include <string>
#include <map>
#include "Game.h"
using namespace std;

class GameBook {
private:
    map<string, Game*> games;
public:
    Game *getGame(string phonenum);

    void addGame(Game *pGame);
};


#endif //TURINGTEXT_GAMEBOOK_H
