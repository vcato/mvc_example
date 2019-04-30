#include <QMainWindow>
#include "mainwindow.hpp"


class QtMainWindow : public QMainWindow, public MainWindow
{
  public:
    QtMainWindow();
    ~QtMainWindow();

  private:
    struct QtView;
    std::unique_ptr<QtView> _view_ptr;
    MainWindow::View &_view() override;
};
