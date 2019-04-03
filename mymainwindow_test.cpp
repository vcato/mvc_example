#include "mymainwindow.hpp"

#include <cassert>
#include <sstream>
#include "mymainwindowimpl.hpp"
#include "myoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

using std::ostringstream;
using std::string;


namespace {
class FakeOptionsWindow : public MyOptionsWindow
{
  public:
    bool is_open = false;

    struct FakeView : View {
      FakeView(FakeOptionsWindow &options_window)
      : View(options_window)
      {
      }

      bool label_axes_state = false;

      void setLabelAxesToggleState(bool arg) override
      {
        label_axes_state = arg;
      }

      bool labelAxesToggleState() const override
      {
        return label_axes_state;
      }
    };

    FakeView view;

    FakeOptionsWindow()
    : view(*this)
    {
    }

    void open() override { is_open = true; }

    Controller &_controller()
    {
      assert(MyOptionsWindow::_controller_ptr);
      return *MyOptionsWindow::_controller_ptr;
    }

    void userTogglesLabelAxes()
    {
      assert(is_open);
      view.label_axes_state = !view.label_axes_state;
      _controller().onLabelAxesToggled();
    }

  private:
    MyOptionsWindow::View &_view() override
    {
      return view;
    }
};
}


namespace {
class FakeMainWindow : public MyMainWindow
{
  public:
    struct FakeView : MyMainWindow::View
    {
      FakeView(MyMainWindow &main_window)
      : MyMainWindow::View(main_window)
      {
      }

      bool options_window_exists = false;
      FakeOptionsWindow options_window;
      ostringstream command_stream;

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
        bool label_axes = _applicationData().options.label_axes;
        command_stream << "redraw3DWindow(label_axes=" << label_axes << ")\n";
      }
    };

    bool is_open = false;
    FakeView view;

    FakeMainWindow()
    : view(*this)
    {
    }

    MyMainWindow::View &_view() override { return view; }

    MyMainWindow::Controller &controller()
    {
      assert(MyMainWindow::_controller_ptr);
      return *MyMainWindow::_controller_ptr;
    }

    void open() override { is_open = true; }

    void userPressesOpenOptions()
    {
      assert(is_open);
      controller().onOpenOptionsPressed();
    }

    string commandString() { return view.command_stream.str(); }

    void clearCommandString()
    {
      view.command_stream.str("");
    }

    void expectCommands(const string &expected_commands)
    {
      assert(commandString() == expected_commands);
      clearCommandString();
    }

    FakeOptionsWindow &optionsWindow()
    {
      return view.options_window;
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
  assert(main_window.optionsWindow().is_open);
  main_window.optionsWindow().userTogglesLabelAxes();
  assert(application_data.options.label_axes == true);
  main_window.expectCommands("redraw3DWindow(label_axes=1)\n");
  main_window.optionsWindow().userTogglesLabelAxes();
  assert(application_data.options.label_axes == false);
  main_window.expectCommands("redraw3DWindow(label_axes=0)\n");
}
