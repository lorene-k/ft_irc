#ifndef CLIENT_HPP

# define CLIENT_HPP

/* ------------------------------------------------------------------- MACROS */
#define RED     "\e[1;31m"
#define WHITE   "\e[0;37m"
#define GREEN   "\e[1;32m"
#define YELLOW  "\e[1;33m"
#define BLUE  	"\033[0;34m"
#define RESET   "\033[0m"
# define ORANGE "\033[0;38;5;208m"
# define BLUE   "\033[0;34m"
# define CYAN   "\033[0;36m"
# define PURPLE "\033[0;35m"
# define MAUVE  "\033[38;5;177m"
# define SERVER "ircserv"
# define BUFFER_SIZE 1024
# define MAX_CLIENTS 100

/* ---------------------------------------------------------------- LIBRARIES */
# include <stdio.h>
# include <iostream>
# include <vector>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <csignal>
# include <sstream>
# include <string>
# include <cstdlib>
# include <errno.h>
# include <map>
# include <algorithm>

# include "Channel.hpp"
# include "Server.hpp"
# include "Client_responses.hpp"

/* -------------------------------------------------------------------- CLASS */
class   Server;

class   Client {
    private:
        int                             _fd;
        std::string                     _nickname;
        struct sockaddr_in              _clientAddr;
        socklen_t                       _addrLen;
        std::string                     _ipAdd;
        bool                            _hasPass;
        std::vector<Channel*>           _channels;
        std::string                     _cmdName;
        std::vector<std::string>        _cmdArgs;
        std::string                     _cmdResponse;
        bool                            _isRegistered;
        std::string                     _username;
        std::string                     _realname;
        std::string                     _usermask;
        // ************************************************ Command Handlers */
        typedef void (Client::*cmdHandler)(Server *);
        std::map<std::string, cmdHandler> _cmdHandlers;
        void                            initCmdHandlers();

    public:
        // ************************************************** Canonical form */
        Client();
        Client(Client const & other);
        Client & operator=(Client const & other);
        ~Client();
        
        // ********************************************************* Getters */
        int                 getFd();
        size_t              getCmdArgsSize();
        std::string         getIpAdd();
        std::string         getName();
        struct sockaddr_in& getAddr();
        socklen_t&          getAddrLen();
        bool                getIfRegistered();
        bool                getIfNamed();
        std::vector<std::string> const &getArgs() const;
        bool                isTargetInChan(std::string channelName, std::string targetName);
        std::string         getResponse() const;
        std::string         getUsername() const;
        std::string         getRealname() const;
        std::string         getUsermask() const;
        
        // ********************************************************* Setters */
        void                setFd(int fd);
        void                setnickname(std::string nickname);
        void                setAddrLen(socklen_t len);
        void                setIpAdd(std::string ipAdd);
        void                setIsRegistered();
        void                setResponse(std::string response);

        // *************************************************** Data handling */
        void                handleBuffer(ssize_t bytesRead, Server* server, char *buffer);
        void                dealWithData(Server* server, int fdIn);
        void                relayData(const char *msg, int fd);
        
        // ********************************************************* Parsing */
        bool                parseInput(std::string buf);
        bool                parseCommand(std::string &name);
        void                parseArgs(std::istringstream &ss);
        bool                checkRegistered();
        bool                checkIfInChannel(std::string channelName);
        
        // ******************************************************** Commands */
        void                handleCmd(std::string buf, Server* server);
        void                handlePass(Server* server);
        bool                controlTopic(Server* server);
        void                handleTopic(Server* server);
        void                handleNick(Server* server);
        void                handleJoin(Server* server);
        void                handlePart(Server* server);
        bool                controlKick(Server* server);
        void                handleKick(Server* server);
        void                handlePrivmsg(Server* server);
        void                handleNames(Server* server);
        bool                controlInvite(Server* server, Channel *channel);
        void                handleInvite(Server* server);
        bool                controlFlag(std::string flag);
        
        bool                modeRequestBanList();
        bool                modeRequest(Server *server);
        bool                controlMode(Server* server);
        void                simpleMode(Server* server, std::string flag);
        void                doubleMode(Server* server);
        void                modeHandler(Server* server, std::string flag, char mode); 
        
        void                handleMode(Server* server);
        void                handleQuit(Server* server);
        void                handlePing(Server* server);
        void                handleUser(Server* server);
        void                handleCap(Server* server);
        void                handleWho(Server* server);
        
        // *********************************************************** Utils */
        std::vector<std::string> splitArgs(std::string args, char delimiter);
        std::string         joinArgs(std::vector<std::string> &args);
        std::string         collectTrailingMsg(std::vector<std::string> args);

        // ******************************************************** Channels */
        bool                isOperator(std::string channelName);
        void                addChannelToClient(Channel *channel);
        void                eraseChannelFromClient(Channel *channel);
        bool                checkChanErrors(std::string const &channel, Server* server);
        void                removeFromChannel(Channel *channel);
        void                leaveChannel(Channel *channel, Server *server);

        // ******************************************************* RPL utils */
        void                sendJoinRPL(Channel *channel, Server *server);
        void                formatRPL(std::string code, std::string msg);
        void                formatResponse(std::pair<std::string, std::string>, std::string varName);
        void                formatCmdMsg(std::string cmdName, std::string msg, std::string nick = "");
        void                sendKickRPL(Channel *channel, Client *kicker);
};

#endif