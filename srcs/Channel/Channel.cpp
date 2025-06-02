#include "Channel.hpp"

Channel::Channel() : _inviteOnly(false), _topicRestriction(false), _userLimit(-1) {} // revoir topicrestriction pas sur de ce que c est

Channel::Channel(std::string channelName) : _name(channelName), _inviteOnly(false), _topicRestriction(false), _userLimit(-1) {}

Channel::Channel(std::string channelName, bool inviteOnly) : _name(channelName), _inviteOnly(inviteOnly), _topicRestriction(false), _userLimit(-1) {}

Channel::Channel(const Channel& other) {
    if (this != &other) {
        _name = other._name;
        _topic = other._topic;
        _opNames = other._opNames;
        _clients = other._clients;
        _invitedClients = other._invitedClients;
        _inviteOnly = other._inviteOnly;
        _topicRestriction = other._topicRestriction;
        _userLimit = other._userLimit;
        _channelKey = other._channelKey;
        _topic = other._topic;
        _key = other._key;
    }
}

Channel& Channel::operator=(Channel& other) {
    if (this != &other) {
        _name = other._name;
        _topic = other._topic;
        _opNames = other._opNames;
        _clients = other._clients;
        _invitedClients = other._invitedClients;
        _inviteOnly = other._inviteOnly;
        _topicRestriction = other._topicRestriction;
        _userLimit = other._userLimit;
        _channelKey = other._channelKey;
        _topic = other._topic;
        _key = other._key;
    }
    return *this;
}

Channel::~Channel() {}

// ***************************************************************** GETTERS */
std::string Channel::getName() {
    return _name;
}

std::string Channel::getKey() {
    return _channelKey;
}

std::string Channel::getTopic() {
    return _topic;
}

bool Channel::isInvite() {
    if (_inviteOnly == true)
        return true;
    return false;
}

bool Channel::isTopicRestricted() {
    if (_topicRestriction == true)
        return true;
    return false;
}

int Channel::getLimit() {
    return _userLimit;
}

size_t Channel::getClientsSize() {
    return _clients.size();
}

std::vector<std::string> Channel::getOpNames() {
    return (_opNames);
}

std::vector<Client*> Channel::getClients()
{
    return (_clients);
}

bool    Channel::isClient(std::string clientName) {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (clientName == _clients[i]->getName())
            return true;
    }
    return false;
}

bool    Channel::isInvited(Client* client) {
    for (size_t i = 0; i < _invitedClients.size(); i++) {
        if (client->getName() == _invitedClients[i]->getName())
            return true;
    }
    return false;
}

// ***************************************************************** SETTERS */
void Channel::setInvite(char mode) {
    if (mode == '+') 
        _inviteOnly = true;
    else
        _inviteOnly = false;
}

void Channel::setLimit(Client* client, char mode) {

    if (mode == '+') {
        if ((size_t)std::atoi(client->getArgs()[2].c_str()) < _clients.size()) {
            return ;
        }
        _userLimit = std::atoi(client->getArgs()[2].c_str());
    }
    else {
        _userLimit = -1;
    }
}

void  Channel::setKey(std::string channelKey) {
    _channelKey = channelKey;
}

void            Channel::clearKey() {
    _channelKey.clear();
}

void  Channel::setTopic(std::string topic) {
    if (topic.empty() || topic == ":") {
        _topic.clear();
    }
    else
        _topic = topic;
}

void            Channel::setTopRestriction() {
    _topicRestriction = true;
}
void            Channel::unsetTopRestriction() {
    _topicRestriction = false;
}

bool Channel::hasKey() {
    if (_channelKey.empty())
        return false;
    return true;
}

bool Channel::hasTop() {
    if (_topic.empty()) {
        return false;
    }
    return true;
}
