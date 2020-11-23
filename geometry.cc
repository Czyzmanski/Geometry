#include <cstdlib>
#include "geometry.h"

Vector::Vector(const Position &pos) : m_x{pos.x()}, m_y{pos.y()} {}

Vector::operator Position() const {
    return Position{m_x, m_y};
}

Position Vector::operator+(const Position &pos) const {
    return pos + *this;
}

Rectangle Vector::operator+(const Rectangle &rect) const {
    return rect + *this;
}

Rectangles Vector::operator+(const Rectangles &rects) const {
    return rects + *this;
}

namespace {
    inline bool horizontal_merge(const Rectangle &rect1, const Rectangle &rect2) {
        return rect1.width() == rect2.width()
               && rect1.pos().x() == rect2.pos().x()
               && rect1.pos().y() + rect1.height() == rect2.pos().y();
    }

    inline bool vertical_merge(const Rectangle &rect1, const Rectangle &rect2) {
        return rect1.height() == rect2.height()
               && rect1.pos().y() == rect2.pos().y()
               && rect1.pos().x() + rect1.width() == rect2.pos().x();
    }
}

inline Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
    if (!horizontal_merge(rect1, rect2)) {
        exit(EXIT_FAILURE);
    }

    return Rectangle{rect1.width(), rect1.height() + rect2.height(), rect1.pos()};
}

inline Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
    if (!vertical_merge(rect1, rect2)) {
        exit(EXIT_FAILURE);
    }

    return Rectangle{rect1.width() + rect2.width(), rect1.height(), rect1.pos()};
}

Rectangle merge_all(const Rectangles &rects) {
    if (rects.size() == 0) {
        exit(EXIT_FAILURE);
    }

    Rectangle acc = rects[0];

    for (size_t i = 1; i < rects.size(); i++) {
        if (horizontal_merge(acc, rects[i])) {
            acc = merge_horizontally(acc, rects[i]);
        }
        else if (vertical_merge(acc, rects[i])) {
            acc = merge_vertically(acc, rects[i]);
        }
        else {
            exit(EXIT_FAILURE);
        }
    }

    return acc;
}
