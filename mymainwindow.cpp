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


void MyMainWindowView::setOptionsPtr(Options *arg)
{
  _options_ptr = arg;
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


MyMainWindowController::MyMainWindowController()
: _options_window_client(*this)
{
}


void MyMainWindowController::setViewPtr(MyMainWindowView *arg)
{
  _view_ptr = arg;
  assert(_view_ptr);
}


void MyMainWindowController::setApplicationDataPtr(ApplicationData *arg)
{
  _application_data_ptr = arg;

  assert(arg);
  _view().setOptionsPtr(&arg->options);
}


void MyMainWindowController::onOpenOptionsPressed()
{
  MyMainWindowView &view = _view();

  if (!view.optionsWindowExists()) {
    view.createOptionsWindow();
    view.optionsWindow().setClientPtr(&_options_window_client);
    assert(_application_data_ptr);
    view.optionsWindow().setOptionsPtr(&_application_data_ptr->options);
  }

  view.optionsWindow().open();
}


void MyMainWindowController::onOptionsWindowOptionsChanged()
{
  _view().redraw3DWindow();
}


MyMainWindowView &MyMainWindowController::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}



// MyMainWindow
///////////////

MyMainWindow::MyMainWindow()
: _controller_ptr(std::make_unique<MyMainWindowController>())
{
}


MyMainWindow::~MyMainWindow() = default;


void MyMainWindow::setApplicationDataPtr(ApplicationData *arg)
{
  assert(_controller_ptr);
  _controller_ptr->setApplicationDataPtr(arg);
}
