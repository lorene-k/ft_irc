#include "Server.hpp"

// ************************************************************* INIT SERVER */
int     Server::errInitServ(const char * errMsg) {
    perror(errMsg);
    if (_serverFd != -1) {
        close(_serverFd);
        _serverFd = -1;
    }
    return 1;
}

void    Server::addToPoll() {
    pollfd server_pollfd;
    server_pollfd.fd = _serverFd;
    server_pollfd.events = POLLIN;                                                       // Requested events (POLLIN = there is data to read)
    server_pollfd.revents = 0;                                                           // Returned events 
    _fds.push_back(server_pollfd);
}

void    Server::initServAddr() {
    memset(&_server_addr, 0, sizeof(_server_addr));
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_addr.s_addr = INADDR_ANY;
    _server_addr.sin_port = htons(_port);
}

static int checkPort(char *av1)
{
    std::string portStr = av1;
    for (size_t i = 0; i < portStr.length(); i++)
    {
        if (!std::isdigit(portStr[i]) || i > 5)
            throw (std::runtime_error(INVALID_PORT));
    }
    int port = atoi(av1);
    if (port < 1024 || port > 65535)
        throw (std::runtime_error(INVALID_PORT));
    return (port);
}

int    Server::initServ(char **av) {
    _port = checkPort(av[1]);
    _password = av[2];
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);                                        // Creating server fd
    if (_serverFd < 0)
        return (errInitServ("Couldn't create socket: server\n"));
    int opt = 1;
    if (setsockopt(_serverFd, SOCK_STREAM, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("setsockopt failed\n");
    initServAddr();
    if (bind(_serverFd, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) < 0)     // Binding both address and port
        return (errInitServ("Couldn't bind: server\n"));
    if (listen(_serverFd, MAX_CLIENTS) < 0)                                             // Listen for new connections
        return (errInitServ("Couldn't listen: server\n"));
    std::cout << GREEN << "Server listening on port: " << _port << RESET << std::endl;
    addToPoll();
    return 0;
}

