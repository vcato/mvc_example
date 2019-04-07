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
    class FakeView : public MyOptionsWindow::View {
      public:
        FakeView(FakeOptionsWindow &options_window_arg)
        : MyOptionsWindow::View(options_window_arg),
          _options_window(options_window_arg)
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

        void openWindow() override
        {
          _options_window.is_open = true;
        }

      private:
        FakeOptionsWindow &_options_window;
    };

    bool is_open = false;
    FakeView view{*this};

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
      FakeView(FakeMainWindow &main_window)
      : MyMainWindow::View(main_window),
        _main_window(main_window)
      {
      }

      bool options_window_exists = false;
      ostringstream command_stream;
      FakeMainWindow &_main_window;

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
        return _main_window.options_window;
      }

      void redraw3D() override
      {
        bool label_axes = _applicationData().options.label_axes;
        command_stream << "redraw3D(label_axes=" << label_axes << ")\n";
      }

      void openWindow() override
      {
        _main_window.is_open = true;
      }
    };

    bool is_open = false;
    FakeOptionsWindow options_window;
    FakeView view;

    FakeMainWindow()
    : view(*this)
    {
    }

    MyMainWindow::View &_view() override { return view; }

    void userPressesOpenOptions()
    {
      assert(is_open);
      _controller().onOpenOptionsPressed();
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
      return options_window;
    }
};
}


static void testTogglingLabelAxes()
{
  ApplicationData application_data;
  FakeMainWindow main_window;
  main_window.setApplicationDataPtr(&application_data);
  main_window.open();
  main_window.userPressesOpenOptions();
  assert(main_window.optionsWindow().is_open);
  main_window.optionsWindow().userTogglesLabelAxes();
  assert(application_data.options.label_axes == true);
  main_window.expectCommands("redraw3D(label_axes=1)\n");
  main_window.optionsWindow().userTogglesLabelAxes();
  assert(application_data.options.label_axes == false);
  main_window.expectCommands("redraw3D(label_axes=0)\n");
}


static void testOpeningTheOptionsWindowTheLabelAxesAlreadyOn()
{
  ApplicationData application_data;
  FakeMainWindow main_window;
  main_window.setApplicationDataPtr(&application_data);

  application_data.options.label_axes = true;
  main_window.open();
  main_window.userPressesOpenOptions();
  assert(main_window.optionsWindow().view.label_axes_state == true);
}


int main()
{
  testTogglingLabelAxes();
  testOpeningTheOptionsWindowTheLabelAxesAlreadyOn();
}
