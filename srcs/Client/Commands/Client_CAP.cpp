#include "Client.hpp"

// ********************************************************************* CAP */
void    Client::handleCap(Server* server) {
    if (_cmdArgs[0] == "LS") {
        _cmdResponse = ":ircserv CAP * LS :\r\n";
        relayData(_cmdResponse.c_str(), _fd);
    }
    (void)server;
}