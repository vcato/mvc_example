#include "myoptionswindow.hpp"


class MyOptionsWindow::View {
  public:
    View(MyOptionsWindow &);

    virtual void setLabelAxesToggleState(bool) = 0;
    virtual bool labelAxesToggleState() const = 0;

  protected:
    Controller &_controller();

  private:
    MyOptionsWindow &_options_window;
};


class MyOptionsWindow::Controller {
  public:
    Controller(MyOptionsWindow &);

    void onLabelAxesToggled();
    void onOptionsChanged();

  private:
    MyOptionsWindow &_options_window;

    View &_view();
    Client &_client();
    Options &_options();
};
