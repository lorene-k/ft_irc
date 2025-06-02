#include "Server.hpp"

// *********************************************************** CHANNEL MODES */
void    Server::modeChanTopic(char mode, Channel *channel) {
    if (mode == '+')
        channel->setTopRestriction();
    else if (mode == '-')
        channel->unsetTopRestriction();
}

void    Server::modeInvite(char mode, Channel *channel) {
    channel->setInvite(mode);
}

bool    Server::modeLimit(Client* client, char mode, Channel *channel) {
    if (mode == '+' && client->getCmdArgsSize() < 3){
        client->formatResponse(ERR_NEEDMOREPARAMS, client->getName() + " " + client->getArgs()[0]);
        return (false);
    }
    channel->setLimit(client, mode);
    return (true);
}

bool    Server::modeOperator(Client* client, char mode, Channel *channel) {
    if (client->getCmdArgsSize() < 3) {
        client->formatResponse(ERR_NEEDMOREPARAMS, client->getName() + " " + client->getArgs()[0]);
        return (false);
    }
    else if (std::find(channel->getClients().begin(), channel->getClients().end(), client) == channel->getClients().end()) {
        client->formatResponse(ERR_USERNOTINCHANNEL, client->getName() + " " + client->getArgs()[1] + " " + client->getArgs()[0]);
        return (false);
    }
    else {
        if (mode == '+')
            channel->addOperator(client->getArgs()[2]);
        else if (mode == '-')
            channel->eraseOperator(client->getArgs()[2], client);
        client->setResponse(":" + client->getUsermask() + " MODE " + channel->getName() + (mode == '+' ? " +o " : " -o ") + client->getArgs()[2] + "\r\n");
        channel->talkToClients(client->getResponse(), client);
        return (true);
    }
}

bool    Server::modeChanKey(Client* client, char mode, Channel *channel) {
    if (mode == '+' && client->getCmdArgsSize() < 3) {
        client->formatResponse(ERR_NEEDMOREPARAMS, client->getName() + " " + client->getArgs()[0]);
        return (false);
    }
    if (mode == '+')
        channel->setKey(client->getArgs()[2]);
    else if (mode == '-')
        channel->clearKey();
    return (true);
}