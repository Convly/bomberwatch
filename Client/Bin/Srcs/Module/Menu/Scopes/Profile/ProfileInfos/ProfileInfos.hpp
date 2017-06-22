//
// ProfileInfos.hpp for profileInfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Profile/ProfileInfos/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu May 11 04:00:02 2017 JSX
// Last update Thu Jun  1 02:05:48 2017 JSX
//

#ifndef PROFILE_INFOS_INDIE_STUDIO_HPP_
#define PROFILE_INFOS_INDIE_STUDIO_HPP_

#include <string>

namespace indie {
  namespace module {
    class Profile;
    class ProfileInfos {
    private:
      indie::module::Profile&   _profile;
      int                       _playerId;
      std::string               _pseudo;
      int                       _level;
      int                       _playedTime;
      std::string               _registrationDate;

    public:
      ProfileInfos (const int, indie::module::Profile &);
      ProfileInfos(const int, const std::string &, const int, const int, const std::string &, indie::module::Profile &);
      virtual ~ProfileInfos ();
      indie::module::ProfileInfos & operator=(const indie::module::ProfileInfos &);

    public:
      int                  getPlayerId() const;
      const std::string &  getPseudo() const;
      int                  getLevel() const;
      int                  getTimePlayed() const;
      const std::string &  getRegistrationDate() const;

    public:
      void                  setPlayerId(const int);
      void                  setPseudo(const std::string &);
      void                  setLevel(const int);
      void                  setTimePlayed(const int);
      void                  setRegistrationDate(const std::string &);
    };
  } /* module */
} /* indie */

#endif /* end of include guard: PROFILE_INFOS_INDIE_STUDIO_HPP_ */
