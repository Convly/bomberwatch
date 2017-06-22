//
// TrackerManager.hpp for trackermanager in /home/herbau_a/rendu/cpp_indie_studio/ServerGame/Bin/Includes/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Jun 15 03:51:01 2017 JSX
// Last update Thu Jun 15 04:10:24 2017 JSX
//

#ifndef TRACKER_MANAGER_HPP
#define TRACKER_MANAGER_HPP

#include <iostream>
#include <unordered_map>
#include "Tracker.hpp"

namespace bwsg {
  class TrackerManager {
  private:
    template <typename T>
    std::unordered_map<std::string, bwsg::Tracker<T>>    _trackers;

  public:
    TrackerManager ();
    virtual ~TrackerManager ();

  public:
    template <typename T>
    bwsg:Tracker&   registerTracker<T>(const std::string&);
  };
} /* bwsg */

#endif /* end of include guard: TRACKER_MANAGER_HPP */
