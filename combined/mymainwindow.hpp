#ifndef MYMAINWINDOW_HPP_
#define MYMAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"
#include "myoptionswindow.hpp"


class MyMainWindow {
  public:
    MyMainWindow();
    ~MyMainWindow();

    void setApplicationDataPtr(ApplicationData *);
    void open();

  protected:
    ApplicationData &_applicationData();

  protected: // Controller methods
    void controllerOnOpenOptionsPressed();
    void controllerOnOptionsWindowOptionsChanged();

  private: // View interface
    virtual void viewOpenWindow() = 0;
    virtual bool viewOptionsWindowExists() const = 0;
    virtual void viewCreateOptionsWindow() = 0;
    virtual MyOptionsWindow &viewOptionsWindow() = 0;
    virtual void viewRedraw3D() = 0;

  private:
    class OptionsWindowClient : public MyOptionsWindow::Client {
      public:
        OptionsWindowClient(MyMainWindow &main_window)
        : _main_window(main_window)
        {
        }

        void onOptionsChanged() override
        {
          _main_window.controllerOnOptionsWindowOptionsChanged();
        }

        Options &options() override
        {
          return _main_window._applicationData().options;
        }

      private:
        MyMainWindow &_main_window;
    };

    OptionsWindowClient _options_window_client;
    ApplicationData *_application_data_ptr = nullptr;

    void _controllerOpenOptionsWindow();
};


#endif /* MYMAINWINDOW_HPP_ */
