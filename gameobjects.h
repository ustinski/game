#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

class QOpenGLTexture;
class QImage;

namespace GameObjects
{
    void init();
    void draw();
    void update(double dt);
    void restart();

    int totalBubbles();
    int speed();
    int targetsLeft();
    int score();
    void decreaseScore();

    QOpenGLTexture *circle(int index);
    QOpenGLTexture *shadow(int index);
    QOpenGLTexture *refraction(int index);

    void addCannonBall(double cannonRotation);
    QOpenGLTexture *loadImage(const QImage &image);

    QOpenGLTexture *background();
};

#endif // GAMEOBJECTS_H
