#ifndef MESH_H
#define MESH_H

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>

#include "gl.h"

#include <vector>

using namespace std;

struct VertexData
{
    QVector3D position;
    QVector2D uv;
};

class GLWidget;

class Mesh
{
public:
    Mesh() {}
    Mesh(const QString &texture, double x, double y);
    Mesh(QOpenGLTexture *texture, double x, double y, int width, int height)
    { init(texture, x, y, width, height); }

    void init(QOpenGLTexture *texture, double x, double y, int width, int height);

    QOpenGLBuffer *arrayBuf() { return &_arrayBuf; }
    void setPosition(const QPoint position)
    { _position = QVector2D(position); }

    virtual void move(const QVector2D &dr) { _position += dr; }
    void setPosition(double x, double y);
    const QVector2D &position() { return _position; }
    virtual void draw();

protected:
    QMatrix4x4 model;

    QOpenGLTexture *_texture;
    QVector2D _position;

    QOpenGLBuffer _arrayBuf;

    void initVertices(int width, int height);
    virtual void prepareMatrix();

private:
    vector <VertexData> vertices;
};

#endif // MESH_H
