#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"
#include "optionswindow.hpp"


class MainWindow {
  public:
    MainWindow();
    ~MainWindow();

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
    virtual OptionsWindow &viewOptionsWindow() = 0;
    virtual void viewRedraw3D() = 0;

  private:
    class OptionsWindowClient : public OptionsWindow::Client {
      public:
        OptionsWindowClient(MainWindow &main_window)
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
        MainWindow &_main_window;
    };

    OptionsWindowClient _options_window_client;
    ApplicationData *_application_data_ptr = nullptr;

    void _controllerOpenOptionsWindow();
};


#endif /* MAINWINDOW_HPP_ */
