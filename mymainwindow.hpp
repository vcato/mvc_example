#include <memory>
#include "applicationdata.hpp"

struct MyMainWindowController;


class MyMainWindow {
  public:
    MyMainWindow(ApplicationData &application_data);
    ~MyMainWindow();

    virtual void open() = 0;

  protected:
    std::unique_ptr<MyMainWindowController> _controller_ptr;
};
