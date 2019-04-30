#include "qtoptionswindow.hpp"
#include "optionswindowimpl.hpp"

#include <cassert>
#include <QCheckBox>
#include <QBoxLayout>
#include "widgetutil.hpp"


class QtOptionsWindow::QtView : public OptionsWindow::View {
  public:
    QtView(QtOptionsWindow &options_window)
    : OptionsWindow::View(options_window),
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
    QtOptionsWindow &_options_window;

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


QtOptionsWindow::QtOptionsWindow(QWidget *parent_ptr)
: QDialog(parent_ptr),
  _view_ptr(std::make_unique<QtView>(*this))
{
}


QtOptionsWindow::~QtOptionsWindow() = default;


OptionsWindow::View &QtOptionsWindow::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}
