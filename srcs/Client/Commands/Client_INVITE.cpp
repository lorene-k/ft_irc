#include "Client.hpp"

// ******************************************************************* INVITE */
bool    Client::controlInvite(Server* server, Channel *channel) {
    if (_cmdArgs.size() < 2) {
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (!server->doesChanExist(_cmdArgs[1])) {
        formatResponse(ERR_NOSUCHCHANNEL, _nickname + " " + _cmdArgs[1]);
        return false;
    }
    if (!checkIfInChannel(_cmdArgs[1])){
        formatResponse(ERR_NOTONCHANNEL, _nickname + " " + _cmdArgs[1]);
        return false;
    }
    if (!isOperator(_cmdArgs[1]) && channel->isInvite()) {
        formatResponse(ERR_CHANOPRIVSNEEDED, _nickname + " " + _cmdArgs[1]);
        return false;
    }
    if (!server->checkUsedNickname(_cmdArgs[0])) {
        formatResponse(ERR_NOSUCHNICK, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (server->isTargetInChan(_cmdArgs[1], _cmdArgs[0])) {
        formatResponse(ERR_USERONCHANNEL, _nickname + " " + _cmdArgs[0] + " " + _cmdArgs[1]);
        return false;
    }
    return true;
}

void    Client::handleInvite(Server* server) {
    Channel *channel = server->getChannel(_cmdArgs[1]);
    if (controlInvite(server, channel)) {
        server->inviteClient(_nickname, _cmdArgs[0], _cmdArgs[1]);
        std::string msg = _nickname + " " +  _cmdArgs[0] + " " + _cmdArgs[1];
        formatRPL(RPL_INVITING, msg);
    }
}
