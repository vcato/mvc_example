#include "mymainwindow.hpp"

#include <cassert>
#include "myoptionswindow.hpp"


// MyMainWindow::Controller
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


// MyMainWindow
///////////////

MyMainWindow::MyMainWindow()
: _options_window_client(*this)
{
}


MyMainWindow::~MyMainWindow() = default;


void MyMainWindow::setApplicationDataPtr(ApplicationData *arg)
{
  _application_data_ptr = arg;
}


ApplicationData &MyMainWindow::_applicationData()
{
  assert(_application_data_ptr);
  return *_application_data_ptr;
}


void MyMainWindow::open()
{
  // _view().viewOpenWindow();
  viewOpenWindow();
}
