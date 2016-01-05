#include "gameobjects.h"
#include "animatedobjects.h"
#include "fontrenderer.h"
#include "glwidget.h"
#include "menu.h"
#include "sdlmixer.h"
#include "gl.h"
#include "window.h"
#include "physics.h"
#include "mesh.h"

#include <QBasicTimer>
#include <QMouseEvent>

#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFixedSize(Window::width(), Window::height());
    setMouseTracking(true);
    QCursor cursor(Qt::BlankCursor);
    cursor.setPos(Window::width() / 2, Window::height() / 2);
    setCursor(cursor);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GL::init(this);
    Menu::init(this);
    Physics::init();
    GameObjects::init();
    AnimatedObjects::init(this);
    FontRenderer::init();
    SdlMixer::init(this);

    (new QBasicTimer)->start(0, this);
    timer.start();
}

void GLWidget::resizeGL(int w, int h)
{ 
    GL::resize(w, h);
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    GameObjects::draw();
    AnimatedObjects::drawCannon();
    Menu::draw();
    drawText();
    AnimatedObjects::scope().draw();
}

void GLWidget::drawText()
{
    int y = -Window::height() / 2 + 15;
    FontRenderer::setSize(25);
    FontRenderer::draw("TIME: " + QString::number(int(Menu::levelTime())) + "/" + QString::number(Menu::initLevelTime()), -160, y);
    FontRenderer::draw("BUBBLES: " + QString::number(GameObjects::targetsLeft()) + "/" + QString::number(GameObjects::totalBubbles()), 220, y);
    FontRenderer::draw("SCORE: " + QString::number(GameObjects::score()), 500, y);
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    double dt = timer.elapsed() / double(1000);
    timer.restart();

    Menu::update(dt);
    if(!Menu::pause()) {
        AnimatedObjects::update(dt);
        Physics::update(dt);
        GameObjects::update(dt);
    }
    AnimatedObjects::scope().setPosition(_mousePos);

    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    _mousePos.setX( event->pos().x() - Window::width() / 2);
    _mousePos.setY(-event->pos().y() + Window::height() / 2);

    Menu::mouseMoveEvent();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(Menu::menu()) Menu::mousePressEvent();
    else AnimatedObjects::mousePressEvent();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{ if(event->key() == Qt::Key_Escape) Menu::switchPause(); }
