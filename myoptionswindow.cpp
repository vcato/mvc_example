#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// MyOptionsWindowView
//////////////////////

MyOptionsWindow::View::View(MyOptionsWindow &options_window)
: _options_window(options_window)
{
}


MyOptionsWindow::Controller &MyOptionsWindow::View::_controller()
{
  return *_options_window._controller_ptr;
}


// MyOptionsWindowController
////////////////////////////


MyOptionsWindow::Controller::Controller(
  MyOptionsWindow &options_window
)
: _options_window(options_window)
{
}


void MyOptionsWindow::Controller::onLabelAxesToggled()
{
  _options().label_axes = _view().labelAxesToggleState();
  _client().onOptionsChanged();
}


void MyOptionsWindow::Controller::onOptionsChanged()
{
  _view().setLabelAxesToggleState(_options().label_axes);
}


MyOptionsWindow::View &MyOptionsWindow::Controller::_view()
{
  return _options_window._view();
}


MyOptionsWindowClient &MyOptionsWindow::Controller::_client()
{
  return _options_window._client();
}


Options &MyOptionsWindow::Controller::_options()
{
  return _options_window._options();
}


// MyOptionsWindow
//////////////////

MyOptionsWindow::MyOptionsWindow()
: _controller_ptr(std::make_unique<Controller>(*this))
{
}


MyOptionsWindow::~MyOptionsWindow() = default;


void MyOptionsWindow::setOptionsPtr(Options *arg)
{
  _options_ptr = arg;
  _controller_ptr->onOptionsChanged();
}


void MyOptionsWindow::setClientPtr(MyOptionsWindowClient *arg)
{
  _client_ptr = arg;
}


MyOptionsWindowClient &MyOptionsWindow::_client()
{
  assert(_client_ptr);
  return *_client_ptr;
}


Options &MyOptionsWindow::_options()
{
  assert(_options_ptr);
  return *_options_ptr;
}
