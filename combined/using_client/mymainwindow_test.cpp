#include "mymainwindow.hpp"

#include <cassert>
#include <sstream>
#include "optionswindow.hpp"

using std::ostringstream;
using std::string;


namespace {
class FakeOptionsWindow : public OptionsWindow
{
  public:
    bool is_open = false;
    bool label_axes_state = false;

    void userTogglesLabelAxes()
    {
      assert(is_open);
      label_axes_state = !label_axes_state;
      controllerOnLabelAxesToggled();
    }

  private: // View implementation
    void viewOpenWindow() override
    {
      is_open = true;
    }

    bool viewLabelAxesToggleState() const override
    {
      return label_axes_state;
    }

    void viewSetLabelAxesToggleState(bool arg) override
    {
      label_axes_state = arg;
    }
};
}


namespace {
class FakeMainWindow : public MyMainWindow
{
  public:
    bool is_open = false;
    bool options_window_exists = false;
    ostringstream command_stream;
    FakeOptionsWindow options_window;

    void userPressesOpenOptions()
    {
      assert(is_open);
      controllerOnOpenOptionsPressed();
    }

    void expectCommands(const string &expected_commands)
    {
      assert(_commandString() == expected_commands);
      _clearCommandString();
    }

  private: // View implementation
    void viewOpenWindow() override
    {
      is_open = true;
    }

    bool viewOptionsWindowExists() const override
    {
      return options_window_exists;
    }

    void viewCreateOptionsWindow() override
    {
      options_window_exists = true;
    }

    OptionsWindow &viewOptionsWindow() override
    {
      return options_window;
    }

    void viewRedraw3D() override
    {
      bool label_axes = _applicationData().options.label_axes;
      command_stream << "redraw3D(label_axes=" << label_axes << ")\n";
    }

  private:
    string _commandString() { return command_stream.str(); }

    void _clearCommandString()
    {
      command_stream.str("");
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
  assert(main_window.options_window.is_open);
  main_window.options_window.userTogglesLabelAxes();
  assert(application_data.options.label_axes == true);
  main_window.expectCommands("redraw3D(label_axes=1)\n");
  main_window.options_window.userTogglesLabelAxes();
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
  assert(main_window.options_window.label_axes_state == true);
}


int main()
{
  testTogglingLabelAxes();
  testOpeningTheOptionsWindowTheLabelAxesAlreadyOn();
}
