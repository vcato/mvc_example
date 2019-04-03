#include "qtmymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "qtmyoptionswindow.hpp"
#include "widgetutil.hpp"

using std::cerr;


class QtMyMainWindow::QtView : public MyMainWindow::View {
  public:
    QtView(QtMyMainWindow &main_window)
    : MyMainWindow::View(main_window),
      _main_window_widget(main_window)
    {
      assert(_main_window_widget.layout());
      QPushButton &button =
        createCentralWidget<QPushButton>(_main_window_widget,"Open Options");
      QObject::connect(&button,&QPushButton::clicked,
        [&]{
          _controller().onOpenOptionsPressed();
        }
      );
    }

    bool optionsWindowExists() const
    {
      return _options_window_ptr != nullptr;
    }

    void createOptionsWindow()
    {
      assert(!_options_window_ptr);
      _options_window_ptr = new QtMyOptionsWindow(&_main_window_widget);
    }

    MyOptionsWindow &optionsWindow() override
    {
      assert(_options_window_ptr);
      return *_options_window_ptr;
    }

    void redraw3DWindow() override
    {
      cerr << "Redrawing 3D window\n";
      cerr << "  label_axes: " << _applicationData().options.label_axes << "\n";
    }

  private:
    QMainWindow &_main_window_widget;
    QtMyOptionsWindow *_options_window_ptr = nullptr;
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
