#include <QMainWindow>
#include "mymainwindow.hpp"


class QtMyMainWindow : public QMainWindow, public MyMainWindow
{
  public:
    QtMyMainWindow();
    ~QtMyMainWindow();

    void open() override { show(); }

  private:
    struct QtView;
    std::unique_ptr<QtView> _view_ptr;
    MyMainWindow::View &_view() override;
};
