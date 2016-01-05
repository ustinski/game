#include "gameobjects.h"
#include "menu.h"
#include "sdlmixer.h"
#include "window.h"
#include "bubble.h"
#include "cannonball.h"
#include "background.h"

#include <qmath.h>

namespace GameObjects
{
    template <class T> class CircleContainer : public list <T*>
    {
    public:
        list <typename list <T*>::iterator> *destroyed()
        { return &_destroyed; }

    private:
        list <typename list <T*>::iterator> _destroyed;
    };

    int _totalBubbles, _speed, maxBubbles, _targetsLeft, _score;
    int targetsDestroyed;

    CircleContainer <Bubble> bubble;
    CircleContainer <CannonBall> cannonball;

    QOpenGLTexture* _circle[4];
    QOpenGLTexture* _shadow[4];
    QOpenGLTexture* _refraction[3];

    Background *_background;



    void initCircleTextures();

    void deleteDestroyedBubbles(double dt);
    void deleteDestroyedCannonBalls(double dt);
    void updateBubbles();
    void updateCannonBalls();

    void reset(Bubble *b);

    QOpenGLTexture *loadTexture(const QString &texture);
}


void GameObjects::init()
{
    _totalBubbles = 100;
    _speed = 500;
    //there are not more than maxBubbles bubbles on screen, if some is destroyed, new one is added afte 3 seconds pause
    maxBubbles = 5;
    _targetsLeft = _totalBubbles;
    _score = 0;

    initCircleTextures();
    _background = new Background();
}

void GameObjects::initCircleTextures()
{
    int i;
    _circle[0] = loadTexture("ball");
    for(i = 1; i < 4; i++) _circle[i] = loadTexture("bubble" + QString::number(50 * i));
    _shadow[0] = loadTexture("shadow15");
    for(i = 1; i < 4; i++) _shadow[i] = loadTexture("shadow" + QString::number(50 * i));

    for(i = 0; i < 3; i++) _refraction[i] = loadTexture("refraction" + QString::number(50 * (i + 1)));
}

void GameObjects::draw()
{
    _background->draw();

    list <Bubble*>::iterator i;
    list < CannonBall*> ::iterator j;
    for(i = bubble.begin(); i != bubble.end(); i++) (*i)->draw(Circle::SHADOW);
    for(j = cannonball.begin(); j != cannonball.end(); j++) (*j)->draw(Circle::SHADOW);
    for(i = bubble.begin(); i != bubble.end(); i++) (*i)->draw(Circle::BODY);
    for(j = cannonball.begin(); j != cannonball.end(); j++) (*j)->draw(Circle::BODY);
}

void GameObjects::update(double dt)
{
    //for (i = cannonball.begin(); i != cannonball.end(); i++) i->update();
    //_effCont.Update(dt);
    deleteDestroyedBubbles(dt);
    deleteDestroyedCannonBalls(dt);
    updateBubbles();
    updateCannonBalls();
}

void GameObjects::deleteDestroyedBubbles(double dt)
{
    list <list <Bubble*>::iterator>::iterator k = bubble.destroyed()->begin();
    while(k != bubble.destroyed()->end()) {
        Bubble &b = ***k;
        b.addDestroyedTime(dt);
        if(b.destroyedTime() > 3) {
            targetsDestroyed++;
            if(targetsDestroyed + maxBubbles <= _totalBubbles) reset(&b);
            else {
                delete &b;
                bubble.erase(*k);
            }
            k = bubble.destroyed()->erase(k);
            if(bubble.empty() && !Menu::menu()) Menu::switchToMenu();
        }
        else k++;
    }
}

void GameObjects::deleteDestroyedCannonBalls(double dt)
{
    list <list <CannonBall*>::iterator>::iterator l = cannonball.destroyed()->begin();
    while (l != cannonball.destroyed()->end()) {
        Circle &cb = ***l;
        cb.addDestroyedTime(dt);
        //cannonballs lie on ground for 5 seconds
        if (cb.destroyedTime() > 3) {
            //cb.stopEffect();
            delete &cb;
            cannonball.erase(*l);
            l = cannonball.destroyed()->erase(l);
        }
        else l++;
    }
}

