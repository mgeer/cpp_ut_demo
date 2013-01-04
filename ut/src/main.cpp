#include <gtest.h>
#include <stdio.h>

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	int result;
    result = RUN_ALL_TESTS();
	return result;
}

