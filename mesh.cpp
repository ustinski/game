#include "mesh.h"
#include "gl.h"
#include "gameobjects.h"

Mesh::Mesh(const QString &texture, double x, double y)
{
    QImage image(":/textures/" + texture + ".png");
    init(GameObjects::loadImage(image), x, y, image.width(), image.height());
}

void Mesh::init(QOpenGLTexture *texture, double x, double y, int width, int height)
{
    _texture = texture;
    _position = {x, y};
    initVertices(width, height);
}

void Mesh::initVertices(int width, int height)
{
    const double hw = width / 2;
    const double hh = height / 2;
    vertices.resize(4);
    vertices[0] = {{-hw, -hh, 0}, {0, 0}};
    vertices[1] = {{ hw, -hh, 0}, {1, 0}};
    vertices[2] = {{ hw,  hh, 0}, {1, 1}};
    vertices[3] = {{-hw,  hh, 0}, {0, 1}};

    _arrayBuf.destroy();
    _arrayBuf.create();
    _arrayBuf.bind();
    _arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));
}

void Mesh::setPosition(double x, double y)
{
    _position.setX(x);
    _position.setY(y);
}

void Mesh::draw()
{
    _arrayBuf.bind();

    QOpenGLShaderProgram *program = GL::texture();
    program->bind();
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));
    int fragmentLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(fragmentLocation);
    program->setAttributeBuffer(fragmentLocation, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

    prepareMatrix();
    program->setUniformValue("mvp_matrix", GL::projection() * model);
    program->setUniformValue("texture", 0);
    _texture->bind(0);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}

void Mesh::prepareMatrix()
{
    model.setToIdentity();
    model.translate(QVector3D(_position.x(), _position.y(), 0));
}
