//
// Created by josh on 4/29/23.
//

#include <iostream>
#include "TwilioClient.h"
#include "TwilioServer.h"
#include "Delegator.h"
#include "AI.h"

int main() {
    // read Twilio credentials from environment variables
    string account_sid = getenv("TWILIO_ACCOUNT_SID");
    string auth_token = getenv("TWILIO_AUTH_TOKEN");
    string from_number = getenv("TWILIO_FROM_NUMBER");
    TwilioClient client(account_sid, auth_token, from_number);
    AI ai(getenv("OPENAI_API_KEY"));
    ai.askGPT("test");

    Delegator *delegator = new Delegator(&client, &ai);

    // send a message
    //client.send_message("+16142027904", "Hello, world!");
    try
    {
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = static_cast<unsigned short>(8000);

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(delegator, acceptor, socket);

        ioc.run();
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
