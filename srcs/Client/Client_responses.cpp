#include "Client.hpp"

// ******************************************************* RESPONSE HANDLING */
void Client::formatResponse(std::pair<std::string, std::string> response, std::string varName) {
    std::ostringstream ssResponse;
    ssResponse << ":ircserv " << response.first << " " << varName << " " << response.second << "\r\n";
    _cmdResponse = ssResponse.str();
    relayData(_cmdResponse.c_str(), _fd);
}

void Client::formatRPL(std::string code, std::string msg) {
    std::ostringstream ssResponse;
    ssResponse << ":ircserv " << code << " " << msg << "\r\n";
    _cmdResponse = ssResponse.str();
    relayData(_cmdResponse.c_str(), _fd);
}

void Client::formatCmdMsg(std::string cmdName, std::string msg, std::string nick) {
    std::ostringstream ssResponse;
    std::string nickname;
    ssResponse << ":" << (!nick.empty() ? nick : _usermask ) << " " << cmdName << msg << "\r\n";
    _cmdResponse = ssResponse.str();
    if (cmdName != "KICK")
        relayData(_cmdResponse.c_str(), _fd);
}

// ******************************************************************** JOIN */
void    Client::sendJoinRPL(Channel *channel, Server *server) {
    std::string channelName = " " + channel->getName();
    _cmdResponse = ":" + _usermask + " JOIN" + channelName + "\r\n";
    relayData(_cmdResponse.c_str(), _fd);
    channel->talkToClients(_cmdResponse, this);
    if (!channel->getTopic().empty()) {
        formatRPL(RPL_TOPIC, _nickname + channelName + " :" + channel->getTopic());
        channel->talkToClients(_cmdResponse, this);
    }
    server->displayClients(channel->getName(), this);
}

void Client::sendKickRPL(Channel *channel, Client *kicker) {
    std::string msg = collectTrailingMsg(_cmdArgs);
    if (msg.empty() || msg.find("bot"))
        msg = ":kicked from channel";
    std::string kickerUsermask = kicker->getName() + "!" + kicker->getUsername() + "@localhost";
    formatCmdMsg("KICK ", channel->getName() + " " + _nickname + " " + msg, kickerUsermask);
    channel->talkToClients(_cmdResponse, this);
    relayData(_cmdResponse.c_str(), _fd);
}