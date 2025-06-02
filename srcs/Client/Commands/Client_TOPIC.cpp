#include "Client.hpp"

// ******************************************************************** TOPIC */
bool Client::controlTopic(Server* server) {
    if (_cmdArgs.size() < 1) {
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (!server->doesChanExist(_cmdArgs[0])) {
        formatResponse(ERR_NOSUCHCHANNEL, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (!checkIfInChannel(_cmdArgs[0])) {
        formatResponse(ERR_NOTONCHANNEL, _nickname + " " + _cmdArgs[0]);
        return false;
    }
    if (_cmdArgs.size() > 1 && (!isOperator(_cmdArgs[0]) && server->hasTopicRestriction(_cmdArgs[0]))) {
        formatResponse(ERR_CHANOPRIVSNEEDED, _cmdArgs[0]);
        return false;
    }
    return true;
}

void Client::handleTopic(Server* server) {
    if (!controlTopic(server))
        return ;
    if (_cmdArgs.size() == 1) {
        if (!server->chanHasTopic(_cmdArgs[0])){
            formatResponse(RPL_NOTOPIC, _nickname + " " + _cmdArgs[0]);
            return ;
        } else {
            std::string topicToDisplay = _nickname + " " + _cmdArgs[0] + server->getChanTopic(_cmdArgs[0]);
            formatRPL(RPL_TOPIC, topicToDisplay);
        }
    } else if (_cmdArgs.size() > 1) {
        std::string newTopic = collectTrailingMsg(_cmdArgs);
        server->setChanTopic(_cmdArgs[0], newTopic);
        std::string msg = " " +_cmdArgs[0] + " :" + newTopic;
        for (size_t i = 0; i < _channels.size(); i++) {
            if (_channels[i]->getName() == _cmdArgs[0]){
                _channels[i]->cmdRespToClients("TOPIC", msg, "", _usermask);
            }
        }
    }
}

