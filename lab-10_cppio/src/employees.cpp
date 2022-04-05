

#include "employees.h"

std::istream &operator>>(std::istream &in, Employee &emp) {
    emp.read_txt_from(in);
    return in;
}

std::ostream &operator<<(std::ostream &out, const Employee &emp) {
    emp.write_txt_to(out);
    return out;
}

std::istream &operator>>(std::ifstream &in, Employee &emp) {
    emp.read_bin_from(in);
    return in;
}

std::ostream &operator<<(std::ofstream &out, const Employee &emp) {
    emp.write_bin_to(out);
    return out;
}

enum EmpType {
    DEV = 1,
    MANAGER = 2
};

int Developer::getIntType() const {
    return EmpType::DEV;
}

int SalesManager::getIntType() const {
    return EmpType::MANAGER;
}

std::string Developer::getStrType() const {
    return "Developer";
}

std::string SalesManager::getStrType() const {
    return "Sales Manager";
}

void EmployeesArray::add(std::unique_ptr<Employee> e) {
    _employees.emplace_back(std::move(e));
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (const auto &emp : _employees)
        total += emp->salary();
    return total;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price / 100;
}

void Employee::read_txt_from(std::istream &in) {
    in >> _name >> _base_salary;
}

void Employee::write_txt_to(std::ostream &out) const {
    out << getStrType() << std::endl;
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
}

void Developer::read_txt_from(std::istream &in) {
    Employee::read_txt_from(in);
    in >> _has_bonus;
}

void Developer::write_txt_to(std::ostream &out) const {
    Employee::write_txt_to(out);
    out << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void SalesManager::read_txt_from(std::istream &in) {
    Employee::read_txt_from(in);
    in >> _sold_nm >> _price;
}

void SalesManager::write_txt_to(std::ostream &out) const {
    Employee::write_txt_to(out);
    out << "Sold items: " << _sold_nm << std::endl;
    out << "Item price: " << _price << std::endl;
}

std::ostream &operator<<(std::ostream &out, const EmployeesArray &arr) {
    for (std::size_t i = 0; i < arr._employees.size(); ++i) {
        const auto &emp = arr._employees[i];
        out << i + 1 << ". ";
        out << *emp;
    }
    out << "== Total salary: " << arr.total_salary() << std::endl << std::endl;
    return out;
}

static std::string read_c_str(std::ifstream &in) {
    std::string str;
    char c;
    while (in >> c && c)
        str += c;
    return str;
}

static void write_c_str(std::ofstream &out, const std::string &str) {
    out.write(str.c_str(), str.size() + 1);
}

void Employee::write_bin_to(std::ofstream &out) const {
    int type = getIntType();
    out.write((const char *) &type, sizeof(int32_t));

    write_c_str(out, _name);
    out.write((const char *) &_base_salary, sizeof(int32_t));
}

void Employee::read_bin_from(std::ifstream &in) {
    _name = read_c_str(in);
    in.read((char *) &_base_salary, sizeof(int32_t));
}

void Developer::write_bin_to(std::ofstream &out) const {
    Employee::write_bin_to(out);
    out.write((const char *) &_has_bonus, sizeof(bool));
}

void Developer::read_bin_from(std::ifstream &in) {
    Employee::read_bin_from(in);
    in.read((char *) &_has_bonus, sizeof(bool));
}

void SalesManager::write_bin_to(std::ofstream &out) const {
    Employee::write_bin_to(out);
    out.write((const char *) &_sold_nm, sizeof(int32_t));
    out.write((const char *) &_price, sizeof(int32_t));
}

void SalesManager::read_bin_from(std::ifstream &in) {
    Employee::read_bin_from(in);
    in.read((char *) &_sold_nm, sizeof(int32_t));
    in.read((char *) &_price, sizeof(int32_t));
}

std::ostream &operator<<(std::ofstream &out, const EmployeesArray &arr) {
    auto size = (int32_t) arr._employees.size();
    out.write((const char *) &size, sizeof(int32_t));
    for (const auto &emp : arr._employees)
        out << *emp;
    return out;
}

std::istream &operator>>(std::ifstream &in, EmployeesArray &arr) {
    int32_t size;
    in.read((char *) &size, sizeof(int32_t));
    for (; size > 0; --size) {
        int32_t type;
        in.read((char *) &type, sizeof(int32_t));

        std::unique_ptr<Employee> emp = EmployeeFactory::create(type);
        if (!emp) continue;

        in >> *emp;
        arr.add(std::move(emp));
    }
    return in;
}

std::unique_ptr<Employee> EmployeeFactory::create(int type) {
    if (type == EmpType::DEV)
        return std::make_unique<Developer>();
    else if (type == EmpType::MANAGER)
        return std::make_unique<SalesManager>();
    return nullptr;
}