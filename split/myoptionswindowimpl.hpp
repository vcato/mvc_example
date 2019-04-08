#include "myoptionswindow.hpp"


class MyOptionsWindow::View {
  public:
    View(MyOptionsWindow &options_window) :_options_window(options_window) { }

    virtual void setLabelAxesToggleState(bool) = 0;
    virtual bool labelAxesToggleState() const = 0;
    virtual void openWindow() = 0;

  protected:
    Controller &_controller() { return _options_window._controller(); }

  private:
    MyOptionsWindow &_options_window;
};


class MyOptionsWindow::Controller {
  public:
    Controller(MyOptionsWindow &);

    void onOpenWindow();
    void onLabelAxesToggled();

  private:
    MyOptionsWindow &_options_window;

    View &_view();
    Client &_client();
    Options &_options();
    void _updateLabelAxesToggleState();
    void _updateLabelAxesValue();
};
