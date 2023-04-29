
#include "Delegator.h"
#include "Game.h"
#include <iostream>
using namespace std;

void Delegator::handle_request(string phonenum, string msg) {
    cout << phonenum << ": " << msg << endl;
    if(msg == "help") {
        string response = helpTool->help();
        cout << "AI: " << response << endl;
        twilioClient->send_message(phonenum, response);
        return;
    }
    Game *g = gb->getGame(phonenum);
    if(g) {
        if(g->isJudge(phonenum)) {
            if(msg.find("player A") != string::npos) {
                if(g->isAI("A")) {
                    string response = ai->askGPT(msg);
                    twilioClient->send_message(phonenum, response);
                } else {
                    string playernum = g->getPlayerPhonenum();
                    twilioClient->send_message(playernum, msg);
                }
            } else if(msg.find("player B") != string::npos) {
                if(g->isAI("B")) {
                    string response = ai->askGPT(msg);
                    twilioClient->send_message(phonenum, response);
                } else {
                    string playernum = g->getPlayerPhonenum();
                    twilioClient->send_message(playernum, msg);
                }
            }
        }
    } else {
        // no game yet
        if(asked_player_judge.find(phonenum) == asked_player_judge.end()) {
            // haven't asked player_or_judge yet
            asked_player_judge.insert(phonenum);
            string response = "Are you a player or judge?";
            twilioClient->send_message(phonenum, response);
        } else {
            // already asked player/judge
            if(msg == "judge") {
                if(p_num.size() > 0) {
                    Game *g = new Game(p_num.front(), phonenum);
                    p_num.pop();
                    gb->addGame(g);
                    twilioClient->send_message(g->getJudgePhonenum(), "Ask a question to player A or B");
                } else {
                    j_num.push(phonenum);
                }
            } else if (msg == "player") {
                if(j_num.size() > 0) {
                    Game *g = new Game(phonenum, j_num.front());
                    j_num.pop();
                    gb->addGame(g);
                    twilioClient->send_message(g->getJudgePhonenum(), "Ask a question to player A or B");
                } else {
                    p_num.push(phonenum);
                }
            }
        }
    }
    string response = ai->askGPT(msg);
    cout << "AI: " << response << endl;
    twilioClient->send_message(phonenum, response);
}

Delegator::Delegator(TwilioClient *twilioClient, AI *ai, GameBook *gb, HelpTool *helpTool) {
    this->twilioClient = twilioClient;
    this->ai = ai;
    this->gb = gb;
    this->helpTool = helpTool;
}
