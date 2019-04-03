#ifndef QTOPTIONSWINDOW_HPP_
#define QTOPTIONSWINDOW_HPP_

#include <QDialog>
#include "myoptionswindow.hpp"

struct QtMyOptionsWindowView;


class QtMyOptionsWindow : public QDialog, public MyOptionsWindow {
  public:
    QtMyOptionsWindow();
    ~QtMyOptionsWindow();

    void open() override { show(); }

  private:
    std::unique_ptr<QtMyOptionsWindowView> _view_ptr;

    MyOptionsWindowView &_view() override;
};



#endif /* QTOPTIONSWINDOW_HPP_ */
