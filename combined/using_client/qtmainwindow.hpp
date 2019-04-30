#ifndef QTMAINWINDOW_HPP_
#define QTMAINWINDOW_HPP_


#include <QMainWindow>
#include "mainwindow.hpp"
#include "qtoptionswindow.hpp"


class QtMainWindow : public QMainWindow, public MainWindow
{
  public:
    QtMainWindow();
    ~QtMainWindow();

  private: // View implementation
    void viewOpenWindow() override;
    bool viewOptionsWindowExists() const override;
    void viewCreateOptionsWindow() override;
    OptionsWindow &viewOptionsWindow() override;
    void viewRedraw3D() override;

  private:
    QtOptionsWindow *_options_window_ptr = nullptr;

    void _viewCreateOpenOptionsButton();
};


#endif /* QTMAINWINDOW_HPP_ */
