#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "matrix.hpp"

typedef std::map<std::string, Matrix*> var_storage;

int main(int argc, char** argv){
	std::string cmd;
	var_storage vars;

	for (std::string reg : {"$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9"}) {
		vars[reg] = new Matrix(0, 0);
	}

	
	while (std::cin >> cmd) {
		if (cmd == "exit") {
			break;

		} else try{
			if (cmd == "load") {
				std::string reg, fname;
				std::cin >> reg >> fname;

				try {
					Matrix* m;
					m = Matrix::load_matrix_from_file(fname);

					delete vars[reg];
					vars[reg] = m;

				} catch (MatrixException &e) {
					std::cout << "LOAD: " << e.what() << "." << std::endl;
				} 

			} else if (cmd == "print") {
				std::string reg;
				std::cin >> reg;

				vars[reg]->print(std::cout);
			} else if (cmd == "add") {
				std::string reg1, reg2;
				std::cin >> reg1 >> reg2;

				try {
					*vars[reg1] += *vars[reg2];
				} catch (MatrixException &e) {
					std::cout << "ADD: " << e.what() << "." << std::endl;
				}

			} else if (cmd == "mul") {
				std::string reg1, reg2;
				std::cin >> reg1 >> reg2;

				try {
					*vars[reg1] *= *vars[reg2];
				} catch (MatrixException &e) {
					std::cout << "MUL: " << e.what() << "." << std::endl;
				} 
			} else if (cmd == "elem") {
				std::string reg, row, column;
				std::cin >> reg >> row >> column;

				try {
					std::cout << vars[reg]->get(stoi(row), stoi(column)) << std::endl;
				} catch (MatrixException &e) {
					std::cout << "ACCESS: " << e.what() << "." << std::endl;
				}
			}  else {
				std::cout << "Unknown command " << cmd << std::endl;
			}

		} catch (std::bad_alloc &e) {
			std::cout << "Unable to allocate memory." << std::endl;
		}

	}

	for (var_storage::iterator it = vars.begin(); it != vars.end(); ++it) {
		delete it->second;
	}
	
	return 0;
}