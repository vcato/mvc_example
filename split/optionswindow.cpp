#include "optionswindow.hpp"
#include "optionswindowimpl.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// OptionsWindow::Controller
////////////////////////////

OptionsWindow::Controller::Controller(
  OptionsWindow &options_window
)
: _options_window(options_window)
{
}


void OptionsWindow::Controller::onOpenWindow()
{
  _updateLabelAxesToggleState();
}


void OptionsWindow::Controller::onLabelAxesToggled()
{
  _updateLabelAxesValue();
  _client().onOptionsChanged();
}


OptionsWindow::View &OptionsWindow::Controller::_view()
{
  return _options_window._view();
}


OptionsWindow::Client &OptionsWindow::Controller::_client()
{
  return _options_window._client();
}


Options &OptionsWindow::Controller::_options()
{
  return _options_window._options();
}


void OptionsWindow::Controller::_updateLabelAxesToggleState()
{
  _view().setLabelAxesToggleState(_options().label_axes);
}


void OptionsWindow::Controller::_updateLabelAxesValue()
{
  _options().label_axes = _view().labelAxesToggleState();
}


// OptionsWindow
//////////////////

OptionsWindow::OptionsWindow()
: _controller_ptr(std::make_unique<Controller>(*this))
{
}


OptionsWindow::~OptionsWindow() = default;


void OptionsWindow::setClientPtr(Client *arg)
{
  _client_ptr = arg;
}


void OptionsWindow::open()
{
  _view().openWindow();
  _controller().onOpenWindow();
}


OptionsWindow::Client &OptionsWindow::_client()
{
  assert(_client_ptr);
  return *_client_ptr;
}


OptionsWindow::Controller &OptionsWindow::_controller()
{
  assert(_controller_ptr);
  return *_controller_ptr;
}


Options &OptionsWindow::_options()
{
  return _client().options();
}
