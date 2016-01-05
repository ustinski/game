#include "window.h"

namespace Window
{
    const int _width = 1300;
    const int _height = 650;
    const int _ground = 40;
}

int Window::width()
{ return _width; }

int Window::height()
{ return _height; }

int Window::ground()
{ return _ground; }
