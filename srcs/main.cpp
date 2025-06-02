#include "Server.hpp"

int   main (int ac, char **av) {
   Server serv;

   if (ac != 3) {
      std::cout << "Usage : ./ircserv <port> <password>" << std::endl;
      return (1);
   }
   try {
      signal(SIGINT, Server::initSignal);
      signal(SIGQUIT, Server::initSignal);
      serv.initServ(av);
      serv.runServ();
      serv.closeFds();
   }
   catch (const std::exception& e) {
      serv.closeFds();
      std::cerr << e.what() << std::endl;
   }
   return (0);
}