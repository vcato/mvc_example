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
    viewOptionsWindow().options_changed_callback =
      [this]{ controllerOnOptionsWindowOptionsChanged(); };
    viewOptionsWindow().options_callback =
      [this]() -> Options& { return _applicationData().options; };
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
