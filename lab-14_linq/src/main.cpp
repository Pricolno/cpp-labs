#include <iostream>
#include "linq.hpp"

int main() {
	int x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	//auto v = linq::from(x, x+5).take(4).to_vector();
	//auto v = linq::from(x, x+5).take(4).where([](int x) {return x < 3;}).to_vector();
	//auto v = linq::from(x, x+5).take(4).select([](int x) { return x * x; }).to_vector();
	//auto v = linq::from(x, x+5).take(4).select([](int x) { return x * x; }).where([](int x) {return x % 2 == 0;}).to_vector();
	//auto v = linq::from(x, x+9).take(6).drop(3).to_vector();
	//auto v = linq::from(x, x+9).take(6).select([](int x) { return x * x; }).until([](int x) { return x > 10; }).to_vector();
	//auto v = linq::from(x, x+9).take(6).select([](int x) { return x * x; }).until_eq(36).to_vector();
	//auto v = linq::from(x, x+9).take(6).select([](int x) { return x * x; }).where_neq(25).to_vector();

	/*
	std::istream_iterator<int> in(std::cin), eof;
	std::ostream_iterator<double> out(std::cout, "\n");
	linq::from(in, eof).select([](int x) { return x * x; }).copy_to(out);  // Вывести на экран
	*/

	auto v = linq::from(x, x+4).to_vector();
	
	for (auto el : v) {
		std::cout << el << " ";
	}
	

	return 0;
}
