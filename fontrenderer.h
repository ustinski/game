#ifndef FONTRENDERER_H
#define FONTRENDERER_H

class QString;

namespace FontRenderer
{
    void init();

    void setSize(int size);
    void draw(const QString &text, int x, int y, double scale = 1);
};

#endif // FONTRENDERER_H
