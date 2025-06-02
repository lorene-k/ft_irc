#include "Client.hpp"

// ******************************************************************** QUIT */
void    Client::handleQuit(Server* server) {
    if (_cmdArgs[0][0] == ':') {
        std::string msg = collectTrailingMsg(_cmdArgs);
        _cmdResponse = ":" + _usermask + " QUIT :Quit: " + msg + "\r\n";
    } else
        _cmdResponse = ":" + _usermask + " QUIT :Quit: leaving\r\n";
    for (size_t i = 0; i < _channels.size(); i++) {
        _channels[i]->talkToClients(_cmdResponse, this);
    }
    std::vector<Channel*> channelsCopy = _channels;
    for (size_t i = 0; i < channelsCopy.size(); i++) {
        leaveChannel(channelsCopy[i], server);
    }
    server->disconnectClient(_fd);
}
