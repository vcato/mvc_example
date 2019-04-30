all: run_unit_tests main

clean:
	rm -f *.o *.d *.pass

##############

PACKAGES=Qt5Widgets

CXXFLAGS=-W -Wall -Wundef -pedantic -std=c++14 \
  `pkg-config --cflags $(PACKAGES)` \
  -fpic -MD -MP -D_GLIBCXX_DEBUG -g

main: main.o mymainwindow.o optionswindow.o \
  qtmymainwindow.o qtoptionswindow.o
	$(CXX) -o $@ $^ `pkg-config --libs $(PACKAGES)`

run_unit_tests: mymainwindow_test.pass

mymainwindow_test.pass: mymainwindow_test
	./mymainwindow_test
	touch $@

mymainwindow_test: mymainwindow_test.o mymainwindow.o optionswindow.o
	$(CXX) -o $@ $^

-include *.d
