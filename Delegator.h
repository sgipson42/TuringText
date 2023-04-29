#ifndef DELEGATOR_H
#define DELEGATOR_H

#include <string>
#include <queue>
#include <set>
#include "TwilioClient.h"
#include "AI.h"
#include "GameBook.h"
#include "HelpTool.h"

using namespace std;

class Delegator {
private:
    AI *ai;
    TwilioClient *twilioClient;
    queue<string> p_num;
    queue<string> j_num;
    set<string> asked_player_judge;
    GameBook *gb;
    HelpTool *helpTool;
public:
    Delegator(TwilioClient *twilioClient, AI *ai, GameBook *gb, HelpTool *helpTool);
    string handle_request(string phonenum, string msg);
};

extern Delegator *delegator;

#endif

