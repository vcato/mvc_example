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
  _client().onOptionsChanged();
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

OptionsWindow::Client &OptionsWindow::_client()
{
  assert(_client_ptr);
  return *_client_ptr;
}


Options &OptionsWindow::_options()
{
  return _client().options();
}


// public methods
//////////////////

OptionsWindow::OptionsWindow() = default;


OptionsWindow::~OptionsWindow() = default;


void OptionsWindow::setClientPtr(Client *arg)
{
  _client_ptr = arg;
}


void OptionsWindow::open()
{
  viewOpenWindow();
  controllerOnOpenWindow();
}
