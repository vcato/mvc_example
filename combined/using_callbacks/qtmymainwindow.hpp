#ifndef QTMYMAINWINDOW_HPP_
#define QTMYMAINWINDOW_HPP_


#include <QMainWindow>
#include "mymainwindow.hpp"
#include "qtoptionswindow.hpp"


class QtMyMainWindow : public QMainWindow, public MyMainWindow
{
  public:
    QtMyMainWindow();
    ~QtMyMainWindow();

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


#endif /* QTMYMAINWINDOW_HPP_ */
