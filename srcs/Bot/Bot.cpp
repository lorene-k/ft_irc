#include "Bot.hpp"

Bot::Bot(int port, std::string nickname, std::string password) :
    _connected(false), _sockfd(-1), _port(port),
    _nickname(nickname), _username(nickname), _realname(nickname), _password(password) {
        _responses["cimer"] = "albert";
        _responses["cool"] = "raoul";
        _responses["santé"] = "mais pas des pieds";
        _responses["nickel"] = "michel";
        _responses["rien"] = "lucien";
        _responses["roule"] = "ma poule";
        _responses["plus"] = "dans le bus";
        _responses["parti"] = "mon kiki";
        _responses["bientot"] = "dans le metro";
        _responses["l'aise"] = "blaise";
    }

Bot::~Bot() {}