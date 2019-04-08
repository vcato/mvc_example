#include "myoptionswindow.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// MyOptionsWindowController
////////////////////////////

void MyOptionsWindow::controllerOnOpenWindow()
{
  _controllerUpdateLabelAxesToggleState();
}


void MyOptionsWindow::controllerOnLabelAxesToggled()
{
  _controllerUpdateLabelAxesValue();
  _client().onOptionsChanged();
}


void MyOptionsWindow::_controllerUpdateLabelAxesToggleState()
{
  viewSetLabelAxesToggleState(_options().label_axes);
}


void MyOptionsWindow::_controllerUpdateLabelAxesValue()
{
  _options().label_axes = viewLabelAxesToggleState();
}


// MyOptionsWindow
//////////////////

MyOptionsWindow::MyOptionsWindow() = default;


MyOptionsWindow::~MyOptionsWindow() = default;


void MyOptionsWindow::setClientPtr(Client *arg)
{
  _client_ptr = arg;
}


void MyOptionsWindow::open()
{
  viewOpenWindow();
  controllerOnOpenWindow();
}


MyOptionsWindow::Client &MyOptionsWindow::_client()
{
  assert(_client_ptr);
  return *_client_ptr;
}


Options &MyOptionsWindow::_options()
{
  return _client().options();
}
