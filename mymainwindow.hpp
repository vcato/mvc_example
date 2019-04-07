#ifndef MYMAINWINDOW_HPP_
#define MYMAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"


class MyMainWindow {
  public:
    MyMainWindow();
    ~MyMainWindow();

    void setApplicationDataPtr(ApplicationData *);
    void open();

  protected:
    class View;
    class Controller;

    Controller &_controller();

  private:
    std::unique_ptr<Controller> _controller_ptr;
    ApplicationData *_application_data_ptr = nullptr;

    ApplicationData &_applicationData();
    virtual View &_view() = 0;
};


#endif /* MYMAINWINDOW_HPP_ */
