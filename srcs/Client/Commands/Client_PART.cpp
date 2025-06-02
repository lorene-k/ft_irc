#include "Client.hpp"

// ******************************************************************** PART */
void Client::removeFromChannel(Channel *channel) {
    channel->eraseOperator(_nickname, this);
    channel->eraseClientFromChannel(this);
    eraseChannelFromClient(channel);
}

void Client::leaveChannel(Channel *channel, Server *server) {
    removeFromChannel(channel);
    server->handleEmptyChannel(channel, this);
}

void Client::handlePart(Server* server) {
    if (_cmdArgs.size() < 1)
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
    else {
        std::vector<std::string> channels = splitArgs(_cmdArgs[0], ',');
        std::string msg = collectTrailingMsg(_cmdArgs);
        if (msg.empty())
            msg = ":leaving";
        for (size_t i = 0; i < channels.size(); i++) { 
            if (checkChanErrors(channels[i], server)) {
                Channel* channel = server->getChannel(channels[i]);
                formatCmdMsg("PART ", channel->getName() + " " + msg);
                channel->talkToClients(_cmdResponse, this);
                leaveChannel(channel, server);
            }
        }
    }
}
