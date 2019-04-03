#include "mymainwindow.hpp"
#include "applicationdata.hpp"
#include "myoptionswindow.hpp"

struct MyOptionsWindow;


class MyMainWindowView {
  public:
    MyMainWindowView(MyMainWindowController &controller);
    void setOptionsPtr(Options *);

    virtual bool optionsWindowExists() const = 0;
    virtual void createOptionsWindow() = 0;
    virtual MyOptionsWindow &optionsWindow() = 0;
    virtual void redraw3DWindow() = 0;

  protected:
    MyMainWindowController &_controller;
    Options *_options_ptr = nullptr;
};


class MyMainWindowController {
  public:
    MyMainWindowController();

    void onOpenOptionsPressed();
    void onOptionsWindowOptionsChanged();
    void setViewPtr(MyMainWindowView *);
    void setApplicationDataPtr(ApplicationData *);

  private:
    class OptionsWindowClient : public MyOptionsWindowClient {
      public:
        OptionsWindowClient(MyMainWindowController &controller_arg);

        void onOptionsChanged() override;

      private:
        MyMainWindowController &_controller;
    };

    ApplicationData *_application_data_ptr = nullptr;
    MyMainWindowView *_view_ptr = nullptr;
    OptionsWindowClient _options_window_client;

    MyMainWindowView &_view();
};
