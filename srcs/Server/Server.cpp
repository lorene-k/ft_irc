#include "Server.hpp"

bool    Server::_signal = false;

// ********************************************************** CANONICAL FORM */
Server::Server() : _serverFd(-1) {}

Server::Server(Server const & other) {
    if (this != &other) {
        _port = other._port;
        _serverFd = other._serverFd;
        _server_addr = other._server_addr;
        _fds = other._fds;
        _clients = other._clients;
    }
}

Server & Server::operator=(Server const & other) {
    if (this != &other) {
        _port = other._port;
        _serverFd = other._serverFd;
        _server_addr = other._server_addr;
        _fds = other._fds;
        _clients = other._clients;
    }
    return *this;
}

Server::~Server() {
    for (size_t i = 0; i < _channels.size(); i++)
        delete _channels[i];
    for (size_t i = 0; i < _clients.size(); i++)
        delete _clients[i];
}

// ******************************************************* GETTERS & SETTERS */
int Server::getFd() const {
    return _serverFd;
}

int Server::getPort() const {
    return _port;
}

std::string     Server::getPassword() const {
    return _password;
}

size_t  Server::getClientsSize() const {
    return (_clients.size());
}

Channel *Server::getChannel(std::string channelName) const {
    for(size_t i = 0; i < _channels.size(); i++) {
        if (channelName == _channels[i]->getName())
            return (_channels[i]);
    }
    return (NULL);
}

void    Server::setFd(int fd) {
    _serverFd = fd;
}

void    Server::setPort(int port) {
    _port = port;
}

Client  *Server::getClientByNick(std::string nickname) const {
    for (size_t i = 0; i < _clients.size(); i++) {
        if (_clients[i]->getName() == nickname)
            return (_clients[i]);
    }
    return (NULL);
}