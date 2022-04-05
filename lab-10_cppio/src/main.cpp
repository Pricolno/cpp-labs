#include <iostream>
#include <string>

#include "employees.h"

static EmployeesArray arr;

static void handle_add() {
    int type;
    std::cin >> type;

    std::unique_ptr<Employee> emp = EmployeeFactory::create(type);
    if (!emp) return;

    std::cin >> *emp;
    arr.add(std::move(emp));
}

static void handle_list() {
    std::cout << arr;
}

static void handle_load() {
    std::string filename;
    std::cin >> filename;

    std::ifstream in;
    in.open(filename, std::ios::binary);

    in >> arr;
}

static void handle_save() {
    std::string filename;
    std::cin >> filename;

    std::ofstream out;
    out.open(filename, std::ios::binary);

    out << arr;
}

int main() {
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "add")
            handle_add();
        else if (cmd == "list")
            handle_list();
        else if (cmd == "load")
            handle_load();
        else if (cmd == "save")
            handle_save();
        else if (cmd == "exit")
            break;
    }
}