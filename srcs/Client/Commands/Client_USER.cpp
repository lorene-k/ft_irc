#include "Client.hpp"

// ******************************************************************** USER */
std::string Client::collectTrailingMsg(std::vector<std::string> args) {
    size_t i = 0;
    std::string msg;
    while (i < args.size() && args[i][0] != ':')
        i++;
    if (i == args.size())
        return ("");
    args[i].erase(0, 1);
    while (i < args.size()) {
        if (!msg.empty())
            msg += ' ';
        msg += args[i++];
    }
    return (msg);
}

void Client::handleUser(Server* server) {
    if (_cmdArgs.size() < 4)
        formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
    else if (_isRegistered == true)
        formatResponse(ERR_ALREADYREGISTRED, _nickname);
    else if (!_isRegistered) {
        _username = _cmdArgs[0];
        _realname = collectTrailingMsg(_cmdArgs);
        if (_realname.empty()) {
            formatResponse(ERR_NEEDMOREPARAMS, _nickname + " " + _cmdArgs[0]);
            return;
        }
        if (server->checkUsedUsername(_username)) {
            _username = _nickname;
            _realname = _nickname;
        }
        _usermask = _nickname + "!" + _username + "@localhost";
        _isRegistered = true;
        formatResponse(RPL_WELCOME, _nickname);
        _cmdResponse = ":" + _usermask + " MODE +i\r\n";
        relayData(_cmdResponse.c_str(), _fd);
    }
    (void)server;
}
