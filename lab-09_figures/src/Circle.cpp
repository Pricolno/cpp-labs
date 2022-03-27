#include "Circle.hpp"

#include <iostream>

Circle::Circle(int id, int x, int y, int radius, std::string label): Figure(id, x, y) {
    this->radius = radius;
    this->label = label;
}

void Circle::print() const {
    std::cout << "Circle " << id << ": x = " << x << " y = " << y
              << " radius = " << radius << " label = " << label << std::endl;
}

bool Circle::is_inside(int x_, int y_) const {
    int dx = std::abs(x - x_);
    int dy = std::abs(y - y_);
    return dx * dx + dy * dy <= radius * radius;
}

void Circle::zoom(int factor) {
    this->radius *= factor;
}