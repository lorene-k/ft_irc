#include "Client.hpp"

// ********************************************************************* WHO */
void Client::handleWho(Server* server) {
    formatResponse(RPL_ENDOFWHO, _nickname + " " + _cmdArgs[0]);
    (void)server;
}
