#include "geometry.h"

Position Vector::operator+(const Position &pos) const {
    return pos + *this;
}

Rectangle Vector::operator+(const Rectangle &rect) const {
    return rect + *this;
}

Rectangles Vector::operator+(const Rectangles &rects) const {
    return rects + *this;
}
