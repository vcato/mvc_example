#ifndef QTOPTIONSWINDOW_HPP_
#define QTOPTIONSWINDOW_HPP_

#include <QDialog>
#include "myoptionswindow.hpp"


class QtMyOptionsWindow : public QDialog, public MyOptionsWindow {
  public:
    QtMyOptionsWindow(QWidget *parent_ptr);
    ~QtMyOptionsWindow();

  private:
    struct QtView;
    std::unique_ptr<QtView> _view_ptr;
    View &_view() override;
};



#endif /* QTOPTIONSWINDOW_HPP_ */
