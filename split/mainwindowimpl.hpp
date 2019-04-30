#include "mainwindow.hpp"
#include "applicationdata.hpp"
#include "optionswindow.hpp"


class MainWindow::View {
  public:
    View(MainWindow &main_window) : _main_window(main_window) {}

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
    MainWindow &_main_window;
};


class MainWindow::Controller {
  public:
    Controller(MainWindow &);

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
    MainWindow &_main_window;

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
