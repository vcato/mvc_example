all: run_unit_tests main

clean:
	rm -f *.o *.d *.pass

##############

PACKAGES=Qt5Widgets

CXXFLAGS=-W -Wall -Wundef -pedantic -std=c++14 \
  `pkg-config --cflags $(PACKAGES)` \
  -fpic -MD -MP -D_GLIBCXX_DEBUG -g

main: main.o mainwindow.o optionswindow.o \
  qtmainwindow.o qtoptionswindow.o
	$(CXX) -o $@ $^ `pkg-config --libs $(PACKAGES)`

run_unit_tests: mainwindow_test.pass

mainwindow_test.pass: mainwindow_test
	./mainwindow_test
	touch $@

mainwindow_test: mainwindow_test.o mainwindow.o optionswindow.o
	$(CXX) -o $@ $^

-include *.d
