#include "qtmymainwindow.hpp"

#include <iostream>
#include <cassert>
#include <QPushButton>
#include <QMainWindow>
#include "mymainwindowimpl.hpp"
#include "qtmyoptionswindow.hpp"
#include "widgetutil.hpp"


class QtMyMainWindowView : public MyMainWindowView {
  public:
    QtMyMainWindowView(
      QMainWindow &main_window,
      MyMainWindowController &controller
    )
    : MyMainWindowView(controller)
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
      _options_window_ptr = new QtMyOptionsWindow;
    }

    void redraw3DWindow() override
    {
      std::cerr << "Redrawing 3D window\n";
    }

    MyOptionsWindow &optionsWindow() override
    {
      assert(_options_window_ptr);
      return *_options_window_ptr;
    }

  private:
    QtMyOptionsWindow *_options_window_ptr = nullptr;

};


QtMyMainWindow::QtMyMainWindow(ApplicationData &application_data)
: MyMainWindow(application_data),
  _view_ptr{std::make_unique<QtMyMainWindowView>(*this,*_controller_ptr)}
{
}


QtMyMainWindow::~QtMyMainWindow() = default;
