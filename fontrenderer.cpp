#include "fontrenderer.h"
#include "mesh.h"

#include <map>

#include <QImage>
#include <QOpenGLTexture>

using namespace std;

namespace FontRenderer
{
    struct Symbol
    {
        int width;
        uchar *textureBits;
    };

    class Font : public map <char, Symbol>
    {
    public:
        Font(int height = 0)
        { _height = height; }

        int height() const
        { return _height; }

        const Symbol &operator[](char c) const
        { return at(c); }

    private:
        int _height;
    };

    int current;
    map <int, Font> fonts;



    void pushFont(int size);
    void addSpace(FontRenderer::Font *font);
    Symbol loadSymbol(int size, const QString &symbol);
}

void FontRenderer::init()
{
    pushFont(25);

    current = 25;
}

void FontRenderer::pushFont(int size)
{
    Font font(QImage(":/font/" + QString::number(size) + "/0.png").height());
    font.insert(pair <char, Symbol>('/', loadSymbol(size, "_sl")));
    font.insert(pair <char, Symbol>(':', loadSymbol(size, "_tp")));

    char c;
    for(c = '0'; c <= '9'; c++)
        font.insert(pair <char, Symbol>(c, loadSymbol(size, QString(c))));
    for(c = 'A'; c <= 'Z'; c++)
        font.insert(pair <char, Symbol>(c, loadSymbol(size, QString(c))));
    addSpace(&font);

    fonts.insert(pair <int, Font>(size, font));
}

void FontRenderer::addSpace(FontRenderer::Font *font)
{
    int width = (*font)['I'].width;
    int bitsLength = font->height() * width * 4;
    uchar *bits = new uchar[bitsLength];
    for(int i = 0; i < bitsLength; i++) bits[i] = 0;

    font->insert(pair <char, Symbol>(' ', {width, bits}));
}

void FontRenderer::setSize(int size)
{
    map <int, Font>::const_iterator i;
    for(i = fonts.begin(); i != fonts.end(); i++) if(size == i->first) break;
    if(i != fonts.end()) current = size;
}

void FontRenderer::draw(const QString &text, int x, int y, double scale)
{
    string str = text.toStdString();
    const Font &font = fonts[current];
    int i, j, k, l;

    int totalWidth = 0;
    for(i = 0; i < str.length(); i++) totalWidth += font[str[i]].width;

    uchar *bits = new uchar[font.height() * totalWidth * 4];
    for(i = 0; i < font.height(); i++) {
        int offset = 0;
        for(j = 0; j < str.length(); j++) {
            char c = str[j];
            const Symbol &currentSymbol = font[c];
            int width = currentSymbol.width;
            for(k = 0; k < width; k++) for(l = 0; l < 4; l++)
                bits[(i * totalWidth + (offset + k)) * 4 + l] = currentSymbol.textureBits[(i * width + k) * 4 + l];
            offset += width;
        }
    }

    QOpenGLTexture t(QImage(bits, totalWidth, font.height(), QImage::Format_ARGB32));
    Mesh(&t, x, y, totalWidth * scale, font.height() * scale).draw();
    delete[] bits;
}

FontRenderer::Symbol FontRenderer::loadSymbol(int size, const QString &symbol)
{
    QImage image(":/font/" + QString::number(size) + "/" + symbol + ".png");
    image = image.mirrored();


    int bitsLength = image.height() * image.width() * 4;
    uchar *bits = new uchar[bitsLength];
    for(int i = 0; i < bitsLength; i++) bits[i] = image.bits()[i];

    return {image.width(), bits};
}


































