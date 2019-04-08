#ifndef QTOPTIONSWINDOW_HPP_
#define QTOPTIONSWINDOW_HPP_

#include <QDialog>
#include <QCheckBox>
#include "myoptionswindow.hpp"


class QtMyOptionsWindow : public QDialog, public MyOptionsWindow {
  public:
    QtMyOptionsWindow(QWidget *parent_ptr);
    ~QtMyOptionsWindow();

  private: // View implementation
    void viewOpenWindow() override;
    bool viewLabelAxesToggleState() const override;
    void viewSetLabelAxesToggleState(bool arg) override;

  private:
    QCheckBox *_label_axes_check_box_ptr = nullptr;

    QCheckBox& viewCreateLabelAxesCheckBox(QLayout &layout);
    QCheckBox &_viewLabelAxesCheckBox() const;
};


#endif /* QTOPTIONSWINDOW_HPP_ */
