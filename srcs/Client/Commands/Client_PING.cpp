#include "Client.hpp"

// ******************************************************************** PING */
void Client::handlePing(Server* server) {
    _cmdResponse = "PONG :" + _cmdArgs[0] + "\r\n";
    relayData(_cmdResponse.c_str(), _fd);
    (void)server;
}
