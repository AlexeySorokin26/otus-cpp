
#include "own_allocator.h"

#include <exception>
#include <iostream>
#include <vector>

int main(int argc, char const* argv[]) {
	try {
		const int count = 100;
		pool_allocator<TestData> pool(count);
		std::vector<TestData*> data;
		for (int i = 0; i < count; ++i) {
			TestData* obj = pool.get_next();
			new(obj) TestData(i, i + 1);
			data.push_back(obj);
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
