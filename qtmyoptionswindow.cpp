#include "qtmyoptionswindow.hpp"
#include "myoptionswindowimpl.hpp"

#include <cassert>
#include <QCheckBox>
#include <QBoxLayout>
#include "widgetutil.hpp"


class QtMyOptionsWindow::QtView : public MyOptionsWindow::View {
  public:
    QtView(QtMyOptionsWindow &options_window)
    : MyOptionsWindow::View(options_window),
      _options_window(options_window)
    {
      auto &layout = createLayout<QVBoxLayout>(options_window);
      _label_axes_check_box_ptr = &createLabelAxesCheckBox(layout);
    }

    void setLabelAxesToggleState(bool arg) override
    {
      _labelAxesCheckBox().setChecked(arg);
    }

    bool labelAxesToggleState() const override
    {
      return _labelAxesCheckBox().isChecked();
    }

    void openWindow() override
    {
      _options_window.show();
    }

  private:
    QCheckBox *_label_axes_check_box_ptr = nullptr;
    QtMyOptionsWindow &_options_window;

    QCheckBox& createLabelAxesCheckBox(QLayout &layout)
    {
      QCheckBox &label_axes_check_box =
        createWidget<QCheckBox>(layout,"Label Axes");
      QObject::connect(&label_axes_check_box,&QCheckBox::stateChanged,
        [&]{
          _controller().onLabelAxesToggled();
        }
      );

      return label_axes_check_box;
    }

    QCheckBox &_labelAxesCheckBox()
    {
      assert(_label_axes_check_box_ptr);
      return *_label_axes_check_box_ptr;
    }

    const QCheckBox &_labelAxesCheckBox() const
    {
      assert(_label_axes_check_box_ptr);
      return *_label_axes_check_box_ptr;
    }
};


QtMyOptionsWindow::QtMyOptionsWindow(QWidget *parent_ptr)
: QDialog(parent_ptr),
  _view_ptr(std::make_unique<QtView>(*this))
{
}


QtMyOptionsWindow::~QtMyOptionsWindow() = default;


MyOptionsWindow::View &QtMyOptionsWindow::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}
