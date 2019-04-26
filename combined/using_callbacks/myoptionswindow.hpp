#ifndef MYOPTIONSWINDOW_HPP_
#define MYOPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"


class MyOptionsWindow {
  public:
    MyOptionsWindow();
    ~MyOptionsWindow();

    void open();

    std::function<void()> options_changed_callback;
    std::function<Options&()> options_callback;

  protected: // Controller methods
    void controllerOnLabelAxesToggled();
    void controllerOnOpenWindow();

  private: // View interface
    virtual void viewOpenWindow() = 0;
    virtual bool viewLabelAxesToggleState() const = 0;
    virtual void viewSetLabelAxesToggleState(bool) = 0;

  private:
    Options &_options();

    void _controllerUpdateLabelAxesToggleState();
    void _controllerUpdateLabelAxesValue();
};


#endif /* MYOPTIONSWINDOW_HPP_ */
