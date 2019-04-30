#include "qtoptionswindow.hpp"

#include <cassert>
#include <QCheckBox>
#include <QBoxLayout>
#include "widgetutil.hpp"


void QtOptionsWindow::viewOpenWindow()
{
  show();
}


bool QtOptionsWindow::viewLabelAxesToggleState() const
{
  return _viewLabelAxesCheckBox().isChecked();
}


void QtOptionsWindow::viewSetLabelAxesToggleState(bool arg)
{
  _viewLabelAxesCheckBox().setChecked(arg);
}


QCheckBox &QtOptionsWindow::_viewLabelAxesCheckBox() const
{
  assert(_view_label_axes_check_box_ptr);
  return *_view_label_axes_check_box_ptr;
}


QCheckBox& QtOptionsWindow::viewCreateLabelAxesCheckBox(QLayout &layout)
{
  auto &label_axes_check_box = createWidget<QCheckBox>(layout,"Label Axes");

  QObject::connect(
    &label_axes_check_box,
    &QCheckBox::stateChanged,
    [this]{ controllerOnLabelAxesToggled(); }
  );

  return label_axes_check_box;
}


QtOptionsWindow::QtOptionsWindow(QWidget *parent_ptr)
: QDialog(parent_ptr)
{
  auto &layout = createLayout<QVBoxLayout>(*this);
  _view_label_axes_check_box_ptr = &viewCreateLabelAxesCheckBox(layout);
}


QtOptionsWindow::~QtOptionsWindow() = default;
