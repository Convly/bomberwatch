//
// ProgressBar.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Commons/ProgressBar/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Thu Jun 15 21:24:05 2017 Maxime Cauvin
// Last update Fri Jun 16 02:04:26 2017 Maxime Cauvin
//

#include "ProgressBar.hpp"

ProgressBar::ProgressBar(kirr::Gui::IGUIEnvironment *gui, kirr::Core::rect<kirr::s32> const& rect, kirr::s32 id, kirr::Gui::IGUIElement *parent)
: IGUIElement(kirr::Gui::EGUIET_ELEMENT, gui, parent, id, rect),
  _total(rect.LowerRightCorner.X - rect.UpperLeftCorner.X),
  _bar(rect),
  _border(_bar),
  _driver(gui->getVideoDriver())
{
   if (!parent)
     gui->getRootGUIElement()->addChild(this);
   this->setColors();
   this->setProgress(0);
}

ProgressBar::~ProgressBar() {}

bool ProgressBar::setColors(kirr::Video::SColor const& progress, kirr::Video::SColor const& filling)
{
  this->_fillcolor = progress;
  this->_emptycolor = filling;
  return (true);
}

bool ProgressBar::addBorder(kirr::s32 size, kirr::Video::SColor const& color)
{
  this->_bordercolor = color;
  this->_border = this->_bar;
  this->_border.UpperLeftCorner.X -= size;
  this->_border.UpperLeftCorner.Y -= size;
  this->_border.LowerRightCorner.X += size;
  this->_border.LowerRightCorner.Y += size;
  return (true);
}

bool ProgressBar::setProgress(kirr::f32 progress)
{
  kirr::f32 xpercentage;

  if (progress <= 100)
  {
    this->_progress = progress;
    xpercentage = progress * this->_total / 100.0f;
    this->_tofill.UpperLeftCorner.set(this->_bar.UpperLeftCorner.X, this->_bar.UpperLeftCorner.Y);
    this->_tofill.LowerRightCorner.set(this->_bar.UpperLeftCorner.X + xpercentage, this->_bar.LowerRightCorner.Y);
    this->_empty.UpperLeftCorner.set(this->_tofill.LowerRightCorner.X, this->_tofill.UpperLeftCorner.Y);
    this->_empty.LowerRightCorner.set(this->_bar.LowerRightCorner.X, this->_bar.LowerRightCorner.Y);
  }
  return (true);
}

kirr::f32 ProgressBar::getProgress() const
{
  return (this->_progress);
}

void ProgressBar::draw()
{
  if (!this->isVisible())
    return;
  this->_driver->draw2DRectangle(this->_bordercolor, this->_border);
  this->_driver->draw2DRectangle(this->_fillcolor, this->_tofill);
  this->_driver->draw2DRectangle(this->_emptycolor, this->_empty);
}
