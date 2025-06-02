#include "Client.hpp"

// ******************************************************************* CHECK */
static bool controlOperator(std::string flag) {
    size_t op = 0;
    size_t i = 0;
    if (flag[0] != '+' && flag[0] != '-')
        return false;
    for (; i < flag.size(); i++) {
        if (flag[i] == '+' || flag[i] == '-')
            op++;
    }
    if (op > 2 || (flag[i] == '+' || flag[i] == '-')){
        return false;
    }
    return true;
}

bool Client::modeRequestBanList() {
    if (_cmdArgs[0][0] == '#' && _cmdArgs.size() == 2 && _cmdArgs[1] == "b") {
        formatResponse(RPL_ENDOFBANLIST, _nickname + " " + _cmdArgs[0]);
        return true;
    }
    return false;
}
bool Client::modeRequest(Server *server) {
    if (_cmdArgs.size() == 1) {
        Channel *channel = server->getChannel(_cmdArgs[0]);
        if (channel == NULL) {
            formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
            return true;
        }
        formatRPL(RPL_CHANNELMODEIS, _nickname + " " + _cmdArgs[0] +  " " + channel->getModes());
        return true;
    }
    return false;
}

bool Client::controlMode(Server* server) {
    if (_cmdArgs[0][0] != '#') {
        if (!server->checkUsedNickname(_cmdArgs[0]))
            formatResponse(ERR_NOSUCHNICK, _nickname);
        return false;
    }
    if (_cmdArgs.size() < 1) {
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " MODE");
        return false;
    }
    if (!checkChanErrors(_cmdArgs[0], server))
        return false;
    if (modeRequest(server) || modeRequestBanList())
        return false;
    if (!isOperator(_cmdArgs[0])) {
        formatResponse(ERR_CHANOPRIVSNEEDED, _cmdArgs[0]);
        return false;
    }
    if (_cmdArgs.size() > 1 && !controlOperator(_cmdArgs[1])) {
        formatResponse(ERR_UMODEUNKNOWNFLAG, _nickname + " " + _cmdArgs[1]);
        return false;
    }
    return true ;
}

static int countOpflag(std::string flag) {
    int opFlag = 0;

    for (size_t i = 0; i < flag.length(); i++) {
        if (flag[i] == '+' || flag[i] == '-')
            opFlag++;
    }
    return opFlag;
}

// ******************************************************************** EXEC */
void Client::doubleMode(Server* server) {
    std::vector<std::string> flags;
    if (_cmdArgs[1][0] == '+') {
        flags = splitArgs(_cmdArgs[1], '-');
        flags[1] = "-" + flags[1];
    }
    else {
        flags = splitArgs(_cmdArgs[1], '+');
        flags[1] = "+" + flags[1];
    }
    simpleMode(server, flags[0]);
    simpleMode(server, flags[1]);

}

void Client::simpleMode(Server* server, std::string flag) {
    char mode = '\0';
    if (flag[0] == '+')
        mode = '+';
    else if (flag[0] == '-')
        mode = '-';
    modeHandler(server, flag, mode);
}

void Client::modeHandler(Server* server, std::string flag, char mode) {
    Channel *channel = server->getChannel(_cmdArgs[0]);
    bool validParams = true;
    for (size_t i = 1; i < flag.length(); i++) {
        if (flag[i] == 't')
            server->modeChanTopic(mode, channel);
        else if (flag[i] == 'k')
            validParams = server->modeChanKey(this, mode, channel);
        else if (flag[i] == 'o')
            validParams =server->modeOperator(this, mode, channel);
        else if (flag[i] == 'i')
            server->modeInvite(mode, channel);
        else if (flag[i] == 'l')
            validParams = server->modeLimit(this, mode, channel);
        else
            formatResponse(ERR_UNKNOWNMODE, _nickname + " " + flag[i]);
    }
    if (!validParams && flag.size() == 2)
        return ;
    if (!(flag[1] == 'o' && flag.size() == 2))
        formatRPL(RPL_CHANNELMODEIS, _usermask + " " + _cmdArgs[0] +  " " + channel->getModes());
    else
        relayData(_cmdResponse.c_str(), _fd);
    channel->talkToClients(_cmdResponse, this);
}

void Client::handleMode(Server* server) {
    if (!controlMode(server))
        return ;
    else if (countOpflag(_cmdArgs[1]) == 1)
        simpleMode(server, _cmdArgs[1]);
    else if (countOpflag(_cmdArgs[1]) == 2)
        doubleMode(server);
}

