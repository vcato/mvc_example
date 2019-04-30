#ifndef OPTIONSWINDOW_HPP_
#define OPTIONSWINDOW_HPP_

#include <memory>
#include "options.hpp"


class OptionsWindow {
  public:
    struct Client {
      virtual void onOptionsChanged() = 0;
      virtual Options &options() = 0;
    };

    OptionsWindow();
    ~OptionsWindow();

    void setClientPtr(Client *);
    void open();

  protected: // Controller methods
    void controllerOnLabelAxesToggled();
    void controllerOnOpenWindow();

  private: // View interface
    virtual void viewOpenWindow() = 0;
    virtual bool viewLabelAxesToggleState() const = 0;
    virtual void viewSetLabelAxesToggleState(bool) = 0;

  private:
    Client *_client_ptr = nullptr;

    Options &_options();
    Client &_client();

    void _controllerUpdateLabelAxesToggleState();
    void _controllerUpdateLabelAxesValue();
};


#endif /* OPTIONSWINDOW_HPP_ */
