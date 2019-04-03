#include "mymainwindow.hpp"

#include <cassert>
#include "mymainwindowimpl.hpp"
#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"


namespace {
struct FakeOptionsWindowView : MyOptionsWindowView {
  FakeOptionsWindowView(MyOptionsWindowController &controller)
  : MyOptionsWindowView(controller)
  {
  }

  virtual void setLabelAxesToggleState(bool arg)
  {
    label_axes_state = arg;
  }

  virtual bool labelAxesToggleState() const
  {
    return label_axes_state;
  }

  bool label_axes_state = false;
};
}


namespace {
struct FakeOptionsWindow : MyOptionsWindow {
  bool is_open = false;
  FakeOptionsWindowView view;

  FakeOptionsWindow()
  : view(*_controller_ptr)
  {
  }

  void open() override
  {
    is_open = true;
  }

  void userTogglesLabelAxes()
  {
    assert(is_open);
    view.label_axes_state = !view.label_axes_state;
    _controller_ptr->onLabelAxesToggled();
  }

  MyOptionsWindowView &_view() override
  {
    return view;
  }
};
}


namespace {
struct FakeMainWindowView : MyMainWindowView {
  FakeMainWindowView(MyMainWindowController &controller)
  : MyMainWindowView(controller),
    options_window()
  {
  }

  int redraw_count = 0;

  bool optionsWindowExists() const override
  {
    return options_window_exists;
  }

  void createOptionsWindow()
  {
    options_window_exists = true;
  }

  MyOptionsWindow &optionsWindow() override
  {
    return options_window;
  }

  virtual void redraw3DWindow()
  {
    ++redraw_count;
  }

  bool options_window_exists = false;
  FakeOptionsWindow options_window;
};
}


namespace {
struct FakeMainWindow : MyMainWindow {
  FakeMainWindowView view;
  bool is_open;

  FakeMainWindow(ApplicationData &data)
  : MyMainWindow(data),
    view(*_controller_ptr)
  {
  }

  void open() override
  {
    is_open = true;
  }

  void userPressesOpenOptions()
  {
    assert(is_open);
    assert(_controller_ptr);
    _controller_ptr->onOpenOptionsPressed();
  }
};
}


int main()
{
  ApplicationData appllication_data;
  FakeMainWindow main_window(appllication_data);
  main_window.open();
  main_window.userPressesOpenOptions();
  assert(main_window.view.options_window.is_open);
  main_window.view.options_window.userTogglesLabelAxes();
  assert(main_window.view.redraw_count == 1);
  assert(appllication_data.options.label_axes);
}
