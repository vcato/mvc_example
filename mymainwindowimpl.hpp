#include "mymainwindow.hpp"
#include "applicationdata.hpp"
#include "myoptionswindow.hpp"


class MyMainWindow::View {
  public:
    View(MyMainWindow &);

    virtual bool optionsWindowExists() const = 0;
    virtual void createOptionsWindow() = 0;
    virtual MyOptionsWindow &optionsWindow() = 0;
    virtual void redraw3DWindow() = 0;

  protected:
    MyMainWindow &_main_window;

    Controller &_controller();
    ApplicationData &_applicationData();
};


class MyMainWindow::Controller {
  public:
    Controller(MyMainWindow &);

    void onOpenOptionsPressed();
    void onOptionsWindowOptionsChanged();

  private:
    class OptionsWindowClient : public MyOptionsWindow::Client {
      public:
        OptionsWindowClient(Controller &);

        void onOptionsChanged() override;
        Options &options() override;

      private:
        Controller &_controller;
    };

    OptionsWindowClient _options_window_client;
    MyMainWindow &_main_window;

    ApplicationData &_applicationData();
    View &_view();
};
