#ifndef CLIENT_RESPONSES_HPP
# define CLIENT_RESPONSES_HPP

/* --------------------------------------------------------------- RPL CODES */
# define RPL_WELCOME            std::make_pair("001", ":Welcome to My IRC Server")
# define RPL_YOUREOPER          std::make_pair("381", ":You are now an IRC operator")
# define RPL_NOTOPIC            std::make_pair("331", ":No topic is set")
# define RPL_ENDOFNAMES         std::make_pair("366", ":End of /NAMES list")
# define RPL_ENDOFWHO           std::make_pair("315", ":End of WHO list")
# define RPL_ENDOFBANLIST       std::make_pair("368", ":End of channel ban list")
# define RPL_TOPIC              "332"
# define RPL_TOPICWHOTIME       "333"
# define RPL_INVITING           "346"
# define RPL_NAMREPLY           "353"
# define RPL_CHANNELMODEIS      "324"
# define RPL_WHOREPLY           "352"

/* ------------------------------------------------------------- ERROR CODES */
# define ERR_UNKNOWNCOMMAND     std::make_pair("421", ":Unknown command")
# define ERR_NOTREGISTERED      std::make_pair("451", ":You have not registered")
# define ERR_NEEDMOREPARAMS     std::make_pair("461", ":Not enough parameters")
# define ERR_ALREADYREGISTRED   std::make_pair("462", ":You may not reregister")
# define ERR_PASSWDMISMATCH     std::make_pair("464", ":Password incorrect")
# define ERR_NONICKNAMEGIVEN    std::make_pair("431", ":No nickname given")
# define ERR_ERRONEUSNICKNAME   std::make_pair("432", ":Erroneus nickname")
# define ERR_NICKNAMEINUSE      std::make_pair("433", ":Nickname is already in use")
# define ERR_PASSWDMISMATCH     std::make_pair("464", ":Password incorrect")
# define ERR_USERNOTINCHANNEL   std::make_pair("441", ":They aren't on that channel")
# define ERR_NOSUCHCHANNEL      std::make_pair("403", ":No such channel")
# define ERR_NOTONCHANNEL       std::make_pair("442", ":You're not on that channel")
# define ERR_BADCHANMASK        std::make_pair("476", ":Bad Channel Mask")
# define ERR_CHANOPRIVSNEEDED   std::make_pair("482", ":You're not channel operator")
# define ERR_CHANNELISFULL      std::make_pair("471", ":Cannot join channel (+l)")
# define ERR_INVITEONLYCHAN     std::make_pair("473", ":Cannot join channel (+i)")
# define ERR_BADCHANNELKEY      std::make_pair("475", ":Cannot join channel (+k)")
# define ERR_NOSUCHNICK         std::make_pair("401", ":No such nick/channel")
# define ERR_CANNOTSENDTOCHAN   std::make_pair("404", ":Cannot send to channel")
# define ERR_NORECIPIENT        std::make_pair("411", ":No recipient given")
# define ERR_NOTEXTTOSEND       std::make_pair("412", ":No text to send")
# define ERR_USERONCHANNEL      std::make_pair("443", " :is already on channel")
# define ERR_UNKNOWNMODE        std::make_pair("472", " :is unknown mode char to me")
# define ERR_UMODEUNKNOWNFLAG   std::make_pair("501", " :Unknown MODE flag")

#endif