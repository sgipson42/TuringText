
#include "Delegator.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

Delegator *delegator = nullptr;

string Delegator::handle_request(string phonenum, string msg) {
    // lowercase msg
    string msg_lower = msg;
    for(int i = 0; i < msg.size(); i++) {
        msg_lower[i] = tolower(msg[i]);
    }
    cout << phonenum << ": " << msg << endl;
    if(msg_lower == "help") {
        string response = helpTool->help();
        return response;
    }
    Game *g = gb->getGame(phonenum);
    if(g) {
        if(g->isJudge(phonenum)) {
            if(msg_lower.find("player a") != string::npos) {
                msg = msg.substr(msg_lower.find("player a") + 9);
                if(g->isAI("A")) {
                    string response = ai->askGPT(msg);
                    twilioClient->send_message(phonenum, response);
                } else {
                    string playernum = g->getPlayerPhonenum();
                    twilioClient->send_message(playernum, msg);
                }
            } else if(msg_lower.find("player b") != string::npos) {
                msg = msg.substr(msg_lower.find("player b") + 9);
                if(g->isAI("B")) {
                    string response = ai->askGPT(msg);
                    string letter = g->isAI("A") ? "A" : "B";
                    response = "Player " + letter + ": " + response;
                    // wait random time before responding
                    this_thread::sleep_for(chrono::seconds(rand() % 30));
                    twilioClient->send_message(phonenum, response);
                } else {
                    string playernum = g->getPlayerPhonenum();
                    twilioClient->send_message(playernum, msg);
                }
            }
        } else {
            string judgenum = g->getJudgePhonenum();
            string letter = g->isAI("A") ? "B" : "A";
            msg = "Player " + letter + ": " + msg;
            twilioClient->send_message(judgenum, msg);
        }
    } else {
        // no game yet
        if(asked_player_judge.find(phonenum) == asked_player_judge.end()) {
            // haven't asked player_or_judge yet
            asked_player_judge.insert(phonenum);
            string response = "Are you a player or judge?";
            return response;
        } else {
            // already asked player/judge
            if(msg_lower == "judge") {
                if(p_num.size() > 0) {
                    string p_phonenum = p_num.front();
                    p_num.pop();
                    cout << "Starting game between " << p_phonenum << " and " << phonenum << endl;
                    Game *g = new Game(p_phonenum, phonenum);
                    gb->addGame(g);
                    twilioClient->send_message(p_phonenum, "A judge has joined. You are now in a game.");
                    return "Ask a question to player A or B";
                } else {
                    j_num.push(phonenum);
                    return "Ok, waiting for a player.";
                }
            } else if (msg_lower == "player") {
                if(j_num.size() > 0) {
                    string j_phonenum = j_num.front();
                    j_num.pop();
                    cout << "Starting game between " << phonenum << " and " << j_phonenum << endl;
                    Game *g = new Game(phonenum, j_phonenum);
                    gb->addGame(g);
                    twilioClient->send_message(j_phonenum, "A player has joined. You are now in a game. Ask a question of Player A or B.");
                    return "Ok, a judge has been found. You are now in a game.";
                } else {
                    p_num.push(phonenum);
                    return "Ok, waiting for a judge.";
                }
            }
        }
    }
    return "";
}

Delegator::Delegator(TwilioClient *twilioClient, AI *ai, GameBook *gb, HelpTool *helpTool) {
    this->twilioClient = twilioClient;
    this->ai = ai;
    this->gb = gb;
    this->helpTool = helpTool;
}
