#include "Channel.hpp"

void Channel::addOperator(std::string opName) {
    _opNames.push_back(opName);
}

void Channel::addClient(Client* client) {
    _clients.push_back(client);
}

bool Channel::checkOpName(std::string clientName) {
    for (size_t i = 0; i < _opNames.size(); i++) {
        if (_opNames[i] == clientName)
            return true;
    }
    return false;
}

void Channel::eraseOperator(std::string opName, Client *client) {
    std::vector<std::string>::iterator it = std::find(_opNames.begin(), _opNames.end(), opName);
    if (it != _opNames.end()) {
        client->setResponse(":" + client->getUsermask() + " MODE " + _name + " -o " + opName+ "\r\n");
        talkToClients(client->getResponse(), client);
        _opNames.erase(it);
    }
}
    
void Channel::eraseClientFromChannel(Client *client) {
    std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
    if (it != _clients.end())
        _clients.erase(it);
}

bool Channel::kickClient(std::string clientName, Client *client) {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getName() == clientName
            && clientName != client->getName()) {
            _clients[i]->sendKickRPL(this, client);
            _clients[i]->eraseChannelFromClient(this);
            _clients.erase(_clients.begin() + i);
            return true;
        }
    }
    return false;
}

std::string  Channel::getjoinedClients() {
    std::string joinedClients;

    for (size_t i = 0; i < _clients.size(); i++) {
        std::string nickname = _clients[i]->getName();
        if (_clients[i]->isOperator(_name))
            nickname = "@" + nickname;
        if (!joinedClients.empty())
            joinedClients += " ";
        joinedClients += nickname;
    }
    return (joinedClients);
}

std::string Channel::getModes() const {
    std::string modes = "+";
    if (_topicRestriction)
        modes += "t";
    if (!_channelKey.empty())
        modes += "k";
    if (_userLimit != -1)
        modes += "l";
    if (_inviteOnly == true)
        modes += "i";
    if (modes.size() == 1)
        modes.clear();
    return (modes);
}

void Channel::talkToClients(std::string msg, Client* client) {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getFd() != client->getFd()){
            _clients[i]->relayData(msg.c_str(), _clients[i]->getFd());
        }
    }
}

void Channel::cmdRespToClients(std::string cmdName, std::string msg, std::string kickedClient, std::string clientName) { // 
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getName() != kickedClient)
        _clients[i]->formatCmdMsg(cmdName, msg, clientName);
    }
}

void Channel::sendInvite(Client *client) {
    _invitedClients.push_back(client);
}