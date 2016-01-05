#ifndef BUTTON_H
#define BUTTON_H

#include "mesh.h"

class Button
{
public:
    Button(const QString &text, int y);
	void reset();
	void select();
	void deselect();
    bool selected() { return _selected; }
    void draw() { (_selected || _animated ? maxFont : minFont).draw(); }
	void update(float dt);
    bool isUnderCursor(const QPoint &cursor)
    { return cursor.y() > _y - 50 && cursor.y() < _y + 50; }

private:
	bool _selected;
	bool _animated;

	double _scale;
    const double scaleMin;
    const double scaleMax;

    int _y;

    class MaxFont : public Mesh
    {
    public:
        MaxFont(const QString &texture, int x, int y) :
            Mesh(texture, x, y) {}
        void setScale(double *scale) { _scale = scale; }

    private:
        void prepareMatrix()
        {
            Mesh::prepareMatrix();
            model.scale(*_scale, *_scale, 1);
        }

        double *_scale;
    };

    Mesh minFont;
    MaxFont maxFont;
};

#endif // BUTTON_H
