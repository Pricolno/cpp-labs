#include "Figure.hpp"

Figure::Figure(int id_, int x_, int y_) : id(id_), x(x_), y(y_) {}

Figure::~Figure() = default;

void Figure::move(int new_x, int new_y) {
    this->x = new_x;
    this->y = new_y;
}
