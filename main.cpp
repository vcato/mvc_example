#include <QApplication>
#include "applicationdata.hpp"
#include "qtmymainwindow.hpp"


int main(int argc,char** argv)
{
  QApplication application(argc,argv);
  ApplicationData application_data;
  QtMyMainWindow main_window(application_data);
  main_window.open();
  application.exec();
}
