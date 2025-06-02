#include "Client.hpp"

// ******************************************************************** JOIN */
void Client::handleJoin(Server* server) {
    if (_cmdArgs.size() < 1)
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " JOIN");
    else
    {    
        std::vector<std::string> channels = splitArgs(_cmdArgs[0], ',');
        std::vector<std::string> keys;
        if (_cmdArgs.size() > 1)
            keys = splitArgs(_cmdArgs[1], ',');
        for (size_t i = 0; i < channels.size(); i++) {
            if (channels[i][0] == '#' && channels[i].size() > 1)
                server->createOrJoinChannel(channels[i], this, i, keys);
            else
                formatResponse(ERR_BADCHANMASK, _cmdArgs[0]);
        }
    }
}
