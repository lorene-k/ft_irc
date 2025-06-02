#include "Server.hpp"

// ******************************************************************** JOIN */
bool    Server::controlKey(Client* client, Channel* channel, size_t index, std::vector<std::string> keys) {
    if (!channel->hasKey())
        return true;
    else if (channel->hasKey() && keys.size() == 0) {
        client->formatResponse(ERR_BADCHANNELKEY, client->getName() + " " + channel->getName());
        return false;
    }
    if (channel->hasKey() && keys[index] != channel->getKey()) {
        client->formatResponse(ERR_BADCHANNELKEY, client->getName() + " " + channel->getName());
        return false;
    }
    return true;
}

bool     Server::controlJoin(Client* client, Channel* channel, size_t index, std::vector<std::string> keys) {
    if (client->checkIfInChannel(channel->getName()))
        return false;
    if (channel->isInvite() == true && channel->isInvited(client) == false) {
        client->formatResponse(ERR_INVITEONLYCHAN, client->getName() + " " + channel->getName());
        return false;
    }
    if (channel->getLimit() != -1 && channel->getClientsSize() >= (size_t)channel->getLimit()) {
        client->formatResponse(ERR_CHANNELISFULL, client->getName() + " " + channel->getName());
        return false;
    }
    if (!controlKey(client, channel, index, keys))
        return false;
    return true;
}

void     Server::createChannel(std::string channelName, Client* client, size_t index, std::vector<std::string> keys) {
    Channel* channel = new Channel(channelName);
    channel->addOperator(client->getName());
    channel->addClient(client);
    _channels.push_back(channel);
    client->addChannelToClient(channel);
    if (keys.size() > 0 && keys.size() > (index))
        channel->setKey(keys[index]);
    client->sendJoinRPL(channel, this);
}

bool    Server::joinChannel(std::string channelName, Client* client, size_t index, std::vector<std::string> keys) {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName) {
            if (controlJoin(client, _channels[i], index, keys)) {
                _channels[i]->addClient(client);
                client->addChannelToClient(_channels[i]);
                client->sendJoinRPL(_channels[i], this);
            }
            return true;
        }
    }
    return false;
}

void     Server::createOrJoinChannel(std::string channelName, Client* client, size_t index, std::vector<std::string> keys) {
    if (!joinChannel(channelName, client, index, keys))
        createChannel(channelName, client, index, keys);
}
