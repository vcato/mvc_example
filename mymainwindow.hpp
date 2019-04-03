#ifndef MYMAINWINDOW_HPP_
#define MYMAINWINDOW_HPP_

#include <memory>
#include "applicationdata.hpp"

struct MyMainWindowController;


class MyMainWindow {
  public:
    MyMainWindow();
    ~MyMainWindow();

    void setApplicationDataPtr(ApplicationData *);
    virtual void open() = 0;

  protected:
    std::unique_ptr<MyMainWindowController> _controller_ptr;
};


#endif /* MYMAINWINDOW_HPP_ */
