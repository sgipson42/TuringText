
#include "Delegator.h"
#include <iostream>
using namespace std;

void Delegator::handle_request(string phonenum, string msg) {
    cout << phonenum << ": " << msg << endl;
    string response = pAi->askGPT(msg);
    cout << "AI: " << response << endl;
    pClient->send_message(phonenum, response);
}

Delegator::Delegator(TwilioClient *pClient, AI *pAi) {
    this->pClient = pClient;
    this->pAi = pAi;
}
