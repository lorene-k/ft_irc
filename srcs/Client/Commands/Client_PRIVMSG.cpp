#include "Client.hpp"

// ***************************************************************** PRIVMSG */
void    Client::handlePrivmsg(Server* server) {
    if (_cmdArgs.size() < 1)
        formatRPL(ERR_NORECIPIENT.first, _nickname + " " + ERR_NORECIPIENT.second + " (PRIVMSG)");
    else if (_cmdArgs.size() < 2 || _cmdArgs[1][0] != ':')
        formatResponse(ERR_NOTEXTTOSEND, _nickname);
    else {
        std::vector<std::string> targets = splitArgs(_cmdArgs[0], ',');
        std::string msg = joinArgs(_cmdArgs);
        std::string trailingArgs = msg;
        for (size_t i = 0; i < targets.size(); i++) {
            if (targets[i][0] == '#') {
                if (checkIfInChannel(targets[i])) {
                    msg = ":" + _usermask + " PRIVMSG " + targets[i] + " :" + msg; 
                    server->sendToChannel(targets[i], msg, this);
                } else
                    formatResponse(ERR_CANNOTSENDTOCHAN, _nickname + " " + targets[i]);
            } else {
                msg = ":" + _usermask + " PRIVMSG " + targets[i] + " :" + msg;
                server->sendToClient(targets[i], msg, this);
                if (trailingArgs.substr(0, 4) == "DCC ")
                    relayData(msg.c_str(), _fd);
            }
        }
    }
}