//
// Created by josh on 4/29/23.
//

#include "TwilioClient.h"
#include "curl/curl.h"

#include <iostream>
using namespace std;

TwilioClient::TwilioClient(string account_sid, string auth_token, string from_number) {
    this->account_sid = account_sid;
    this->auth_token = auth_token;
    this->from_number = from_number;
}

void TwilioClient::send_message(string to_number, string message) {
    CURL *curl = curl_easy_init();
    if (curl)
    {
        // Set Twilio API endpoint
        std::string url = "https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Set authentication
        std::string credentials = account_sid + ":" + auth_token;
        curl_easy_setopt(curl, CURLOPT_USERPWD, credentials.c_str());
        // Set message parameters
        std::string data = "From=" + from_number + "&To=" + to_number + "&Body=" + message;
        // Set POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        // Perform request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
        }
        // Clean up
        curl_easy_cleanup(curl);
    }
}
