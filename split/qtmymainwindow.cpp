#include "qtmymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "qtoptionswindow.hpp"
#include "widgetutil.hpp"

using std::cerr;


class QtMyMainWindow::QtView : public MyMainWindow::View {
  public:
    QtView(QtMyMainWindow &main_window)
    : MyMainWindow::View(main_window),
      _main_window_widget(main_window)
    {
      createOpenOptionsButton();
    }

    // MyMainWindow::View implementation
    ////////////////////////////////////

    bool optionsWindowExists() const override
    {
      return _options_window_ptr != nullptr;
    }

    void createOptionsWindow() override
    {
      assert(!_options_window_ptr);
      _options_window_ptr = new QtOptionsWindow(&_main_window_widget);
    }

    OptionsWindow &optionsWindow() override
    {
      assert(_options_window_ptr);
      return *_options_window_ptr;
    }

    void redraw3D() override
    {
      cerr << "Redrawing 3D\n";
      cerr << "  label_axes: " << _applicationData().options.label_axes << "\n";
    }

    void openWindow() override
    {
      _main_window_widget.show();
    }

  private:
    QMainWindow &_main_window_widget;
    QtOptionsWindow *_options_window_ptr = nullptr;

    void createOpenOptionsButton()
    {
      QPushButton &button =
        createCentralWidget<QPushButton>(_main_window_widget,"Open Options");
      QObject::connect(&button,&QPushButton::clicked,
        [&]{
          _controller().onOpenOptionsPressed();
        }
      );
    }
};


QtMyMainWindow::QtMyMainWindow()
: _view_ptr{std::make_unique<QtView>(*this)}
{
}


QtMyMainWindow::~QtMyMainWindow() = default;


MyMainWindow::View &QtMyMainWindow::_view()
{
  assert(_view_ptr);
  return *_view_ptr;
}
