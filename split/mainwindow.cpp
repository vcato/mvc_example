#include "mainwindow.hpp"
#include "mainwindowimpl.hpp"

#include <cassert>
#include "optionswindow.hpp"


// MainWindow::Controller
/////////////////////////

MainWindow::Controller::Controller(MainWindow &main_window)
: _options_window_client(*this),
  _main_window(main_window)
{
}


void MainWindow::Controller::onOpenOptionsPressed()
{
  _openOptionsWindow();
}


void MainWindow::Controller::onOptionsWindowOptionsChanged()
{
  _view().redraw3D();
}


void MainWindow::Controller::_openOptionsWindow()
{
  if (!_view().optionsWindowExists()) {
    _view().createOptionsWindow();
    _view().optionsWindow().setClientPtr(&_options_window_client);
  }

  _view().optionsWindow().open();
}


// MainWindow
///////////////

MainWindow::MainWindow()
: _controller_ptr(std::make_unique<Controller>(*this))
{
}


MainWindow::~MainWindow() = default;


void MainWindow::setApplicationDataPtr(ApplicationData *arg)
{
  _application_data_ptr = arg;
}


ApplicationData &MainWindow::_applicationData()
{
  assert(_application_data_ptr);
  return *_application_data_ptr;
}


MainWindow::Controller &MainWindow::_controller()
{
  assert(_controller_ptr);
  return *_controller_ptr;
}


void MainWindow::open()
{
  _view().openWindow();
}
