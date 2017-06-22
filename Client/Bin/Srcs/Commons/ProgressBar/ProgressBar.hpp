//
// ProgressBar.hpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Commons/ProgressBar/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Thu Jun 15 21:24:07 2017 Maxime Cauvin
// Last update Fri Jun 16 02:03:40 2017 Maxime Cauvin
//

#ifndef PROGRESSBAR_HPP_
#define  PROGRESSBAR_HPP_

# include "Kirrlicht.hpp"

class ProgressBar : public kirr::Gui::IGUIElement
{
   kirr::f32 _total; //Dimension (X) of the bar, to calculate relative percentage.
   kirr::Core::rect<kirr::s32> _bar; //Dimension of the bar
   kirr::Core::rect<kirr::s32> _position; //Bar
   kirr::Core::rect<kirr::s32> _border; //Border
   kirr::Core::rect<kirr::s32> _tofill; //Percentage indicator
   kirr::Core::rect<kirr::s32> _empty; //"Empty" indicator
   kirr::f32 _progress;

   kirr::Video::SColor _fillcolor;
   kirr::Video::SColor _emptycolor;
   kirr::Video::SColor _bordercolor;
   kirr::Video::IVideoDriver *_driver;

public:

   ProgressBar(kirr::Gui::IGUIEnvironment *gui, kirr::Core::rect<kirr::s32> const& rect, kirr::s32 id = -1, kirr::Gui::IGUIElement *parent = 0);
   virtual ~ProgressBar();

   bool addBorder(kirr::s32 size, kirr::Video::SColor const& color = kirr::Video::SColor(255, 0, 0, 0));

   bool setProgress(kirr::f32 progress);
   bool setColors(kirr::Video::SColor const& progress = kirr::Video::SColor(255, 255, 255, 255), kirr::Video::SColor const& filling = kirr::Video::SColor(255, 0, 0, 0));

   kirr::f32 getProgress() const;

   virtual void draw();
};

#endif
