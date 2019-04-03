#ifndef OPTIONSWINDOW_HPP_
#define OPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"

class MyOptionsWindowController;
class MyOptionsWindowView;


struct MyOptionsWindowClient {
  virtual void onOptionsChanged() = 0;
};


class MyOptionsWindow {
  public:
    MyOptionsWindow();
    ~MyOptionsWindow();

    void setOptionsPtr(Options *);
    void setClientPtr(MyOptionsWindowClient *);
    virtual void open() = 0;

  protected:
    std::unique_ptr<MyOptionsWindowController> _controller_ptr;

  private:
    virtual MyOptionsWindowView &_view() = 0;
};


#endif /* OPTIONSWINDOW_HPP_ */
