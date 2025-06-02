#include "Bot.hpp"

void Bot::quitServ() {
    std::string quitMsg = "QUIT :Bot leaving\r\n";
    send(_sockfd, quitMsg.c_str(), quitMsg.size(), 0);
    std::cout << RED << "Bot disconnected" << RESET << std::endl;
    close(_sockfd);
}

void Bot::listenLoop() {
    char buffer[1024];
    while (!_sigstop) {
        if (poll(&_servPollfd, 1, 100) < 0 && !_sigstop)
                perror("poll()");
        else if (_servPollfd.revents & POLLIN && !_sigstop) {
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesRead = recv(_sockfd, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead <= 0)
                break;
            parseMsg(buffer);
        }
    }
    quitServ();
}

void Bot::authenticate() {
    std::string pass = "PASS " + _password + "\r\n";
    std::string nick = "NICK " + _nickname + "\r\n";
    std::string user = "USER " + _username + " 0 * :" + _realname + "\r\n";
    send(_sockfd, pass.c_str(), pass.size(), 0);
    send(_sockfd, nick.c_str(), nick.size(), 0);
    send(_sockfd, user.c_str(), user.size(), 0);
}

bool Bot::connectToServ() {
    struct sockaddr_in serverAddr;
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0)
        return (perror("socket()"), false);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(_sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(_sockfd);
        return (perror("connect()"), false);
    }
    if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0)  {
        close(_sockfd);
        return (perror("fcntl()"), false);
    }
    _servPollfd.fd = _sockfd;
    _servPollfd.events = POLLIN;
    _servPollfd.revents = 0;
    return (true);
}

void Bot::runBot() {
    if (!connectToServ())
        exit(1);
    authenticate();
    listenLoop();
}
