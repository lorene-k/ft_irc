#include "Server.hpp"

// ****************************************************************** INVITE */

void    Server::inviteClient(std::string issuer, std::string clientName, std::string channelName) {
    size_t i = 0;
    size_t j = 0;
    
    for(; i < _clients.size(); i++)
        if (_clients[i]->getName() == clientName)
            break ;
    for (; j < _channels.size(); j++)
        if (_channels[j]->getName() == channelName)
            break ;
    _channels[j]->sendInvite(_clients[i]);
    _clients[i]->formatCmdMsg("INVITE", " " + clientName + " " + channelName, issuer);
}
