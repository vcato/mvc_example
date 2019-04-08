#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// MyOptionsWindowController
////////////////////////////

MyOptionsWindow::Controller::Controller(
  MyOptionsWindow &options_window
)
: _options_window(options_window)
{
}


void MyOptionsWindow::Controller::onOpenWindow()
{
  _updateLabelAxesToggleState();
}


void MyOptionsWindow::Controller::onLabelAxesToggled()
{
  _updateLabelAxesValue();
  _client().onOptionsChanged();
}


MyOptionsWindow::View &MyOptionsWindow::Controller::_view()
{
  return _options_window._view();
}


MyOptionsWindow::Client &MyOptionsWindow::Controller::_client()
{
  return _options_window._client();
}


Options &MyOptionsWindow::Controller::_options()
{
  return _options_window._options();
}


void MyOptionsWindow::Controller::_updateLabelAxesToggleState()
{
  _view().setLabelAxesToggleState(_options().label_axes);
}


void MyOptionsWindow::Controller::_updateLabelAxesValue()
{
  _options().label_axes = _view().labelAxesToggleState();
}


// MyOptionsWindow
//////////////////

MyOptionsWindow::MyOptionsWindow()
: _controller_ptr(std::make_unique<Controller>(*this))
{
}


MyOptionsWindow::~MyOptionsWindow() = default;


void MyOptionsWindow::setClientPtr(Client *arg)
{
  _client_ptr = arg;
}


void MyOptionsWindow::open()
{
  _view().openWindow();
  _controller().onOpenWindow();
}


MyOptionsWindow::Client &MyOptionsWindow::_client()
{
  assert(_client_ptr);
  return *_client_ptr;
}


MyOptionsWindow::Controller &MyOptionsWindow::_controller()
{
  assert(_controller_ptr);
  return *_controller_ptr;
}


Options &MyOptionsWindow::_options()
{
  return _client().options();
}
