#include <QMainWindow>
#include "mymainwindow.hpp"


class QtMyMainWindowView;


class QtMyMainWindow : public QMainWindow, public MyMainWindow
{
  public:
    QtMyMainWindow(ApplicationData &application_data);
    ~QtMyMainWindow();
    void open() override { show(); }

  private:
    std::unique_ptr<QtMyMainWindowView> _view_ptr;
};
