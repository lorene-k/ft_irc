#include "Client.hpp"

// ******************************************************************** PASS */
void Client::handlePass(Server* server) {
    if (_cmdArgs.size() < 1)
        formatResponse(ERR_NEEDMOREPARAMS, (!_nickname.empty() ? _nickname + " " : "") + "PASS");
    else if (_hasPass == true && !_nickname.empty())
        formatResponse(ERR_ALREADYREGISTRED, _nickname);
    else if (_hasPass == false && _cmdArgs[0] == server->getPassword())
        _hasPass = true;
    else if (_cmdArgs[0] != server->getPassword()) {   
        _hasPass = false;
        _cmdResponse = std::string(":ircserv ") + ERR_PASSWDMISMATCH.first + " " + ERR_PASSWDMISMATCH.second + "\r\n";
        relayData(_cmdResponse.c_str(), _fd);
    }
}