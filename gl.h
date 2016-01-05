#ifndef GL_H
#define GL_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

class GLWidget;

namespace GL
{
    void init(GLWidget *widget);

    QOpenGLShaderProgram *texture();
    QOpenGLShaderProgram *refraction();

    const QMatrix4x4 &projection();
    void resize(int w, int h);
}

#endif // GL_H
