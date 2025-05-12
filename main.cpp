#include "lib.h"

#include <iostream>

// for me 
// Оператор ?: в C++ приводит оба операнда к общему типу, если они разные.
// Это называется "usual arithmetic conversions".
//auto f(int a, float b) {
//	return (a < b) ? a : b;
//
//	// this will be 
//	? ? ? res; // ?? -? 
//	if (a < b) {
//		res = a;
//	}
//	else {
//		res = b;
//	}
//	return res;
// int main()
//{
//	int a = 10;
//	float b = 1.f;
//	f(a, b);
//}

//}

// the problem will be in usage of this function 
// compiler could not deduce the type of the function
// auto bar(int a, int b); 


// Мы отбрасываем const и ссыку у указателей оставляем то что принадлежит указателю 
//template <typename T>
//void func1(T param) {
//	// some very interesting code
//}
//// тут оставляем 
//template <typename T>
//void func2(T& param) {
//	// some very interesting code
//}
//// тут оставляем 
//template <typename T>
//void func3(T* param) {
//	// some very interesting code
//}
//template <typename T>
//void func4(T&& param) {
//	// some very interesting code
//}
//
//int main(int argc, char* argv[]) {
//	int i = 10;
//	const int ci = 15;
//	const int& cir = ci;
//	int* pi = &i;
//	const int* cpi = &i;
//	func1(i); // 1.1. param type ? int 
//	func1(ci); // 1.2. param type ? int 
//	func1(cir); // 1.3. param type ? int
//	func1(42); // 1.4. param type ? int 
//	func1(pi); // 1.5. param type ? int*
//	func1(cpi); // 1.6. param type ?const int*
//	func1({ 1 }); // 1.7. param type ?
//	func1({ 1, 2, 3 }); // 1.8. param type ?
//
//
//	func2(i); // 2.1. param type ? int& 
//	func2(ci); // 2.2. param type ? const int& 
//	func2(cir); // 2.3. param type ? const int& 
//	func2(42); // 2.4. param type ? почему нельзя ссылку на временный объект не констанутную
//	func2(pi); // 2.5. param type ? int*&
//	func2(cpi); // 2.6. param type ? const int*&
//
//	func3(i); // 3.1. param type ?
//	func3(ci); // 3.2. param type ?
//	func3(cir); // 3.3. param type ?
//	func3(42); // 3.4. param type ?
//	func3(pi); // 3.5. param type ?
//	func3(cpi); // 3.6. param type ?
//
//	func4(i); // 4.1. param type ?  int& && → int&
//	func4(ci); // 4.2. param type ? const int& && → const int&
//	func4(cir); // 4.3. param type ? const int& && → const int&
//	func4(42); // 4.4. param type ? int&&
//	func4(pi); // 4.5. param type ? int*& && → int*&
//	func4(cpi); // 4.6. param type ? const int*&
//	return 0;
//}


//#include <utility>
//int func_value() {
//	return 42;
//}
//int& func_ref() {
//	static int value = 42;
//	return value;
//}
//const int& func_cref() {
//	static const int value = 42;
//	return value;
//}
//int* func_ptr() {
//	static int value = 42;
//	return &value;
//}
//const int* func_cptr() {
//	static int value = 42;
//	return &value;
//}
//const int* const func_ccptr() {
//	static const int value = 42;
//	return &value;
//}
//int&& func_rref() {
//	int value = 42;
//	return std::move(value);
//}
//int main(int argc, char* argv[]) {
//	{
//		auto v1 = func_value(); // 1.1 - v1 type ?
//		auto& v2 = func_value(); // 1.2 - v2 type we have rvalue here?
//		const auto& v3 = func_value(); // 1.3 - v3 type ?
//		auto&& v4 = func_value(); // 1.4 - v4 type ?
//	}
//	{
//		auto v1 = func_ref(); // 2.1 - v1 type ?
//		auto& v2 = func_ref(); // 2.2 - v2 type ?
//		const auto& v3 = func_ref(); // 2.3 - v3 type ?
//		auto&& v4 = func_ref(); // 2.4 - v4 type ?
//	}
//	{
//		auto v1 = func_cref(); // 3.1 - v1 type ?
//		auto& v2 = func_cref(); // 3.2 - v2 type ?
//		const auto& v3 = func_cref(); // 3.3 - v3 type ?
//		auto&& v4 = func_cref(); // 3.4 - v4 type ?
//	}
//	{
//		auto v1 = func_ptr(); // 4.1 - v1 type ?
//		auto& v2 = func_ptr(); // 4.2 - v2 type ?
//		const auto& v3 = func_ptr(); // 4.3 - v3 type ?
//		auto&& v4 = func_ptr(); // 4.4 - v4 type ?
//	}
//	{
//		auto v1 = func_cptr(); // 5.1 - v1 type ?
//		auto& v2 = func_cptr(); // 5.2 - v2 type ?
//		const auto& v3 = func_cptr(); // 5.3 - v3 type ?
//		auto&& v4 = func_cptr(); // 5.4 - v4 type ?
//	}
//	{
//		auto v1 = func_ccptr(); // 6.1 - v1 type ?
//		auto& v2 = func_ccptr(); // 6.2 - v2 type ?
//		const auto& v3 = func_ccptr(); // 6.3 - v3 type ?
//		auto&& v4 = func_ccptr(); // 6.4 - v4 type ?
//	}
//	{
//		auto v1 = func_rref(); // 7.1 - v1 type ?
//		auto& v2 = func_rref(); // 7.2 - v2 type ?
//		const auto& v3 = func_rref(); // 7.3 - v3 type ?
//		auto&& v4 = func_rref(); // 7.4 - v4 type ?
//	}
//	{
//		auto v1(10); // 8.1 - v1 type ?
//		auto v2 = 10; // 8.2 - v2 type ?
//		auto v3{ 10 }; // 8.3 - v3 type ?
//		auto v4 = { 10 }; // 8.4 - v4 type ?
//		auto v5 = { 1, 2, 3 }; // 8.5 - v5 type ?
//		auto v6 = { 1, 2, 3.0 }; // 8.6 - v6 type ?
//	}
//	return 0;
//}

#include <string>
#include <tuple>
#include <cassert>
auto getPerson() {
	const std::string name = "Petia";
	const std::string secondName = "Ivanoff";
	const std::size_t age = 23;
	const std::string department = "Sale";
	return std::make_tuple(
		name, secondName, age, department
	);
}
int main(int argc, char* argv[]) {
	std::string name, secondName, department;
	std::size_t age;
	custom_tie(name, secondName, age, department) = getPerson();
	assert(name == "Petia");
	assert(secondName == "Ivanoff");
	assert(age == 23);
	assert(department == "Sale");
	return 0;
}