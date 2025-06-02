#include "Bot.hpp"

volatile sig_atomic_t Bot::_sigstop = 0;

void Bot::sigHandler(int) {
    _sigstop = 1;
}

int   main (int ac, char **av) {
   if (ac != 3) {
        std::cout << "Usage : ./ircbot <port> <password>" << std::endl;
        return (1);
    }
    signal(SIGINT, Bot::sigHandler);
    signal(SIGQUIT, Bot::sigHandler);
    Bot bot(atoi(av[1]), "ircbot", av[2]);
    bot.runBot();
    return (0);
}