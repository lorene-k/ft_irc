#ifndef BOT_HPP

# define BOT_HPP

/* ------------------------------------------------------------------- MACROS */
#define RED     "\e[1;31m"
#define GREEN   "\e[1;32m"
#define RESET   "\033[0m"

/* ---------------------------------------------------------------- LIBRARIES */
# include <iostream>
# include <sstream>
# include <cstring>
# include <vector>
# include <map>
# include <algorithm>
# include <string>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <csignal>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>

/* -------------------------------------------------------------------- CLASS */
class Bot
{
private:
        bool                                    _connected;
        int                                     _sockfd;
        int                                     _port;
        pollfd                                  _servPollfd;
        std::string                             _nickname;
        std::string                             _username;
        std::string                             _realname;
        std::string                             _password;
        std::vector<std::string>                _channels;
        static volatile sig_atomic_t            _sigstop;
        std::map<std::string, std::string>      _responses;
        bool                                    connectToServ();
        void                                    authenticate();
        void                                    listenLoop();
        void                                    parseMsg(std::string buf);
        void                                    checkConnected(std::string code);
        void                                    joinChannel(std::vector<std::string> args);
        void                                    sendGreeting(std::vector<std::string> args);
        void                                    sendResponses(std::vector<std::string> args);
        void                                    handleKick(std::vector<std::string> args);

public:
        Bot(int port, std::string nickname, std::string password);
        ~Bot();
        static void                             sigHandler(int);
        void                                    runBot();
        void                                    quitServ();
};

#endif