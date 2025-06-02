#ifndef SERVER_HPP
# define SERVER_HPP

# define INVALID_PORT "Error : invalid port number"

# include "Client.hpp"
# include "Channel.hpp"
# include <stdio.h>
# include <string.h>

class Server {
    private:
        int                     _port;
        int                     _serverFd;
        struct sockaddr_in      _server_addr;
        std::vector<Client*>    _clients;
        std::vector<Channel*>   _channels;
        std::vector<pollfd>     _fds;
        static bool             _signal;
        std::string             _password;

    public:
    // ****************************************************** Canonical form */
        Server();
        Server(Server const & other);
        Server& operator=(Server const & other);
        ~Server();
        
    // *************************************************** Getters & setters */
        int                 getFd() const;
        int                 getPort() const;
        size_t              getClientsSize() const;
        std::string         getPassword() const;
        Channel             *getChannel(std::string channelName) const;
        Client*             getClientByNick(std::string nickname) const;
        void                setFd(int fd);
        void                setPort(int port);

    // *************************************************************** Debug */
        void                printRegisteredClients();
    
    // ************************************************************* Checker */
        bool                checkIfNamed(Client &client) const;
        bool                checkUsedNickname(std::string &nickName) const;  
        bool                checkUsedUsername(std::string &username) const;
    
    // *************************************************** Server init & run */
        int                 errInitServ(const char * errMsg);
        void                addToPoll();
        void                initServAddr();
        int                 initServ(char **av);
        void                runServ();
    
    // ****************************************** Connect/disconnect clients */
        void                disconnectClient(int fd);
        void                addClientToPoll(Client *newClient, int fd);
        void                connectNewClient();
        
    // ****************************************** Close fds & handle signals */
        void                closeFds();
        static void         initSignal(int signum);

    // ************************************************************ Channels */
        std::string         getChanTopic(std::string channelName);
        void                setChanTopic(std::string channelName, std::string topic);
        bool                hasTopicRestriction(std::string channelName);
        bool                chanHasTopic(std::string channelName);
        bool                controlKey(Client* client, Channel* channel, size_t index, std::vector<std::string> keys);
        bool                controlJoin(Client* client, Channel* channel, size_t index, std::vector<std::string> keys);
        void                createChannel(std::string channelName, Client* client, size_t index, std::vector<std::string> keys);
        bool                joinChannel(std::string channelName, Client* client, size_t index, std::vector<std::string> keys);
        void                createOrJoinChannel(std::string channelName, Client* client, size_t i, std::vector<std::string> keys);
        bool                isTargetInChan(std::string channelName, std::string targetName);
        bool                doesChanExist(std::string channelName);
        void                inviteClient(std::string issuer, std::string clientName, std::string channelName);
        
    // ******************************************************* Channel modes */
        void                modeChanTopic(char mode, Channel *channel);
        void                modeInvite(char mode, Channel *channel);
        bool                modeLimit(Client* client, char mode, Channel *channel);
        bool                modeOperator(Client* client, char mode, Channel *channel);
        bool                modeChanKey(Client* client, char mode, Channel *channel);

    // ************************************************************ Send msg */
        void                sendToClient(std::string target, std::string msg, Client* client);
        void                sendToChannel(std::string target, std::string msg, Client* client);
    
    // *************************************************************** Utils */
        void                displayClients(std::string channelName, Client *client);
        void                displayChannels(Client *client);
        void                handleEmptyChannel(Channel *channel, Client *client);
};

#endif