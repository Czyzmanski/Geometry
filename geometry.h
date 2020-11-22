#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdint>
#include <vector>
#include <utility>


class Vector {
private:
    int32_t m_x;
    int32_t m_y;
public:
    Vector() = delete;

    Vector(int32_t x, int32_t y) : m_x(x), m_y(y) {}

    ~Vector() = default;

    Vector(const Vector &vec) = default;

    Vector &operator=(const Vector &vec) = default;

    Vector(Vector &&vec) = default;

    Vector &operator=(Vector &&vec) = default;

    bool operator==(const Vector &vec) const {
        return m_x == vec.m_x && m_y == vec.m_y;
    }

    int32_t x() const {
        return m_x;
    };

    int32_t y() const {
        return m_y;
    }

    Vector reflection() const {
        return Vector{m_y, m_x};
    }

    Vector &operator+=(const Vector &vec) {
        m_x += vec.m_x;
        m_y += vec.m_y;
        return *this;
    }
};


class Position {
private:
    int32_t m_x;
    int32_t m_y;
public:
    Position() = delete;

    Position(int32_t x, int32_t y) : m_x(x), m_y(y) {}

    ~Position() = default;

    Position(const Position &pos) = default;

    Position &operator=(const Position &pos) = default;

    Position(Position &&pos) = default;

    Position &operator=(Position &&pos) = default;

    bool operator==(const Position &pos) const {
        return m_x == pos.m_x && m_y == pos.m_y;
    }

    int32_t x() const {
        return m_x;
    }

    int32_t y() const {
        return m_y;
    }

    Position reflection() const {
        return Position{m_y, m_x};
    }

    Position &operator+=(const Vector &vec) {
        m_x += vec.x();
        m_y += vec.y();
        return *this;
    }

    static Position &origin() {
        static Position position{0, 0};
        return position;
    }
};


class Rectangle {
private:
    uint32_t m_width;
    uint32_t m_height;
    Position m_pos;
public:
    Rectangle() = delete;

    Rectangle(uint32_t width, uint32_t height) : m_width(width), m_height(height),
                                                 m_pos(Position::origin()) {}

    Rectangle(uint32_t width, uint32_t height,
              const Position &pos) : m_width(width), m_height(height), m_pos(pos) {}

    ~Rectangle() = default;

    Rectangle(const Rectangle &rect) = default;

    Rectangle &operator=(const Rectangle &rect) = default;

    Rectangle(Rectangle &&rect) = default;

    Rectangle &operator=(Rectangle &&rect) = default;

    bool operator==(const Rectangle &rect) const {
        return m_width == rect.m_width
               && m_height == rect.m_height
               && m_pos == rect.m_pos;
    }

    uint32_t width() const {
        return m_width;
    }

    uint32_t height() const {
        return m_height;
    }

    const Position &pos() const {
        return m_pos;
    }

    Rectangle reflection() const {
        return Rectangle{m_height, m_width, m_pos.reflection()};
    }

    Rectangle &operator+=(const Vector &vec) {
        m_pos += vec;
        return *this;
    }

    uint64_t area() const {
        return (uint64_t) m_width * (uint64_t) m_height;
    }
};


class Rectangles {
private:
    std::vector<Rectangle> rectangles;
public:
    Rectangles() = default;

    Rectangles(std::initializer_list<Rectangle> rectangles) : rectangles(rectangles) {}

    ~Rectangles() = default;

    const Rectangle &operator[](std::size_t i) const {
        return rectangles[i];
    }

    std::size_t size() const {
        return rectangles.size();
    }

    bool operator==(const Rectangles &rects) const {
        return rectangles == rects.rectangles;
    }

    Rectangles &operator+=(const Vector &vec) {
        for (Rectangle &rect : rectangles) {
            rect += vec;
        }
        return *this;
    }
};

#endif // GEOMETRY_H
