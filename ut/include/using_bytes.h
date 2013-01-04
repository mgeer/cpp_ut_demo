#ifndef __FC_EXERCISE_TEST_USING_BYTES__
#define __FC_EXERCISE_TEST_USING_BYTES__
#include <gtest.h>
#include <vector>
#include "result.h"
#include "fixture_path.h"

class UsingBytes : public testing::Test {
public:
	void ASSERT_TEXT(std::string expected_text, const char* actualBytes, size_t actual_size) {
		char* buffer = new char[actual_size + 1];
		strncpy(buffer, actualBytes, actual_size);
		buffer[actual_size] = 0;
		std::string actual_text = buffer;
		ASSERT_EQ(expected_text, actual_text);
		delete[] buffer;
	}

	void ASSERT_TEXT(std::string expected_text, std::vector<char> actual) {
		char* buffer = new char[actual.size()];
		std::vector<char>::iterator ite = actual.begin();
		size_t index = 0;
		while (ite!=actual.end()) {
			buffer[index] = *ite;
			++ite;
			++index;
		}
		ASSERT_TEXT(expected_text, buffer, actual.size());
		delete[] buffer;
	}
};
#endif

