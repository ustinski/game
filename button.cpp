#include "button.h"

Button::Button(const QString &text, int y) :
scaleMin(0.6666),
scaleMax(1),
_y(y),
minFont(text + QString::number(100), 0, y),
maxFont(text + QString::number(150), 0, y)
{
    maxFont.setScale(&_scale);
	reset();
}

void Button::reset()
{
	_selected = false;
	_animated = false;
	_scale = scaleMax;
}

void Button::select()
{
	_selected = true;
	_animated = true;

	_scale = scaleMin;
}

void Button::deselect()
{
	_selected = false;
	_animated = true;
}

void Button::update(float dt)
{
    if(!_animated) return;
    if(_selected) {
		_scale += dt;
        if(_scale >= scaleMax) {
			_scale = scaleMax;
			_animated = false;
		}
    } else {
		_scale -= dt;
        if(_scale <= scaleMin) {
			//when scale reaches scaleMin, font is changed from size150 to size100, so _scale is changed from min to max
			//this is done instead of regular scaling, because bigger font has fatter outline
			_scale = scaleMax;
			_animated = false;
		}
	}
}
