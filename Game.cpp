//
// Created by josh on 4/29/23.
//

#include "Game.h"

Game::Game(string playerPhonenum, string judgePhonenum) {
    this->playerPhonenum = playerPhonenum;
    this->judgePhonenum = judgePhonenum;
    string aiLetter = rand() % 2 == 0 ? "A" : "B";
    this->aiLetter = aiLetter;
}

bool Game::isJudge(string phonenum) {
    return judgePhonenum == phonenum;
}

bool Game::isAI(string letter) {
    return aiLetter == letter;
}

string Game::getPlayerPhonenum() {
    return playerPhonenum;
}

string Game::getJudgePhonenum() {
    return judgePhonenum;
}
