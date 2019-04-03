#include "qtmyoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

#include <cassert>
#include <QCheckBox>
#include <QBoxLayout>
#include "widgetutil.hpp"


class QtMyOptionsWindow::QtView : public MyOptionsWindow::View {
  public:
    QtView(QDialog &parent,MyOptionsWindow &options_window)
    : MyOptionsWindow::View(options_window)
    {
      auto &layout = createLayout<QVBoxLayout>(parent);
      QCheckBox &label_axes_toggle =
        createWidget<QCheckBox>(layout,"Label Axes");
      _label_axes_toggle_ptr = &label_axes_toggle;
      QObject::connect(&label_axes_toggle,&QCheckBox::stateChanged,
        [&]{
          _controller().onLabelAxesToggled();
        }
      );
    }

    void setLabelAxesToggleState(bool arg) override
    {
      assert(_label_axes_toggle_ptr);
      _label_axes_toggle_ptr->setChecked(arg);
    }

    bool labelAxesToggleState() const override
    {
      assert(_label_axes_toggle_ptr);
      return _label_axes_toggle_ptr->isChecked();
    }

  private:
    QCheckBox *_label_axes_toggle_ptr = nullptr;
};


QtMyOptionsWindow::QtMyOptionsWindow(QWidget *parent_ptr)
: QDialog(parent_ptr),
  _view_ptr(std::make_unique<QtView>(*this,*this))
{
}


QtMyOptionsWindow::~QtMyOptionsWindow() = default;


MyOptionsWindow::View &QtMyOptionsWindow::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}
