#define BOOST_TEST_MODULE test_version

#include <boost/test/unit_test.hpp>

#include "ip_filter.h"

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
	// test data
	std::vector<std::vector<std::string>> test_ips = {
		{"1", "1", "1", "1"},
		{"1", "2", "3", "4"},
		{"10", "20", "30", "40"},
		{"1", "1", "1", "2"},
		{"255", "255", "255", "255"},
		{"192", "168", "1", "1"}
	};

	// expected data
	std::vector<std::vector<std::string>> expected = {
		{"255", "255", "255", "255"},
		{"192", "168", "1", "1"},
		{"10", "20", "30", "40"},
		{"1", "2", "3", "4"},
		{"1", "1", "1", "2"},
		{"1", "1", "1", "1"}
	};

	reverseLexSort(test_ips);

	BOOST_CHECK(test_ips.size() == expected.size());
	for (size_t i = 0; i < test_ips.size(); ++i) {
		BOOST_CHECK(test_ips[i] == expected[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()
