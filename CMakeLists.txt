cmake_minimum_required(VERSION 2.6)

enable_testing()
set(CMAKE_CXX_STANDARD 14)

add_executable(main
  main.cpp
  qtmymainwindow.cpp
  mymainwindow.cpp
  qtmyoptionswindow.cpp
  myoptionswindow.cpp
)

# For using Qt5
find_package(Qt5Widgets)
target_link_libraries (main Qt5::Widgets)


#add_executable(controller_test
#  controller_test.cpp
#  controller.cpp
#  userinterface.cpp
#  datestring.cpp
#  makelistentries.cpp
#  decodedhtmlstring.cpp
#  replacedstring.cpp
#)
#add_test(controller controller_test)
#
#
#add_custom_target(
#  run_tests ALL ctest
#  DEPENDS
#    controller_test
#)
