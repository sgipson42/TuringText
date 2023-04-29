//
// Created by josh on 4/29/23.
//

#ifndef TURINGTEXT_TWILIOCLIENT_H
#define TURINGTEXT_TWILIOCLIENT_H

#include <string>
using namespace std;

class TwilioClient {
private:
    string account_sid;
    string auth_token;
    string from_number;
public:
    TwilioClient(string account_sid, string auth_token, string from_number);
    void send_message(string to_number, string message);
};


#endif //TURINGTEXT_TWILIOCLIENT_H
