//
// TrackerEvent.hpp for trackerEvent in /home/herbau_a/rendu/cpp_indie_studio/ServerGame/Bin/Includes/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu Jun 15 04:00:28 2017 JSX
// Last update Thu Jun 15 04:08:34 2017 JSX
//

#ifndef TRACKER_EVENT_HPP
#define TRACKER_EVENT_HPP

# include <sstream>

# include <chrono>
​
std::string  irc::Utils::returnCurrentDate(bool date, bool t)
{
 auto now = std::chrono::system_clock::now();
 auto in_time_t = std::chrono::system_clock::to_time_t(now);
 std::stringstream ss;
​
 if (date)
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
 if (t)
 {
  if (date)
   ss << " ";
  ss << std::put_time(std::localtime(&in_time_t), "%X");
 }
 return (ss.str());
}

namespace bwsg {
  template <typename T>
  class TrackerEvent {
  private:
    T     _data;


  public:
    TrackerEvent (T);
    virtual ~TrackerEvent ();
  };
} /* bwsg */

#endif /* end of include guard: TRACKER_EVENT_HPP */
