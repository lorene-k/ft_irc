#include "Client.hpp"

// ******************************************************** COMMAND HANDLERS */
void Client::initCmdHandlers() {
    if (!_cmdHandlers.empty())
        return;
    _cmdHandlers["PASS"] = &Client::handlePass;
    _cmdHandlers["NICK"] = &Client::handleNick;
    _cmdHandlers["USER"] = &Client::handleUser;
    _cmdHandlers["JOIN"] = &Client::handleJoin;
    _cmdHandlers["PART"] = &Client::handlePart;
    _cmdHandlers["NAMES"] = &Client::handleNames;
    _cmdHandlers["PRIVMSG"] = &Client::handlePrivmsg;
    _cmdHandlers["QUIT"] = &Client::handleQuit;
    _cmdHandlers["INVITE"] = &Client::handleInvite;
    _cmdHandlers["KICK"] = &Client::handleKick;
    _cmdHandlers["TOPIC"] = &Client::handleTopic;
    _cmdHandlers["MODE"] = &Client::handleMode;
    _cmdHandlers["PING"] = &Client::handlePing;
    _cmdHandlers["CAP"] = &Client::handleCap;
    _cmdHandlers["WHO"] = &Client::handleWho;
}

// ********************************************************** CANONICAL FORM */
Client::Client() : _fd(-1), _hasPass(false), _isRegistered(false) {
    initCmdHandlers();
}

Client::Client(Client const &other) {
    if (this != &other) {
        _fd = other._fd;
        _nickname = other._nickname;
        _clientAddr = other._clientAddr;
        _addrLen = other._addrLen;
        _ipAdd = other._ipAdd;
        _hasPass = other._hasPass;
        _channels = other._channels;
        _cmdName = other._cmdName;
        _cmdArgs = other._cmdArgs;
        _cmdResponse = other._cmdResponse;
        _isRegistered = other._isRegistered;
        _realname = other._realname;
        _username = other._username;
        _usermask = other._usermask;
        _cmdHandlers = other._cmdHandlers;
    }
}

Client &Client::operator=(Client const & other) {
    if (this != &other) {
        _fd = other._fd;
        _nickname = other._nickname;
        _clientAddr = other._clientAddr;
        _addrLen = other._addrLen;
        _ipAdd = other._ipAdd;
        _hasPass = other._hasPass;
        _channels = other._channels;
        _cmdName = other._cmdName;
        _cmdArgs = other._cmdArgs;
        _cmdResponse = other._cmdResponse;
        _isRegistered = other._isRegistered;
        _realname = other._realname;
        _username = other._username;
        _usermask = other._usermask;
        _cmdHandlers = other._cmdHandlers;
    }
    return *this;
}

Client::~Client() {}

// ***************************************************************** GETTERS */
int Client::getFd() {
    return _fd;
}

size_t  Client::getCmdArgsSize() {
    return _cmdArgs.size();
}

std::string Client::getIpAdd() {
    return _ipAdd;
}

std::string Client::getName() {
    return _nickname;
}

struct sockaddr_in& Client::getAddr() {
    return _clientAddr;
}

socklen_t& Client::getAddrLen() {
    return _addrLen;
}

bool Client::getIfRegistered() {
    return _hasPass;
}

bool Client::getIfNamed() {
    if (_nickname.empty())
        return false;
    return true;
}

std::vector<std::string> const &Client::getArgs() const {
    return (_cmdArgs);
}

std::string Client::getResponse() const {
    return (_cmdResponse);
}

std::string Client::getUsername() const {
    return (_username);
}

std::string Client::getRealname() const {
    return (_realname);
}

std::string Client::getUsermask() const {
    return (_usermask);
}

// ***************************************************************** SETTERS */
void Client::setFd(int fd) {
    _fd = fd;
}

void Client::setnickname(std::string nickname) {
    _nickname = nickname;
}

void Client::setAddrLen(socklen_t len) {
    _addrLen = len;
}

void Client::setIpAdd(std::string ipAdd) {
    _ipAdd = ipAdd;
}

void Client::setIsRegistered() {
    _hasPass = true;
}

void Client::setResponse(std::string response) {
    _cmdResponse = response;
}