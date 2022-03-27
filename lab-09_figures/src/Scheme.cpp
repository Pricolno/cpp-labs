#include "Scheme.hpp"


Scheme::Scheme(std::size_t capacity) {
    this->figures.reserve(capacity);
}

Scheme::~Scheme(){
    for(auto &fg : this->figures){
        delete fg;
    }
}


void Scheme::push_back_figure(Figure *fg) {
    this->figures.push_back(fg);
}

void Scheme::remove_figure(int id) {
    int ind = find_ind_fg(id);
    delete this->figures[ind];
    this->figures.erase(this->figures.begin() + ind);
}

int Scheme::find_ind_fg(int id_) const {
    for(std::size_t i = 0; i < this->figures.size(); i++){
        if(this->figures[i]->id == id_){
            return i;
        }
    }
    return -1;
}

void Scheme::print_all_figures() const {
    for(auto &fg : this->figures){
        fg->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    int ind = find_ind_fg(id);
    if(id != -1)
        this->figures[ind]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for(auto &fg : this->figures){
        if(fg->is_inside(x, y))
            return fg;
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    int ind = find_ind_fg(id);
    this->figures[ind]->move(new_x, new_y);
}



