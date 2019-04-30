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
    ApplicationData *_application_data_ptr = nullptr;

    void _controllerOpenOptionsWindow();
};


#endif /* MAINWINDOW_HPP_ */
