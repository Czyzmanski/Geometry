#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <utility>


class Position;


class Rectangle;


class Rectangles;


class Vector {
private:
    int32_t m_x;
    int32_t m_y;
public:
    Vector() = delete;

    Vector(int32_t x, int32_t y) : m_x{x}, m_y{y} {}

    ~Vector() = default;

    Vector(const Vector &vec) = default;

    explicit Vector(const Position &pos);

    Vector &operator=(const Vector &vec) = default;

    Vector(Vector &&vec) = default;

    Vector &operator=(Vector &&vec) = default;

    explicit operator Position() const;

    Vector operator+(const Vector &vec) const {
        return Vector{m_x + vec.x(), m_y + vec.y()};
    }

    Position operator+(const Position &pos) const;

    Rectangle operator+(const Rectangle &rect) const;

    Rectangles operator+(const Rectangles &rects) const;

    Rectangles operator+(Rectangles &&rects) const;

    bool operator==(const Vector &vec) const {
        return m_x == vec.m_x && m_y == vec.m_y;
    }

    int32_t x() const {
        return m_x;
    }

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
    Vector vec;
public:
    Position() = delete;

    Position(int32_t x, int32_t y) : vec{x, y} {}

    ~Position() = default;

    Position(const Position &pos) = default;

    explicit Position(const Vector &vec) : vec{vec} {}

    Position &operator=(const Position &pos) = default;

    Position(Position &&pos) = default;

    Position &operator=(Position &&pos) = default;

    explicit operator Vector() const {
        return vec;
    }

    Position operator+(const Vector &vec) const {
        return (Position) (this->vec + vec);
    }

    bool operator==(const Position &pos) const {
        return vec == pos.vec;
    }

    int32_t x() const {
        return vec.x();
    }

    int32_t y() const {
        return vec.y();
    }

    Position reflection() const {
        return (Position) vec.reflection();
    }

    Position &operator+=(const Vector &vec) {
        this->vec += vec;

        return *this;
    }

    static const Position &origin() {
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

    Rectangle(int64_t width, int64_t height,
              const Position &pos = Position::origin()) : m_pos{pos} {
        if (width <= 0 || height <= 0) {
            exit(EXIT_FAILURE);
        }

        m_width = (uint32_t) width;
        m_height = (uint32_t) height;
    }

    ~Rectangle() = default;

    Rectangle(const Rectangle &rect) = default;

    Rectangle &operator=(const Rectangle &rect) = default;

    Rectangle(Rectangle &&rect) = default;

    Rectangle &operator=(Rectangle &&rect) = default;

    Rectangle operator+(const Vector &vec) const {
        return Rectangle{m_width, m_height, m_pos + vec};
    }

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
        m_pos = m_pos + vec;

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

    Rectangles(std::initializer_list<Rectangle> rects) : rectangles{rects} {}

    ~Rectangles() = default;

    Rectangles(const Rectangles &rects) = default;

    Rectangles &operator=(const Rectangles &rects) = default;

    Rectangles(Rectangles &&rects) = default;

    Rectangles &operator=(Rectangles &&rects) = default;

    Rectangles operator+(const Vector &vec) const {
        Rectangles result{*this};
        result += vec;

        return result;
    }

    Rectangle &operator[](size_t i) {
        return rectangles[i];
    }

    const Rectangle &operator[](size_t i) const {
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


Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_all(const Rectangles &rects);

#endif // GEOMETRY_H
