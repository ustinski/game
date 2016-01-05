#include <QImage>
#include <QVector2D>

#include <iostream>
#include <math.h>

int main(int argc, char **argv)
{
    bool ok;
    int size = QString(argv[1]).toInt(&ok);
    if(!ok || size <= 0) {
        std::cerr << "Usage:\n"
                "    ./genTexture 50\n"
                "    ./genTexture 100\n"
                "    ./genTexture 150\n";
        exit(EXIT_FAILURE);
    }

    QImage image(size, size, QImage::Format_ARGB32);
    for(int i = 0; i < size; i++) for(int j = 0; j < size; j++) {
        QVector2D v_texcoord = QVector2D(j, i) / size;
        double R = size / double(2);
        QVector2D rv(j + 0.5 - R, i + 0.5 - R);
        double r = rv.length();
        if(r >= R - 2) {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
            continue;
        }

        double sinA = r / R;
        double A = asin(sinA);

        double n = 1.8;

        double sinB = sinA / n;
        double B = asin(sinB);
        double k = 1 - R * cos(A) * tan(A - B) / r;

        //transform k from {1/n, 1} to {0, 255}
        k = (n * k - 1) * 255 / (n - 1);

        image.setPixel(i, j, qRgba(k, k, k, 255));
    }
    image.save("refraction" + QString::number(size) + ".png");
}
