#include "qtmyoptionswindow.hpp"

#include <cassert>
#include <QCheckBox>
#include <QBoxLayout>
#include "widgetutil.hpp"


void QtMyOptionsWindow::viewOpenWindow()
{
  show();
}


bool QtMyOptionsWindow::viewLabelAxesToggleState() const
{
  return _viewLabelAxesCheckBox().isChecked();
}


void QtMyOptionsWindow::viewSetLabelAxesToggleState(bool arg)
{
  _viewLabelAxesCheckBox().setChecked(arg);
}


QCheckBox &QtMyOptionsWindow::_viewLabelAxesCheckBox() const
{
  assert(_label_axes_check_box_ptr);
  return *_label_axes_check_box_ptr;
}


QCheckBox& QtMyOptionsWindow::viewCreateLabelAxesCheckBox(QLayout &layout)
{
  QCheckBox &label_axes_check_box =
    createWidget<QCheckBox>(layout,"Label Axes");
  QObject::connect(&label_axes_check_box,&QCheckBox::stateChanged,
    [&]{
      controllerOnLabelAxesToggled();
    }
  );

  return label_axes_check_box;
}


QtMyOptionsWindow::QtMyOptionsWindow(QWidget *parent_ptr)
: QDialog(parent_ptr)
{
  auto &layout = createLayout<QVBoxLayout>(*this);
  _label_axes_check_box_ptr = &viewCreateLabelAxesCheckBox(layout);
}


QtMyOptionsWindow::~QtMyOptionsWindow() = default;
