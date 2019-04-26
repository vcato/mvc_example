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
    ApplicationData *_application_data_ptr = nullptr;

    void _controllerOpenOptionsWindow();
};


#endif /* MYMAINWINDOW_HPP_ */
