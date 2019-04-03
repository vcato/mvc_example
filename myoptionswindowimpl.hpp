struct MyOptionsWindowClient;
struct MyOptionsWindowController;


struct MyOptionsWindowView {
  virtual void setLabelAxesToggleState(bool) = 0;
  virtual bool labelAxesToggleState() const = 0;

  MyOptionsWindowView(MyOptionsWindowController &controller);

  MyOptionsWindowController &_controller;
};


class MyOptionsWindowController {
  public:
    void setViewPtr(MyOptionsWindowView *);
    void setClientPtr(MyOptionsWindowClient *);
    void setOptionsPtr(Options *);
    void onLabelAxesToggled();

  private:
    Options *_options_ptr = nullptr;
    MyOptionsWindowClient *_client_ptr = nullptr;
    MyOptionsWindowView *_view_ptr = nullptr;
};
