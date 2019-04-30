#include "optionswindow.hpp"


class OptionsWindow::View {
  public:
    View(OptionsWindow &options_window) :_options_window(options_window) { }

    virtual void setLabelAxesToggleState(bool) = 0;
    virtual bool labelAxesToggleState() const = 0;
    virtual void openWindow() = 0;

  protected:
    Controller &_controller() { return _options_window._controller(); }

  private:
    OptionsWindow &_options_window;
};


class OptionsWindow::Controller {
  public:
    Controller(OptionsWindow &);

    void onOpenWindow();
    void onLabelAxesToggled();

  private:
    OptionsWindow &_options_window;

    View &_view();
    Client &_client();
    Options &_options();
    void _updateLabelAxesToggleState();
    void _updateLabelAxesValue();
};
