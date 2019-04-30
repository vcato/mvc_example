#include <QApplication>
#include "applicationdata.hpp"
#include "qtmainwindow.hpp"


int main(int argc,char** argv)
{
  QApplication application(argc,argv);
  ApplicationData application_data;
  QtMainWindow main_window;
  main_window.setApplicationDataPtr(&application_data);
  main_window.open();
  application.exec();
}
