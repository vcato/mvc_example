#ifndef OPTIONSWINDOW_HPP_
#define OPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"


class OptionsWindow {
  public:
    OptionsWindow();
    ~OptionsWindow();

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


#endif /* OPTIONSWINDOW_HPP_ */
