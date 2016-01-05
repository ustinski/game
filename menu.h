#ifndef MENU_H
#define MENU_H

class GLWidget;

namespace Menu
{
    void init(GLWidget *widget);
    void draw();
    void update(double dt);
    void mousePressEvent();
    void mouseMoveEvent();

    bool menu();
    void switchToMenu();
    bool pause();
    void switchPause();

    double levelTime();
    int initLevelTime();
}

#endif // MENU_H
