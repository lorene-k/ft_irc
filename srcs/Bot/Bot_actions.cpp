#include "Bot.hpp"

void Bot::handleKick(std::vector<std::string> args) {
    if (_connected && args[1] == "KICK"
        && std::find(_channels.begin(), _channels.end(), args[2]) != _channels.end()) {
        _channels.erase(std::remove(_channels.begin(), _channels.end(), args[2]), _channels.end());
        std::cout << GREEN << "Kicked from channel: " << args[2] << RESET << std::endl;
    }
}

void Bot::sendResponses(std::vector<std::string> args) {
    if (_connected && args[1] == "PRIVMSG") {
        std::string lastWord = args[args.size() - 1];
        std::transform(lastWord.begin(), lastWord.end(), lastWord.begin(), ::tolower);
        if (lastWord[0] == ':')
            lastWord = lastWord.erase(0, 1);
        if (_responses.find(lastWord) != _responses.end()) {
            std::string response = "PRIVMSG " + args[2] + " :" + _responses[lastWord] + "\r\n";
            send(_sockfd, response.c_str(), response.size(), 0);
        }
    }
}

void Bot::sendGreeting(std::vector<std::string> args) {
    if (_connected && args[2] == "ircbot" && args[args.size() - 1] == "list") {
        _channels.push_back(args[4]);
        std::string msg = "PRIVMSG " + args[4] + " :Salut les nazes !\r\n";
        send(_sockfd, msg.c_str(), msg.size(), 0);
    }
}

void Bot::joinChannel(std::vector<std::string> args) {
    if (_connected && args[1] == "INVITE") {
        std::string join = "JOIN " + args[3] + "\r\n";
        send(_sockfd, join.c_str(), join.size(), 0);
        std::cout << GREEN << "Joining channel: " << args[3] << RESET << std::endl;
    }
}

void Bot::checkConnected(std::string code) {
    if (!_connected && code == "001") {
        _connected = true;
        std::cout << GREEN << "Bot successfully connected!" << RESET << std::endl;
    }
}

void Bot::parseMsg(std::string buf) {
    std::vector<std::string> argVec;
    std::string arg;
    std::istringstream ss(buf);
    while(ss >> arg)
        argVec.push_back(arg);
    checkConnected(argVec[1]);
    joinChannel(argVec);
    sendGreeting(argVec);
    sendResponses(argVec);
    handleKick(argVec);
}
