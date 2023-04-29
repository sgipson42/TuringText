//
// Created by josh on 4/29/23.
//

#include "GameBook.h"

Game *GameBook::getGame(string phonenum) {
    if (games.find(phonenum) == games.end()) {
        return nullptr;
    }
    return games[phonenum];
}

void GameBook::addGame(Game *pGame) {
    games[pGame->getPlayerPhonenum()] = pGame;
    games[pGame->getJudgePhonenum()] = pGame;
}
