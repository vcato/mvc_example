#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

#include <cassert>
#include <iostream>

using std::cerr;


MyOptionsWindowView::MyOptionsWindowView(MyOptionsWindowController &controller)
: _controller(controller)
{
  controller.setViewPtr(this);
}


void MyOptionsWindowController::setOptionsPtr(Options *arg)
{
  _options_ptr = arg;

  assert(_options_ptr);
  assert(_view_ptr);

  _view_ptr->setLabelAxesToggleState(_options_ptr->label_axes);
}


void MyOptionsWindowController::setViewPtr(MyOptionsWindowView *arg)
{
  _view_ptr = arg;
}


void MyOptionsWindowController::onLabelAxesToggled()
{
  assert(_client_ptr);
  assert(_options_ptr);
  assert(_view_ptr);
  _options_ptr->label_axes = _view_ptr->labelAxesToggleState();
  _client_ptr->onOptionsChanged();
}


void MyOptionsWindowController::setClientPtr(MyOptionsWindowClient *arg)
{
  _client_ptr = arg;
}


MyOptionsWindow::MyOptionsWindow()
: _controller_ptr(std::make_unique<MyOptionsWindowController>())
{
}


MyOptionsWindow::~MyOptionsWindow() = default;


void MyOptionsWindow::setOptionsPtr(Options *arg)
{
  _controller_ptr->setOptionsPtr(arg);
}


void MyOptionsWindow::setClientPtr(MyOptionsWindowClient *arg)
{
  _controller_ptr->setClientPtr(arg);
}


