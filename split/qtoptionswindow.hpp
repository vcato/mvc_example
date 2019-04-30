#ifndef QTOPTIONSWINDOW_HPP_
#define QTOPTIONSWINDOW_HPP_

#include <QDialog>
#include "optionswindow.hpp"


class QtOptionsWindow : public QDialog, public OptionsWindow {
  public:
    QtOptionsWindow(QWidget *parent_ptr);
    ~QtOptionsWindow();

  private:
    struct QtView;
    std::unique_ptr<QtView> _view_ptr;
    View &_view() override;
};



#endif /* QTOPTIONSWINDOW_HPP_ */
