#include "mymainwindow.hpp"

#include <cassert>
#include <sstream>
#include "mymainwindowimpl.hpp"
#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

using std::ostringstream;
using std::string;


namespace {
class FakeOptionsWindow : public MyOptionsWindow, public MyOptionsWindowView {
  public:
    bool is_open = false;
    bool label_axes_state = false;

    FakeOptionsWindow()
    : MyOptionsWindowView(*_controller_ptr)
    {
    }

    void open() override { is_open = true; }

    void userTogglesLabelAxes()
    {
      assert(is_open);
      label_axes_state = !label_axes_state;
      _controller_ptr->onLabelAxesToggled();
    }

  private:
    MyOptionsWindowView &_view() override
    {
      return *this;
    }

    void setLabelAxesToggleState(bool arg) override
    {
      label_axes_state = arg;
    }

    bool labelAxesToggleState() const override
    {
      return label_axes_state;
    }
};
}


namespace {
class FakeMainWindow : public MyMainWindow, public MyMainWindowView {
  public:
    bool is_open = false;
    bool options_window_exists = false;
    FakeOptionsWindow options_window;
    ostringstream command_stream;

    FakeMainWindow()
    : MyMainWindowView(*_controller_ptr)
    {
    }

    void open() override { is_open = true; }

    void userPressesOpenOptions()
    {
      assert(is_open);
      assert(_controller_ptr);
      _controller_ptr->onOpenOptionsPressed();
    }

    string commandString() { return command_stream.str(); }

  private:
    bool optionsWindowExists() const override
    {
      return options_window_exists;
    }

    void createOptionsWindow() override
    {
      options_window_exists = true;
    }

    MyOptionsWindow &optionsWindow() override
    {
      return options_window;
    }

    void redraw3DWindow() override
    {
      command_stream << "redraw3DWindow()\n";
    }
};
}


int main()
{
  ApplicationData application_data;
  FakeMainWindow main_window;
  main_window.setApplicationDataPtr(&application_data);
  main_window.open();
  main_window.userPressesOpenOptions();
  assert(main_window.options_window.is_open);
  main_window.options_window.userTogglesLabelAxes();
  assert(application_data.options.label_axes);
  string expected_command_string = "redraw3DWindow()\n";
  assert(main_window.commandString() == expected_command_string);
}
