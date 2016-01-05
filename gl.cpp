#include "gl.h"
#include "glwidget.h"

#include <QOpenGLBuffer>

namespace GL
{
    QOpenGLShaderProgram *_texture;
    QOpenGLShaderProgram *_refraction;
    QOpenGLBuffer *indexBuf;
    QMatrix4x4 _projection;


    void initShaderProgram(QOpenGLShaderProgram **program, const QString &shader, GLWidget *widget);
    void initIndexBuf();
    void setOptions();
}

void GL::init(GLWidget *widget)
{
    initShaderProgram(&_texture, "texture", widget);
    initShaderProgram(&_refraction, "refraction", widget);
    initIndexBuf();
    setOptions();
}

void GL::initShaderProgram(QOpenGLShaderProgram **program, const QString &shader, GLWidget *widget)
{
    *program = new QOpenGLShaderProgram;
    QOpenGLShaderProgram &p = **program;
    if(!p.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/" + shader + ".vert")) widget->close();
    if(!p.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/" + shader + ".frag")) widget->close();

    if(!p.link()) widget->close();
    if(!p.bind()) widget->close();
}

void GL::initIndexBuf()
{
    indexBuf = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    indexBuf->create();
    GLuint indices[4];
    for(int i = 0; i < 4; i++) indices[i] = i;
    indexBuf->bind();
    indexBuf->allocate(indices, 4 * sizeof(GLuint));
}

void GL::setOptions()
{
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

QOpenGLShaderProgram *GL::texture() { return _texture; }
QOpenGLShaderProgram *GL::refraction() { return _refraction; }
const QMatrix4x4 &GL::projection() { return _projection; }

void GL::resize(int w, int h)
{
    _projection.setToIdentity();
    _projection.ortho(-w / 2, w / 2, -h / 2, h / 2, -10, 20);
    _projection.translate(0, 0, -10);
}
