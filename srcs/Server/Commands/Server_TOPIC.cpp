#include "Server.hpp"

// ******************************************************************* TOPIC */
std::string    Server::getChanTopic(std::string channelName) { // test function
    for (size_t i = 0; i < _channels.size(); i ++) {
        if (_channels[i]->getName() == channelName)
            return _channels[i]->getTopic();
    }
    return NULL;
}

void    Server::setChanTopic(std::string channelName, std::string topic) {
    for (size_t i = 0; i < _channels.size(); i ++) {
        if (_channels[i]->getName() == channelName)
            _channels[i]->setTopic(topic);
    }
}

bool    Server::hasTopicRestriction(std::string channelName) {
    for (size_t i = 0; i < _channels.size(); i ++) {
        if (_channels[i]->getName() == channelName)
            return _channels[i]->isTopicRestricted();
    }
    return false;
}

bool    Server::chanHasTopic(std::string channelName) {
    for (size_t i = 0; i <_channels.size(); i++) {
        if (channelName == _channels[i]->getName()) {
            if (_channels[i]->hasTop()) {
                return true;
            }
            else
                return false;
        }
    }
    return false;
}
