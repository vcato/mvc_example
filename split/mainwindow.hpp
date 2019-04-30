#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"


class MainWindow {
  public:
    MainWindow();
    ~MainWindow();

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


#endif /* MAINWINDOW_HPP_ */
