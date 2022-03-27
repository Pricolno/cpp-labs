#pragma once

#include "Figure.hpp"

#include <vector>


class Scheme {
public:
    explicit Scheme(std::size_t capacity);
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures() const;
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y); // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

private:
    int find_ind_fg(int id) const;

private:
    std::vector<Figure*> figures;
};
