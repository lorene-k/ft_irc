#include "Client.hpp"

// **************************************************************** CHANNELS */
bool Client::checkChanErrors(std::string const &channel, Server* server)
{
    if (!server->doesChanExist(channel)) {
        formatResponse(ERR_NOSUCHCHANNEL, _nickname + " " + _cmdArgs[0]);
        return (false);
    }
    else if (!checkIfInChannel(channel)) {    
        formatResponse(ERR_NOTONCHANNEL, _nickname + " " + _cmdArgs[0]);
        return (false);
    }
    return (true);
}

void Client::eraseChannelFromClient(Channel *channel) {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channel->getName())
            _channels.erase(_channels.begin() + i);
    }
}

void Client::addChannelToClient(Channel *channel) {
    _channels.push_back(channel);
}

bool Client::checkIfInChannel(std::string channelName) {
    for (size_t i = 0; i < _channels.size(); i++){
        if (_channels[i]->getName() == channelName)
            return true;
    }
    return false;
}

bool Client::isTargetInChan(std::string channelName, std::string targetName) {
    for (size_t i = 0; i < _channels.size(); i++){
        if (_channels[i]->getName() == channelName)
            if(_channels[i]->isClient(targetName))
                return true;
    }
    return false;
}

bool    Client::isOperator(std::string channelName) {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName) {
            if (_channels[i]->checkOpName(_nickname))
                return true;
            else
                return false;
        }
    }
    return false;
}

// ************************************************** SPLIT & JOIN (privmsg) */
std::vector<std::string> Client::splitArgs(std::string args, char delimiter)
{
    std::vector<std::string> argVec;
    std::string::size_type start = 0;
    std::string::size_type end = args.find(delimiter);

    while (end != std::string::npos) {
        argVec.push_back(args.substr(start, end - start));
        start = end + 1;
        end = args.find(delimiter, start);
    }
    argVec.push_back(args.substr(start));
    return (argVec);
}

std::string Client::joinArgs(std::vector<std::string> &args)
{
    std::string str;
    str = args[1].substr(1, std::string::npos);
    for (size_t i = 2; i < args.size(); i++)
    {
        str.push_back(' ');
        str.append(args[i]);
    }
    str.push_back('\n');
    return (str);
}
