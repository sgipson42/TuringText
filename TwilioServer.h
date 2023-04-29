//
// Created by josh on 4/29/23.
//

#ifndef TURINGTEXT_TWILIOSERVER_H
#define TURINGTEXT_TWILIOSERVER_H

#include <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
class Delegator;

void http_server(Delegator *delegator, tcp::acceptor& acceptor, tcp::socket& socket);

#endif //TURINGTEXT_TWILIOSERVER_H
