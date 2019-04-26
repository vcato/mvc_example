#include "myoptionswindow.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


// Controller
////////////////////////////

void MyOptionsWindow::controllerOnOpenWindow()
{
  _controllerUpdateLabelAxesToggleState();
}


void MyOptionsWindow::controllerOnLabelAxesToggled()
{
  _controllerUpdateLabelAxesValue();
  assert(options_changed_callback);
  options_changed_callback();
}


void MyOptionsWindow::_controllerUpdateLabelAxesToggleState()
{
  viewSetLabelAxesToggleState(_options().label_axes);
}


void MyOptionsWindow::_controllerUpdateLabelAxesValue()
{
  _options().label_axes = viewLabelAxesToggleState();
}


// private methods
//////////////////


Options &MyOptionsWindow::_options()
{
  assert(options_callback);
  return options_callback();
}


// public methods
//////////////////

MyOptionsWindow::MyOptionsWindow() = default;


MyOptionsWindow::~MyOptionsWindow() = default;


void MyOptionsWindow::open()
{
  viewOpenWindow();
  controllerOnOpenWindow();
}
