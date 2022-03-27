#include "Rectangle.hpp"

#include "algorithm"
#include "iostream"

Rectangle::Rectangle(int id_, int x_, int y_, int width_, int height_) : Figure(id_, x_, y_) {
    this->width = width_;
    this->height = height_;
}

void Rectangle::print() const {
    std::cout << "Rectangle " << id << ": x = " << x << " y = " << y
              << " width = " << width << " height = " << height << std::endl;
}

bool Rectangle::is_inside(int x_, int y_) const {
    int dx = std::abs(x - x_);
    int dy = std::abs(y - y_);

    return 2 * dx <= width && 2 * dy <= height;
}

void Rectangle::zoom(int factor) {
    this->width *= factor;
    this->height *= factor;
}



