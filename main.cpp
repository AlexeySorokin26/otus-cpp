
#include "ip_filter.h"

int main(int argc, char const* argv[]) {
	try {
		const std::string fileName = "ip_filter.tsv"; // we should get copy of this file in build folder from cmake
		auto ip_pool = getFirstPartOfSplitedVector(fileName);
		reverseLexSort(ip_pool);
		print(ip_pool);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
