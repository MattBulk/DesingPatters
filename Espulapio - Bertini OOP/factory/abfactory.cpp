#include "abfactory.h"

class Widget {
public:
    virtual ~Widget() {}
    
    virtual void draw() = 0;
};

class Window : public Widget {
public:
    Window() : title("") { }
    virtual ~Window() { }

    virtual void resize() = 0;

    std::string title;
};

class Button : public Widget {
public:
    Button() : text("") { }
    virtual ~Button() { }

    virtual void setIcon() = 0;

    std::string text;
};

class WindowsWindow : public Window {
public:
    WindowsWindow(std::string title) {
        this->title = title;
    }

    virtual ~WindowsWindow() { }

    virtual void draw() override {
        print("WindowsWindows: ", "has been drawn");
    }
    virtual void resize() override {
            print("WindowsWindows: ", "has been resized");
    }
};

class WindowsButton : public Button {
public:
    WindowsButton(std::string text) {
        this->text = text;
    }

    virtual ~WindowsButton() { }

    virtual void draw() override {
        print("WindowsButton: ", "has been drawn");

    }
    virtual void setIcon() override {
        print("WindowsButton:", "icon has been set");
    }
};

class iOSWindow : public Window {
public:
    iOSWindow(std::string title) {
        this->title = title;
    }

    virtual ~iOSWindow() { }

    virtual void draw() override {
        print("iOSWindows: ", "has been drawn");
    }
    virtual void resize() override {
            print("iOSWindows: ", "has been resized");
    }
};

class iOSButton : public Button {
public:
    iOSButton(std::string text) {
        this->text = text;
    }

    virtual ~iOSButton() { }

    virtual void draw() override {
        print("iOSButton: ", "has been drawn");

    }
    virtual void setIcon() override {
        print("iOSButton:", "icon has been set");
    }
};

class WidgetFactory {
public:
    virtual ~WidgetFactory() { }

    virtual Button* createButton(const std::string &text) = 0;
    virtual Window* createWindow(const std::string &title) = 0;
};

class WindowsFactory : public WidgetFactory {
public:
    virtual ~WindowsFactory() { }

    virtual Button *createButton(const std::string &text) override {
        return(new WindowsButton(text));       
    }

    virtual Window *createWindow(const std::string &title) override {
        return(new WindowsWindow(title));
    }
};

class iOSFactory : public WidgetFactory {
public:
    virtual ~iOSFactory() { }

    virtual Button *createButton(const std::string &text) override {
        return(new iOSButton(text));       
    }

    virtual Window *createWindow(const std::string &title) override {
        return(new iOSWindow(title));
    }
};

#define _WIN64

void abFactoryExample() {
    WidgetFactory *guiFactory;

    #ifndef _WIN64
        guiFactory = new WindowsFactory();
    #else
        guiFactory = new iOSFactory();
    #endif

    Button *btn;
    Window *win;

    btn = guiFactory->createButton("Click");
    win = guiFactory->createWindow("Lisa Framework");

    btn->draw();
    btn->setIcon();

    win->draw();
    win->resize();

}
