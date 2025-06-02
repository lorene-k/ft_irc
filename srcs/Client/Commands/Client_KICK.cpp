#include "Client.hpp"

// ******************************************************************** KICK */
bool    Client::controlKick(Server* server) {
    if (_cmdArgs.size() < 2) {
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (_cmdArgs[0][0] != '#') {
        formatResponse(ERR_BADCHANMASK, _cmdArgs[0]);
        return false;
    }
    if (!checkChanErrors(_cmdArgs[0], server))
        return (false);
    if (!isOperator(_cmdArgs[0])) {
        formatResponse(ERR_CHANOPRIVSNEEDED, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    return true;
}

void    Client::handleKick(Server* server) {
    if (!controlKick(server))
        return ;
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == _cmdArgs[0]) {
            if (!_channels[i]->kickClient(_cmdArgs[1], this)) {
                formatResponse(ERR_USERNOTINCHANNEL, _nickname + " " + _cmdArgs[1] + " " + _cmdArgs[0]);
                return ;
            }
        }
    }
}
