//
// Created by josh on 4/29/23.
//

#include <iostream>
#include "TwilioClient.h"
#include "TwilioServer.h"
#include "Delegator.h"
#include "AI.h"

int main() {
    srand(time(NULL));
    // read Twilio credentials from environment variables
    // if env var exists
    string account_sid;
    if(getenv("TWILIO_ACCOUNT_SID") != NULL) {
        account_sid = getenv("TWILIO_ACCOUNT_SID");
    }
    string auth_token;
    if(getenv("TWILIO_ACCOUNT_SID") != NULL) {
        auth_token = getenv("TWILIO_ACCOUNT_SID");
    }
    string from_number;
    if(getenv("TWILIO_ACCOUNT_SID") != NULL) {
        from_number = getenv("TWILIO_ACCOUNT_SID");
    }
    TwilioClient *client = new TwilioClient(account_sid, auth_token, from_number);
    if(getenv("OPENAI_API_KEY") == NULL || getenv("OPENAI_API_KEY") == "") {
        cout << "Error: OPENAI_API_KEY not set" << endl;
        return 1;
    }
    AI *ai = new AI(getenv("OPENAI_API_KEY"));
    GameBook *gb = new GameBook;
    HelpTool *helptool = new HelpTool;

    delegator = new Delegator(client, ai, gb, helptool);

    // send a message
    //client.send_message("+16142027904", "Hello, world!");
    try
    {
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = static_cast<unsigned short>(8000);

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
