#include "mymainwindow.hpp"
#include "applicationdata.hpp"
#include "myoptionswindow.hpp"

struct MyOptionsWindow;


class MyMainWindowView {
  public:
    MyMainWindowView(MyMainWindowController &controller);

    virtual bool optionsWindowExists() const = 0;
    virtual void createOptionsWindow() = 0;
    virtual MyOptionsWindow &optionsWindow() = 0;
    virtual void redraw3DWindow() = 0;

  protected:
    MyMainWindowController &_controller;
};


class MyMainWindowController {
  public:
    MyMainWindowController(ApplicationData &application_data);

    void onOpenOptionsPressed();
    void onOptionsWindowOptionsChanged();
    void setViewPtr(MyMainWindowView *);

  private:
    class OptionsWindowClient : public MyOptionsWindowClient {
      public:
        OptionsWindowClient(MyMainWindowController &controller_arg);

        void onOptionsChanged() override;

      private:
        MyMainWindowController &_controller;
    };

    ApplicationData &_application_data;
    MyMainWindowView *_view_ptr = nullptr;
    OptionsWindowClient _options_window_client;

    MyMainWindowView &_view();
};
