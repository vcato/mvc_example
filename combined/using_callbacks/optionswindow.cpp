#include "optionswindow.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// Controller
////////////////////////////

void OptionsWindow::controllerOnOpenWindow()
{
  _controllerUpdateLabelAxesToggleState();
}


void OptionsWindow::controllerOnLabelAxesToggled()
{
  _controllerUpdateLabelAxesValue();
  assert(options_changed_callback);
  options_changed_callback();
}


void OptionsWindow::_controllerUpdateLabelAxesToggleState()
{
  viewSetLabelAxesToggleState(_options().label_axes);
}


void OptionsWindow::_controllerUpdateLabelAxesValue()
{
  _options().label_axes = viewLabelAxesToggleState();
}


// private methods
//////////////////


Options &OptionsWindow::_options()
{
  assert(options_callback);
  return options_callback();
}


// public methods
//////////////////

OptionsWindow::OptionsWindow() = default;


OptionsWindow::~OptionsWindow() = default;


void OptionsWindow::open()
{
  viewOpenWindow();
  controllerOnOpenWindow();
}
