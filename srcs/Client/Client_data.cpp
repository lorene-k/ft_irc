#include "Client.hpp"

// *********************************************************** DATA HANDLING */
void    Client::handleBuffer(ssize_t bytesRead, Server* server, char *buffer) {
    static std::string tmp;
    int nl = 0;

    for (ssize_t i = 0; i < bytesRead; i++) {
        if (buffer[i] == '\n')
            nl++;
    }
    tmp.append(buffer);
    if (nl == 0)
        return ;
    else if (nl == 1) {
        handleCmd(tmp, server);
        tmp.erase();
        return ;
    }
    std::vector<std::string> argVec = splitArgs(tmp, '\r');
    for (size_t i = 0; i < argVec.size() - 1; i++) {
        if (i != 0)
            argVec[i].erase(0, 1);
        handleCmd(argVec[i], server);
    }
    tmp.erase();
}

void    Client::dealWithData(Server* server, int fdIn) {
    char    buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(fdIn, buffer, BUFFER_SIZE - 1, 0);
    if (bytesRead < 0) {
        perror("recv failed");
        server->disconnectClient(_fd);
    }
    else if (bytesRead == 0) {
        std::cout << GREEN << "Client: " << _fd << " disconnected" << RESET << std::endl;
        handleQuit(server);
    }
    else
        handleBuffer(bytesRead, server, buffer);
}

void    Client::relayData(const char *msg, int fd) {
    ssize_t bytes_sent = send(fd, msg, strlen(msg), 0);
    if (bytes_sent == -1)
        perror("Send failed");
}

// ***************************************************************** PARSING */
bool Client::checkRegistered() {
    if (_cmdName == "CAP" || _isRegistered)
        return (true);
    if (!_hasPass && _cmdName != "PASS")
        return (false);
    if (_hasPass && _nickname.empty()
        && _cmdName != "NICK" && _cmdName != "PASS")
        return (false);
    if (_hasPass && !_nickname.empty() && _cmdName != "USER")
        return (false);
    return (true);
}

void Client::parseArgs(std::istringstream &ss) {
    std::string arg;
    while(ss >> arg)
        _cmdArgs.push_back(arg);
}

bool Client::parseCommand(std::string &name) {
    _cmdName = name;
    std::transform(_cmdName.begin(), _cmdName.end(), _cmdName.begin(), ::toupper);
    if (_cmdHandlers.find(_cmdName) != _cmdHandlers.end())
        return (true);
    if (_isRegistered)
        formatResponse(ERR_UNKNOWNCOMMAND, _nickname + " " + name);
    return (false);
}

bool Client::parseInput(std::string buf) {
    std::string name;
    std::istringstream ss(buf);

    ss >> name;
    _cmdArgs.clear();
    if (!parseCommand(name))
        return (false);
    parseArgs(ss);
    return (true);
}

void Client::handleCmd(std::string buf, Server* server) {
    if (parseInput(buf) && checkRegistered())
        (this->*(_cmdHandlers[_cmdName]))(server);
    else if (_cmdName.empty())
        return ;
    else if (!checkRegistered())
        formatResponse(ERR_NOTREGISTERED, SERVER);
}
