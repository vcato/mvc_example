#ifndef QTOPTIONSWINDOW_HPP_
#define QTOPTIONSWINDOW_HPP_

#include <QDialog>
#include <QCheckBox>
#include "optionswindow.hpp"


class QtOptionsWindow : public QDialog, public OptionsWindow {
  public:
    QtOptionsWindow(QWidget *parent_ptr);
    ~QtOptionsWindow();

  private: // View implementation
    void viewOpenWindow() override;
    bool viewLabelAxesToggleState() const override;
    void viewSetLabelAxesToggleState(bool arg) override;

  private:
    QCheckBox *_view_label_axes_check_box_ptr = nullptr;

    QCheckBox& viewCreateLabelAxesCheckBox(QLayout &layout);
    QCheckBox &_viewLabelAxesCheckBox() const;
};


#endif /* QTOPTIONSWINDOW_HPP_ */
