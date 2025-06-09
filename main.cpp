#include <iostream>
#include <exception>
#include <vector>
#include <list>
#include <cmath>
#include <iomanip>
#include <type_traits>

template<typename T>
void print(T&& val) {
	if constexpr (std::is_same_v<std::remove_reference_t<T>, int>) {
		do {
			int tmp = val % 10;
			std::cout << tmp << std::endl;
			val = val / 10;
		} while (val != 0);
		std::cout << std::endl;
	}
	else if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string>) {
		std::cout << val << std::endl;
	}
	else if constexpr (std::is_same_v<std::remove_reference_t<T>, std::vector<typename std::remove_reference_t<T>::value_type>>) {
		for (const auto& el : val) {
			std::cout << el << ".";
		}
		std::cout << std::endl;
	}
	else {
		static_assert(false, "Unsupported type");
	}
}

int main() {
	try {
		print(12345);
		std::vector<int>v{ 1, 2, 3, 4, 5 };
		print(v);
		std::string text{ "text" };
		print(text);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}