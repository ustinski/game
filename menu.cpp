#include "menu.h"
#include "glwidget.h"
#include "window.h"
#include "gameobjects.h"
#include "button.h"

namespace Menu
{
    Button *start;
    Button *resume;
    Button *quit;

    bool _menu, pauseMenu;
    float pauseMenuTimer;
    double _levelTime;
    int _initLevelTime;
    bool _pause;

    GLWidget *_widget;
}

void Menu::init(GLWidget *widget)
{
    //menu with "start" and "quit"
    _menu = true;
    //after game is stopped, buttons can't be pressed for pauseMenuTimer seconds to prevene accidental pressing buttons, initial value is false
    pauseMenu = false;
    pauseMenuTimer = 3;
    _initLevelTime = 60;
    _pause = false;

    start = new Button("START", Window::height() / 4);
    resume = new Button("RESUME", 0);
    quit = new Button("QUIT", -Window::height() / 4);

    _widget = widget;
}

void Menu::draw()
{
    if(!_menu) return;
    start->draw();
    if(_pause) resume->draw();
    quit->draw();
}

void Menu::update(double dt)
{
    if(!_menu) _levelTime -= dt;
    if(_levelTime <= 0) {
        _levelTime = 0;
        _menu = true;
    }
    if(_menu) {
        start->update(dt);
        if(_pause) resume->update(dt);
        quit->update(dt);

        if(pauseMenu) {
            pauseMenuTimer -= dt;
            if(pauseMenuTimer <= 0) {
                pauseMenu = false;
                pauseMenuTimer = 3;
            }
        }
    }
}

void Menu::mousePressEvent()
{
    //returns true if start
    if(!_pause && pauseMenu) return;
    const QPoint &mousePos = _widget->mousePos();
    if(start->isUnderCursor(mousePos)) {
        //(re)start
        //_levelTime changes to zero during game, after restart is equal to _initLevelTime again
        _levelTime = _initLevelTime;
        _menu = false;
        pauseMenu = true;
        _pause = false;

        start->reset();
        quit->reset();

        GameObjects::restart();
    }
    else if(_pause && resume->isUnderCursor(mousePos)) switchPause();
    else if(quit->isUnderCursor(mousePos)) _widget->close();
}

void Menu::mouseMoveEvent()
{
    if(!_menu) return;
    const QPoint &mousePos = _widget->mousePos();
    if(start->isUnderCursor(mousePos)) {
        if(!start->selected()) start->select();
    } else if(resume->isUnderCursor(mousePos)) {
        if(!resume->selected()) resume->select();
    } else if(quit->isUnderCursor(mousePos)) {
        if(!quit->selected()) quit->select();
    } else {
        if(start->selected()) start->deselect();
        if(resume->selected()) resume->deselect();
        if(quit->selected()) quit->deselect();
    }
}

bool Menu::menu() { return _menu; }
void Menu::switchToMenu() { _menu = true; }
bool Menu::pause() { return _pause; }

void Menu::switchPause()
{
    if(_pause) {
        _menu = false;
        _pause = false;
    }
    else if(!_menu) {
        _menu = true;
        _pause = true;
    }
}

double Menu::levelTime() { return _levelTime; }
int Menu::initLevelTime() { return _initLevelTime; }
