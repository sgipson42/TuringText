//
// Created by josh on 4/29/23.
//

#ifndef TURINGTEXT_GAME_H
#define TURINGTEXT_GAME_H

#include <string>
using namespace std;

class Game {
private:
    string judgePhonenum;
    string aiLetter;
    string playerPhonenum;
public:
    Game(string judgePhonenum, string playerPhonenum);
    bool isJudge(string phonenum);
    bool isAI(string letter);
    string getPlayerPhonenum();
    string getJudgePhonenum();
};


#endif //TURINGTEXT_GAME_H
