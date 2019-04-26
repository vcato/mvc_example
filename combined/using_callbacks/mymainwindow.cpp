#include "mymainwindow.hpp"

#include <cassert>
#include "myoptionswindow.hpp"


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
    viewOptionsWindow().options_changed_callback =
      [this]{ controllerOnOptionsWindowOptionsChanged(); };
    viewOptionsWindow().options_callback =
      [this]() -> Options& { return _applicationData().options; };
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
