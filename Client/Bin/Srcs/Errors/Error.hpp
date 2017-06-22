//
// Error.hpp for Errors exception in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Errors/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Sat May  6 01:21:38 2017 jsx
// Last update Sat May  6 01:22:23 2017 jsx
//

#ifndef ERROR_HPP
# define ERROR_HPP

#include <string>
#include <exception>

namespace indie {
  class Error: public std::exception
  {
  public:
    Error(const std::string& msg = "") throw() : _msg(msg) {}

    virtual const char* what() const throw() {
      return (_msg.c_str());
    }

    virtual ~Error() throw(){}

  private:
    std::string _msg;
  };
} /* indie */

#endif
