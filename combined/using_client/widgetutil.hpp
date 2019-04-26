#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include <QMainWindow>


template <typename Layout,typename Widget>
static Layout &createLayout(Widget &widget)
{
  Layout *layout_ptr = new Layout;
  widget.setLayout(layout_ptr);
  return *layout_ptr;
}


template <typename Widget,typename Layout,typename... Args>
static Widget &createWidget(Layout &layout,const Args &...args)
{
  Widget *widget_ptr = new Widget(args...);
  layout.addWidget(widget_ptr);
  return *widget_ptr;
}


template <typename Widget,typename... Args>
static Widget &createCentralWidget(QMainWindow &main_window,const Args &...args)
{
  Widget *widget_ptr = new Widget(args...);
  main_window.setCentralWidget(widget_ptr);
  return *widget_ptr;
}


#endif /* WIDGET_HPP_ */
