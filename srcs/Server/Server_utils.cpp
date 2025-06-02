#include "Server.hpp"

// **************************************************************** SEND MSG */
void    Server::sendToClient(std::string target, std::string msg, Client* client) {
    Client *targetClient = getClientByNick(target);
    if (targetClient == NULL) {
        client->formatResponse(ERR_NOSUCHNICK, client->getName() + " " + target);
        return ;
    }
    targetClient->relayData(msg.c_str(), targetClient->getFd());
}

void    Server::sendToChannel(std::string target, std::string msg, Client* client) {
    Channel *channel = getChannel(target);
    if (channel == NULL)
        client->formatResponse(ERR_NOSUCHNICK, client->getName() + " " + target);
    else
        channel->talkToClients(msg, client);
}

// **************************************************************** CHECKERS */
bool    Server::checkIfNamed(Client &client) const {
    if (client.getIfNamed())
        return true;
    return false;
}

bool    Server::checkUsedNickname(std::string &nickname) const {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getName() == nickname)
            return true;
    }
    return false;
}

bool    Server::checkUsedUsername(std::string &username) const {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getUsername() == username)
            return true;
    }
    return false;
}

bool    Server::doesChanExist(std::string channelName) {
    for (size_t i = 0; i <_channels.size(); i++) {
        if (channelName == _channels[i]->getName())
            return true;
    }
    return false;
}

bool Server::isTargetInChan(std::string channelName, std::string targetName) {
    for (size_t i = 0; i < _channels.size(); i++){
        if (_channels[i]->getName() == channelName)
            if(_channels[i]->isClient(targetName))
                return true;
    }
    return false;
}

// ********************************************************************** UTILS */
void    Server::displayClients(std::string channelName, Client *client) {
    Channel *channel = getChannel(channelName);
    std::string joinedClients = channel->getjoinedClients();
    client->formatRPL(RPL_NAMREPLY, client->getName() + " = " + channelName + " :" + joinedClients);
    channel->talkToClients(client->getResponse(), client);
    client->formatResponse(RPL_ENDOFNAMES, client->getName() + " " + channelName);
    channel->talkToClients(client->getResponse(), client);
}

void    Server::displayChannels(Client *client) {
    for (size_t i = 0; i < _channels.size(); i++) {
       displayClients(_channels[i]->getName(), client);
    }
}

void Server::handleEmptyChannel(Channel *channel, Client *client) {
    std::vector<Channel*>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
    if (it != _channels.end()){
        if (channel->getClientsSize() == 0) {
            delete *it;
            _channels.erase(it);
        }
        else if ((*it)->getOpNames().empty() && (*it)->getClientsSize() > 0) {
            std::string newOp = (*it)->getClients()[0]->getName();
            (*it)->addOperator(newOp);
            client->setResponse(":" + client->getUsermask() + " MODE " + channel->getName() + " +o " + newOp + "\r\n");
            channel->talkToClients(client->getResponse(), client);
        }
    }
}