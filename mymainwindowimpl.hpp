#include "applicationdata.hpp"
#include "myoptionswindow.hpp"


struct MyOptionsWindow;


struct MyMainWindowView {
  virtual bool optionsWindowExists() const = 0;
  virtual void createOptionsWindow() = 0;
  virtual MyOptionsWindow &optionsWindow() = 0;
  virtual void redraw3DWindow() = 0;

  MyMainWindowView(MyMainWindowController &controller);

  MyMainWindowController &_controller;
};


class MyMainWindowController {
  public:
    MyMainWindowController(ApplicationData &application_data);

    void onOpenOptionsPressed();
    void onOptionsWindowOptionsChanged();
    void setViewPtr(MyMainWindowView *);

  private:
    struct OptionsWindowClient : MyOptionsWindowClient {
      MyMainWindowController &controller;

      OptionsWindowClient(MyMainWindowController &controller_arg)
      : controller(controller_arg)
      {
      }

      void onOptionsChanged() override;
    };

    ApplicationData &_application_data;
    MyMainWindowView *_view_ptr = nullptr;
    OptionsWindowClient _options_window_client;

    MyMainWindowView &_view();
};
