#include "mymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <cassert>
#include "myoptionswindow.hpp"


// MyMainWindow::View
///////////////////

MyMainWindow::View::View(MyMainWindow &main_window)
: _main_window(main_window)
{
}


MyMainWindow::Controller &MyMainWindow::View::_controller()
{
  assert(_main_window._controller_ptr);
  return *_main_window._controller_ptr;
}


ApplicationData &MyMainWindow::View::_applicationData()
{
  assert(_main_window._application_data_ptr);
  return *_main_window._application_data_ptr;
}


// MyMainWindow::Controller
/////////////////////////

MyMainWindow::Controller::OptionsWindowClient::OptionsWindowClient(
  Controller &controller
)
: _controller(controller)
{
}


void MyMainWindow::Controller::OptionsWindowClient::onOptionsChanged()
{
  _controller.onOptionsWindowOptionsChanged();
}


MyMainWindow::Controller::Controller(MyMainWindow &main_window)
: _options_window_client(*this),
  _main_window(main_window)
{
}


void MyMainWindow::Controller::onOpenOptionsPressed()
{
  View &view = _view();

  if (!view.optionsWindowExists()) {
    view.createOptionsWindow();
    view.optionsWindow().setClientPtr(&_options_window_client);
    view.optionsWindow().setOptionsPtr(&_applicationData().options);
  }

  view.optionsWindow().open();
}


void MyMainWindow::Controller::onOptionsWindowOptionsChanged()
{
  _view().redraw3DWindow();
}


MyMainWindow::View &MyMainWindow::Controller::_view()
{
  return _main_window._view();
}


ApplicationData &MyMainWindow::Controller::_applicationData()
{
  assert(_main_window._application_data_ptr);
  return *_main_window._application_data_ptr;
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
