#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0);

    const QPoint &mousePos()
    { return _mousePos; }

private:
    QPoint _mousePos;
    QElapsedTimer timer;


    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void drawText();

    void timerEvent(QTimerEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GLWIDGET_H
