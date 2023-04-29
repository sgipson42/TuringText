//
// Created by josh on 4/29/23.
//

#include "AI.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

AI::AI(string openai_api_key) {
    this->openai_api_key = openai_api_key;
}

string AI::askGPT(string q) {
    string answer = "";
    int retries = 1;
    while (answer.empty() && retries > 0) {
        cout << "q: " << q << endl;
        auto j = nlohmann::json::object(
                {
                        {"model", "gpt-4"},
                        {"max_tokens", 1000},
                        {"temperature", 0.5},
                        {"top_p", 1},
                        {"n", 1},
                        {"stream", false},
                        {"stop", "\n"}
        });
        j["messages"] = nlohmann::json::array();
        j["messages"].push_back(nlohmann::json::object(
                {
                        {"role", "system"},
                        {"content", "You are a human talking to a judge. You are part of a Turing Test and your goal is to convince the judge that you are a human and the other player is the AI. Keep the response very short as it will be sent over SMS. Use abbreviations and emojis sometimes."}
                }));
        j["messages"].push_back(nlohmann::json::object(
                {
                        {"role", "assistant"},
                        {"content", "Respond to this message from the judge."}
                }));
        j["messages"].push_back(nlohmann::json::object(
                {
                        {"role", "user"},
                        {"content", q}
                }));
        string body = j.dump();
        cout << body << endl;
        cpr::Response r = cpr::Post(cpr::Url{"https://api.openai.com/v1/chat/completions"},
                                    cpr::Header{
                                            {"Authorization", "Bearer " + openai_api_key},
                                            {"Content-type", "application/json"}},
                                    cpr::Body{ body });
        cout << r.text << endl;
        auto d = nlohmann::json::parse(r.text);
        if (!d["choices"].empty()) {
            answer = d["choices"][0]["message"]["content"];
            //trim(answer);
            cout << "Response: " << answer << endl;
        }
        else {
            cout << "Invalid response: " << r.text << endl;
        }
        retries--;
    }
    return answer;
}
