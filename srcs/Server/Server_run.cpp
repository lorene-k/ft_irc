#include "Server.hpp"

// ************************************************************* RUN PROGRAM */
void    Server::runServ() {
    while (Server::_signal == false) {
        if((poll(&_fds[0],_fds.size(), -1) == -1) && Server::_signal == false) {
            perror("poll count");
            break;
        }
        for (size_t i = 0; i < _fds.size(); i++){
            if (_fds[i].revents & POLLIN) {
                if (_fds[i].fd == _serverFd)
                    connectNewClient();
                else
                    _clients[i - 1]->dealWithData(this, _fds[i].fd);
            }
        }
    }
}

// ********************************************** CONNECT/DISCONNECT CLIENTS */
void    Server::disconnectClient(int fd) {
    for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++) {
        if (it->fd == fd) {
            _fds.erase(it);
            break ;
        }
    }
    for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
        if ((*it)->getFd() == fd) {
            delete *it;
            _clients.erase(it);
            break;
        }
    }
    close(fd);
}

void    Server::addClientToPoll(Client *newClient, int fd) {
    pollfd clientPollFd;
    clientPollFd.fd = fd;
    clientPollFd.events = POLLIN | POLLOUT;
    clientPollFd.revents = 0;

    _fds.push_back(clientPollFd);
    _clients.push_back(newClient);
}

void    Server::connectNewClient() {
    Client *newClient = new Client();
    socklen_t len = sizeof(newClient->getAddr());
    
    newClient->setAddrLen(len);
    int fd = accept(_serverFd, (struct sockaddr*)&newClient->getAddr(), &newClient->getAddrLen());
    newClient->setFd(fd);
    if (fd < 0)
        perror("accept() failed");
    else
        std::cout << GREEN << "New client connected\n" << RESET << std::endl;
    addClientToPoll(newClient, fd);
}

// ********************************************** CLOSE FDS & HANDLE SIGNALS */
void    Server::closeFds() {
    for (size_t i = 0; i < _clients.size(); i++) {
        // std::cout << RED << "Closing client fd n: " << i << RESET << std::endl;
        close(_clients[i]->getFd());
    }
    if (_serverFd != -1) {
        // std::cout << RED << "Closing server fd" << RESET << std::endl;
        close(_serverFd);
    }
}

void    Server::initSignal(int signum) {
    Server::_signal = true;
    (void)signum;
}
