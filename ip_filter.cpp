#include "ip_filter.h"

#include <fstream>
#include <algorithm>

std::vector<std::string> split(const std::string& str, char d) {
	std::vector<std::string> r;

	std::string::size_type start = 0;
	auto stop = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

std::vector<std::vector<std::string>> getFirstPartOfSplitedVector(const std::string& fileName) {
	std::fstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + fileName);
	}

	std::vector<std::vector<std::string>> data;
	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> v = split(line, '\t');
		data.push_back(split(v.at(0), '.'));
	}

	return data;
}

void print(const std::vector<std::vector<std::string>>& data) {
	for (auto ip = data.cbegin(); ip != data.cend(); ++ip) {
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
			if (ip_part != ip->cbegin()) {
				std::cout << ".";
			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

void reverseLexSort(std::vector<std::vector<std::string>>& data) {
	//std::sort(data.back(), data.end());
}

