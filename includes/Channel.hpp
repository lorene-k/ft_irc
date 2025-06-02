#ifndef CHANNEL_HPP

# define CHANNEL_HPP

# include <iostream>
# include <vector>

class Client;

class Channel
{
    private:
        std::string         _name;
        std::string         _topic;
        std::vector<std::string>         _opNames;
        std::vector<Client*> _clients;
        std::vector<Client*> _invitedClients;
        std::string          _key;
        bool                _inviteOnly;
        bool                _topicRestriction;
        int                 _userLimit;
        std::string         _channelKey;
        
    public:
        Channel();
        Channel(std::string channelName);
        Channel(std::string channelName, bool inviteOnly);
        Channel(const Channel& other);
        Channel& operator=(Channel& other);
        ~Channel();

        std::string     getName();
        std::string     getKey();
        std::string     getTopic();
        std::string     getModes() const;
        bool            checkOpName(std::string clientName);
        bool            isInvite();
        bool            isTopicRestricted();
        int             getLimit();
        size_t          getClientsSize();
        std::vector<Client*> getClients();
        std::vector<std::string> getOpNames();
     
        bool            isClient(std::string clientName);
        bool            isInvited(Client* client);

        void            setInvite(char mode);
        void            setLimit(Client* client, char mode);
        void            setKey(std::string channelKey);
        void            clearKey();
        void            setTopic(std::string topic);
        void            setTopRestriction();
        void            unsetTopRestriction();
        
        bool            hasKey();
        bool            hasTop();
        std::string     getjoinedClients();
        void            eraseClientFromChannel(Client *client);
        void            addOperator(std::string opName);
        void            eraseOperator(std::string opName, Client *client);
        void            addClient(Client* client);
        bool            kickClient(std::string clientName, Client *client);
        void            talkToClients(std::string msg, Client* client);
        void            cmdRespToClients(std::string cmdName, std::string msg, std::string kickedClient, std::string clientName);
        void            sendInvite(Client *client);
};

#include "Client.hpp"

#endif