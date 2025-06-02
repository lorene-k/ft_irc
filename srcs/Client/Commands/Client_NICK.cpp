#include "Client.hpp"

// ******************************************************************** NICK */
void Client::handleNick(Server* server) {
    if (_cmdArgs.size() < 1)
        formatResponse(ERR_NONICKNAMEGIVEN, (!_nickname.empty() ? _nickname : ""));
    else if (server->checkUsedNickname(_cmdArgs[0]) == true)
        formatResponse(ERR_NICKNAMEINUSE, _nickname + (!_nickname.empty() ? " " : "") + _cmdArgs[0]);
    else if (_cmdArgs[0][0] == '#' || _cmdArgs[0][0] == ':' || _cmdArgs[0][0] == '@')
        formatResponse(ERR_ERRONEUSNICKNAME, _nickname + (!_nickname.empty() ? " " : "") + _cmdArgs[0]);
    else
        _nickname = _cmdArgs[0];
}
