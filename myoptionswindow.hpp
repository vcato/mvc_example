#ifndef OPTIONSWINDOW_HPP_
#define OPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"


class MyOptionsWindow {
  public:
    struct Client {
      virtual void onOptionsChanged() = 0;
      virtual Options &options() = 0;
    };

    MyOptionsWindow();
    ~MyOptionsWindow();

    void setClientPtr(Client *);
    virtual void open() = 0;

  protected:
    struct View;
    struct Controller;

    Controller &_controller();

  private:
    std::unique_ptr<Controller> _controller_ptr;
    Client *_client_ptr = nullptr;

    Options &_options();
    virtual View &_view() = 0;
    Client &_client();
};


#endif /* OPTIONSWINDOW_HPP_ */
