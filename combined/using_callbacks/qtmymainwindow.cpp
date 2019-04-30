#include "qtmymainwindow.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "qtoptionswindow.hpp"
#include "widgetutil.hpp"

using std::cerr;


// View methods
////////////////

void QtMyMainWindow::viewOpenWindow()
{
  show();
}


bool QtMyMainWindow::viewOptionsWindowExists() const
{
  return _options_window_ptr != nullptr;
}


void QtMyMainWindow::viewCreateOptionsWindow()
{
  assert(!_options_window_ptr);
  _options_window_ptr = new QtOptionsWindow(this);
}


OptionsWindow &QtMyMainWindow::viewOptionsWindow()
{
  assert(_options_window_ptr);
  return *_options_window_ptr;
}


void QtMyMainWindow::viewRedraw3D()
{
  cerr << "Redrawing 3D\n";
  cerr << "  label_axes: " << _applicationData().options.label_axes << "\n";
}


void QtMyMainWindow::_viewCreateOpenOptionsButton()
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

QtMyMainWindow::QtMyMainWindow()
{
  _viewCreateOpenOptionsButton();
}


QtMyMainWindow::~QtMyMainWindow() = default;
