#include "mymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <cassert>
#include "myoptionswindow.hpp"


// MyMainWindowView
///////////////////

MyMainWindowView::MyMainWindowView(MyMainWindowController &controller)
: _controller(controller)
{
  _controller.setViewPtr(this);
}


// MyMainWindowController
/////////////////////////

MyMainWindowController::OptionsWindowClient::OptionsWindowClient(
  MyMainWindowController &controller
)
: _controller(controller)
{
}


void MyMainWindowController::OptionsWindowClient::onOptionsChanged()
{
  _controller.onOptionsWindowOptionsChanged();
}


void MyMainWindowController::setViewPtr(MyMainWindowView *arg)
{
  _view_ptr = arg;
}


void MyMainWindowController::onOpenOptionsPressed()
{
  MyMainWindowView &view = _view();

  if (!view.optionsWindowExists()) {
    view.createOptionsWindow();
    view.optionsWindow().setClientPtr(&_options_window_client);
    view.optionsWindow().setOptionsPtr(&_application_data.options);
  }

  view.optionsWindow().open();
}


void MyMainWindowController::onOptionsWindowOptionsChanged()
{
  _view().redraw3DWindow();
}


MyMainWindowController::MyMainWindowController(
  ApplicationData &application_data
)
: _application_data(application_data),
  _options_window_client(*this)
{
}


MyMainWindowView &MyMainWindowController::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}



// MyMainWindow
///////////////

MyMainWindow::MyMainWindow(
  ApplicationData &application_data
)
: _controller_ptr(std::make_unique<MyMainWindowController>(application_data))
{
}


MyMainWindow::~MyMainWindow() = default;
