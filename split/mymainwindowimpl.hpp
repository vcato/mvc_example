#include "mymainwindow.hpp"
#include "applicationdata.hpp"
#include "optionswindow.hpp"


class MyMainWindow::View {
  public:
    View(MyMainWindow &main_window) : _main_window(main_window) {}

    virtual void openWindow() = 0;
    virtual bool optionsWindowExists() const = 0;
    virtual void createOptionsWindow() = 0;
    virtual OptionsWindow &optionsWindow() = 0;
    virtual void redraw3D() = 0;

  protected:
    ApplicationData &_applicationData()
    {
      return _main_window._applicationData();
    }

    Controller &_controller()
    {
      return _main_window._controller();
    }

  private:
    MyMainWindow &_main_window;
};


class MyMainWindow::Controller {
  public:
    Controller(MyMainWindow &);

    void onOpenOptionsPressed();
    void onOptionsWindowOptionsChanged();

  private:
    class OptionsWindowClient : public OptionsWindow::Client {
      public:
        OptionsWindowClient(Controller &controller)
        : _controller(controller)
        {
        }

        void onOptionsChanged() override
        {
          _controller.onOptionsWindowOptionsChanged();
        }

        Options &options() override
        {
          return _controller._applicationData().options;
        }

      private:
        Controller &_controller;
    };

    OptionsWindowClient _options_window_client;
    MyMainWindow &_main_window;

    ApplicationData &_applicationData()
    {
      return _main_window._applicationData();
    }

    View &_view()
    {
      return _main_window._view();
    }

    void _openOptionsWindow();
};
