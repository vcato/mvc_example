#include "mymainwindow.hpp"

#include <cassert>
#include "optionswindow.hpp"


// Controller
/////////////////////////

void MyMainWindow::controllerOnOpenOptionsPressed()
{
  _controllerOpenOptionsWindow();
}


void MyMainWindow::controllerOnOptionsWindowOptionsChanged()
{
  viewRedraw3D();
}


void MyMainWindow::_controllerOpenOptionsWindow()
{
  if (!viewOptionsWindowExists()) {
    viewCreateOptionsWindow();
    viewOptionsWindow().setClientPtr(&_options_window_client);
  }

  viewOptionsWindow().open();
}


// protected methods
//////////////////

ApplicationData &MyMainWindow::_applicationData()
{
  assert(_application_data_ptr);
  return *_application_data_ptr;
}


// public methods
/////////////////

MyMainWindow::MyMainWindow()
: _options_window_client(*this)
{
}


MyMainWindow::~MyMainWindow() = default;


void MyMainWindow::setApplicationDataPtr(ApplicationData *arg)
{
  _application_data_ptr = arg;
}


void MyMainWindow::open()
{
  viewOpenWindow();
}
