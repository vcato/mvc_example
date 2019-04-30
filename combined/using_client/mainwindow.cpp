#include "mainwindow.hpp"

#include <cassert>
#include "optionswindow.hpp"


// Controller
/////////////////////////

void MainWindow::controllerOnOpenOptionsPressed()
{
  _controllerOpenOptionsWindow();
}


void MainWindow::controllerOnOptionsWindowOptionsChanged()
{
  viewRedraw3D();
}


void MainWindow::_controllerOpenOptionsWindow()
{
  if (!viewOptionsWindowExists()) {
    viewCreateOptionsWindow();
    viewOptionsWindow().setClientPtr(&_options_window_client);
  }

  viewOptionsWindow().open();
}


// protected methods
//////////////////

ApplicationData &MainWindow::_applicationData()
{
  assert(_application_data_ptr);
  return *_application_data_ptr;
}


// public methods
/////////////////

MainWindow::MainWindow()
: _options_window_client(*this)
{
}


MainWindow::~MainWindow() = default;


void MainWindow::setApplicationDataPtr(ApplicationData *arg)
{
  _application_data_ptr = arg;
}


void MainWindow::open()
{
  viewOpenWindow();
}
