/*
** main.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/main.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Sun May 07 16:24:17 2017 Enguerrand Allamel
** Last update Mon May 22 16:17:00 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

int 	main(int ac, char **av)
{
  if (ac < 3)
    {
      std::cerr << "Usage : " << av[0] << " <Address> <Port>" << std::endl;
      return (1);
    }

  std::string       cmd;
  std::string       db = "dbname = indie user = indie password = aGF9fFdAdDHrwUYZ hostaddr = 127.0.0.1 port = 5432";
  bwsc::ServerCloud serverCloud(av[1], std::stoi(av[2]), db);

  if (serverCloud.start() == 1)
    return (1);
  while (std::getline(std::cin, cmd))
    {
      if (cmd == "exit" || cmd == "quit")
        break;
    }
  serverCloud.stop();
  return (0);
}
