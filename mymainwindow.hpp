#ifndef MYMAINWINDOW_HPP_
#define MYMAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"


class MyMainWindow {
  public:
    MyMainWindow();
    ~MyMainWindow();

    void setApplicationDataPtr(ApplicationData *);
    virtual void open() = 0;

  protected:
    struct View;
    struct Controller;

    std::unique_ptr<Controller> _controller_ptr;
    ApplicationData *_application_data_ptr = 0;

    ApplicationData &_applicationData();
    virtual View &_view() = 0;
    Controller &_controller();
};


#endif /* MYMAINWINDOW_HPP_ */
