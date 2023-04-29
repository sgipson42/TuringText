#ifndef DELEGATOR_H
#define DELEGATOR_H

#include <string>
#include "TwilioClient.h"
#include "AI.h"

using namespace std;

class Delegator {
private:
    AI *pAi;
    TwilioClient *pClient;
public:
    Delegator(TwilioClient *pClient, AI *pAi);
    void handle_request(string phonenum, string msg);
};

#endif

