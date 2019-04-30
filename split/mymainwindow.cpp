#include "mymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <cassert>
#include "optionswindow.hpp"


// MyMainWindow::Controller
/////////////////////////

MyMainWindow::Controller::Controller(MyMainWindow &main_window)
: _options_window_client(*this),
  _main_window(main_window)
{
}


void MyMainWindow::Controller::onOpenOptionsPressed()
{
  _openOptionsWindow();
}


void MyMainWindow::Controller::onOptionsWindowOptionsChanged()
{
  _view().redraw3D();
}


void MyMainWindow::Controller::_openOptionsWindow()
{
  if (!_view().optionsWindowExists()) {
    _view().createOptionsWindow();
    _view().optionsWindow().setClientPtr(&_options_window_client);
  }

  _view().optionsWindow().open();
}


// MyMainWindow
///////////////

MyMainWindow::MyMainWindow()
: _controller_ptr(std::make_unique<Controller>(*this))
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


MyMainWindow::Controller &MyMainWindow::_controller()
{
  assert(_controller_ptr);
  return *_controller_ptr;
}


void MyMainWindow::open()
{
  _view().openWindow();
}
