#ifndef OPTIONSWINDOW_HPP_
#define OPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"


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
    struct View;
    struct Controller;

    virtual View &_view() = 0;
    std::unique_ptr<Controller> _controller_ptr;
    Options *_options_ptr = nullptr;
    MyOptionsWindowClient *_client_ptr = nullptr;
    MyOptionsWindowClient &_client();
    Options &_options();
};


#endif /* OPTIONSWINDOW_HPP_ */
