#include "qtmainwindow.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "qtoptionswindow.hpp"
#include "widgetutil.hpp"

using std::cerr;


// View methods
////////////////

void QtMainWindow::viewOpenWindow()
{
  show();
}


bool QtMainWindow::viewOptionsWindowExists() const
{
  return _options_window_ptr != nullptr;
}


void QtMainWindow::viewCreateOptionsWindow()
{
  assert(!_options_window_ptr);
  _options_window_ptr = new QtOptionsWindow(this);
}


OptionsWindow &QtMainWindow::viewOptionsWindow()
{
  assert(_options_window_ptr);
  return *_options_window_ptr;
}


void QtMainWindow::viewRedraw3D()
{
  cerr << "Redrawing 3D\n";
  cerr << "  label_axes: " << _applicationData().options.label_axes << "\n";
}


void QtMainWindow::_viewCreateOpenOptionsButton()
{
  auto &button = createCentralWidget<QPushButton>(*this,"Open Options");

  QObject::connect(
    &button,
    &QPushButton::clicked,
    [this]{ controllerOnOpenOptionsPressed(); }
  );
}


// Public methods
/////////////////

QtMainWindow::QtMainWindow()
{
  _viewCreateOpenOptionsButton();
}


QtMainWindow::~QtMainWindow() = default;
