#include "refraction.h"
#include "gameobjects.h"
#include "gl.h"

#include <QOpenGLShaderProgram>

Refraction::Refraction(int radius, QOpenGLTexture *texture, double x, double y, int width, int height) : Mesh(texture, x, y, width, height),
_radius(radius)
{}

void Refraction::draw()
{
    _arrayBuf.bind();

    QOpenGLShaderProgram *program = GL::refraction();
    program->bind();
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));
    int fragmentLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(fragmentLocation);
    program->setAttributeBuffer(fragmentLocation, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

    prepareMatrix();
    program->setUniformValue("mvp_matrix", GL::projection() * model);
    program->setUniformValue("refraction", 0);
    _texture->bind(0);



    program->setUniformValue("background", 1);
    GameObjects::background()->bind(1);
    program->setUniformValue("position", _position);
    program->setUniformValue("radius", _radius);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}
