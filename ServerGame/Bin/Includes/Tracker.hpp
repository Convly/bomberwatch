//
// Tracker.hpp for tracker in /home/herbau_a/rendu/cpp_indie_studio/ServerGame/Bin/Includes/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Jun 15 03:58:00 2017 JSX
// Last update Thu Jun 15 04:00:47 2017 JSX
//

#ifndef TRACKER_HPP_
#define TRACKER_HPP_

#include <vector>
#include "TrackerEvent.hpp"

namespace bwsg {
  template <typename T>
  class Tracker {
  private:
    std::string                          _name;
    std::vector<bwsg::TrackerEvent<T>>   _events;

  public:
    Tracker (const std::string&);
    virtual ~Tracker ();
  };
} /* bwsg */

#endif /* end of include guard: TRACKER_HPP_ */
