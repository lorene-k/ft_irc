#include "Client.hpp"

// ******************************************************************* NAMES */
void    Client::handleNames(Server* server) {
    if (_cmdArgs.size() == 0)
        server->displayChannels(this);
    else {
        std::vector<std::string> channels = splitArgs(_cmdArgs[0], ',');
        for (size_t i = 0; i < channels.size(); i++) {
            if (server->doesChanExist(channels[i])) {
                server->displayClients(channels[i], this);
            }
            else
                formatResponse(RPL_ENDOFNAMES, _nickname + " " + channels[i]);
        }
    }
}