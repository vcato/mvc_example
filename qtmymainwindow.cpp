#include "qtmymainwindow.hpp"
#include "mymainwindowimpl.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "qtmyoptionswindow.hpp"
#include "widgetutil.hpp"

using std::cerr;


class QtMyMainWindowView : public MyMainWindowView {
  public:
    QtMyMainWindowView(
      QMainWindow &main_window,
      MyMainWindowController &controller
    )
    : MyMainWindowView(controller),
      _main_window(main_window)
    {
      assert(main_window.layout());
      QPushButton &button =
        createCentralWidget<QPushButton>(main_window,"Open Options");
      QObject::connect(&button,&QPushButton::clicked,
        [&]{ controller.onOpenOptionsPressed(); }
      );
    }

    bool optionsWindowExists() const
    {
      return _options_window_ptr != nullptr;
    }

    void createOptionsWindow()
    {
      assert(!_options_window_ptr);
      _options_window_ptr = new QtMyOptionsWindow(&_main_window);
    }

    void redraw3DWindow() override
    {
      assert(_options_ptr);

      cerr << "Redrawing 3D window\n";
      cerr << "  label_axis: " << _options_ptr->label_axes << "\n";
    }

    MyOptionsWindow &optionsWindow() override
    {
      assert(_options_window_ptr);
      return *_options_window_ptr;
    }

  private:
    QMainWindow &_main_window;
    QtMyOptionsWindow *_options_window_ptr = nullptr;

};


QtMyMainWindow::QtMyMainWindow()
: _view_ptr{std::make_unique<QtMyMainWindowView>(*this,*_controller_ptr)}
{
}


QtMyMainWindow::~QtMyMainWindow() = default;