void GameObjects::updateBubbles()
{
    for(list <Bubble*>::iterator j = bubble.begin(); j != bubble.end(); j++) {
        Bubble &b = **j;
        if(!b.exists()) continue;
        b.update();

        if(!b.contact()) continue;
        SdlMixer::pop().play();
        b.destroy();
        if(!Menu::menu()) {
            _targetsLeft--;
            //score depends on accuracy
            //score = ... 35 + A    A = |dist| * sin(dist, v)    v - cannonball's speed
            //						A = |[dist, e_v]|            e_v = v / |v|
            //if dist == 0, score = 100, if dist == 80 (max dist), score = 33
            const Circle &cb = b.ball();
            const QVector2D dist = cb.position() - b.position();
            _score += 3500 / (35 + abs(QVector3D::crossProduct(dist, cb.speed().normalized()).z()));
        }
        bubble.destroyed()->push_back(j);
    }
}

void GameObjects::updateCannonBalls()
{
    for(list<CannonBall*>::iterator i = cannonball.begin(); i != cannonball.end(); i++) {
        CannonBall &cb = **i;
        cb.update();
        if(!cb.exists() || !cb.contact()) continue;

        cb.destroy();
        cannonball.destroyed()->push_back(i);
    }
}

void GameObjects::decreaseScore()
{
    if(!Menu::menu()) _score -= 40;
    if(_score < 0) _score = 0;
}

void GameObjects::restart()
{
    //add (or replace) bubbles
    int replaced = 0;
    for(list <Bubble*>::iterator i = bubble.begin(); i != bubble.end(); i++) {
        reset(*i);
        replaced++;
    }
    for(; replaced < maxBubbles; replaced++) {
        Bubble *b = new Bubble();
        bubble.push_back(b);
        reset(b);
    }

    //_effCont.KillAllEffects();

    //is like _targetsLeft, but incremented in 3 seconds after destruction of bubble, before creating new one
    targetsDestroyed = 0;
    //is decremented just after destruction
    _targetsLeft = _totalBubbles;
    _score = 0;

    //cannonball.clear();
    bubble.destroyed()->clear();
    cannonball.destroyed()->clear();
}

void GameObjects::reset(Bubble *b)
{
    for(;;) {
        b->resetParams();
        list<Bubble*>::iterator j;
        for(j = bubble.begin(); j != bubble.end(); j++) {
            if(*j == b) continue;
            Bubble &b2 = **j;
            if((b->position() - b2.position()).length() <= b->radius() + b2.radius()) break;
        }
        if(j != bubble.end()) continue;

        list<CannonBall*>::iterator k;
        for(k = cannonball.begin(); k != cannonball.end(); k++) {
            CannonBall &cb = **k;
            if((b->position() - cb.position()).length() <= b->radius() + 100) break;
        }
        if(k == cannonball.end()) {
            b->resetAll();
            break;
        }
    }
}

QOpenGLTexture *GameObjects::loadTexture(const QString &texture)
{ return loadImage(QImage(":/textures/" + texture + ".png")); }

int GameObjects::totalBubbles()
{
    return _totalBubbles;
}

int GameObjects::speed()
{
    return _speed;
}

int GameObjects::targetsLeft()
{
    return _targetsLeft;
}

int GameObjects::score()
{
    return _score;
}

QOpenGLTexture *GameObjects::circle(int index)
{
    return _circle[index];
}

QOpenGLTexture *GameObjects::shadow(int index)
{
    return _shadow[index];
}

QOpenGLTexture *GameObjects::refraction(int index)
{ return _refraction[index]; }

void GameObjects::addCannonBall(double cannonRotation)
{
    cannonball.push_back(new CannonBall(cannonRotation));
}

QOpenGLTexture *GameObjects::loadImage(const QImage &image)
{
    QOpenGLTexture *t = new QOpenGLTexture(image.mirrored());
    t->setMinificationFilter(QOpenGLTexture::Nearest);
    t->setMagnificationFilter(QOpenGLTexture::Linear);
    t->setWrapMode(QOpenGLTexture::Repeat);
    return t;
}

QOpenGLTexture *GameObjects::background()
{ return _background->texture(); }
