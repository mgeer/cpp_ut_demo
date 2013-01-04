#include "using_bytes.h"
#include "term.h"
#include <map>
using namespace UTSample;

class TermTest : public UsingBytes {
};

TEST_F(TermTest, it_euqals_by_content) {
	char* content = "abcd";
	Term term(content, 4);
	char* same_content = "abcd";
	Term same_term(content, 4);

	bool ret = term == same_term;
	ASSERT_TRUE(ret);

    ret = same_term == term;
    ASSERT_TRUE(ret);
}

TEST_F(TermTest, it_not_equal_when_size_is_different) {
    char* content = "abcd";
	Term term(content, 4);
	char* same_content = "abcd";
	Term another_term(content, 3);

	bool ret = term == another_term;
    ASSERT_FALSE(ret);

    ret = another_term == term;
    ASSERT_FALSE(ret);
}

TEST_F(TermTest, it_compares_terms_with_same_size) {
	Term term("abce", 4);
	Term small_term("abcd", 4);

	bool ret = small_term < term;
	ASSERT_TRUE(ret);
    ret = term < small_term;
    ASSERT_FALSE(ret);

	ret = term > small_term;
	ASSERT_TRUE(ret);
    ret = small_term > term;
    ASSERT_FALSE(ret);
}

TEST_F(TermTest, it_compares_terms_with_different_size) {
	Term term("abcde", 5);
	Term small_term("abcd", 4);
	bool ret = small_term < term;
	ASSERT_TRUE(ret);
    ret = term < small_term;
    ASSERT_FALSE(ret);

	ret = term > small_term;
	ASSERT_TRUE(ret);
    ret = small_term > term;
    ASSERT_FALSE(ret);
}


TEST_F(TermTest, it_founds_term_with_same_contnet_in_map) {
	char* content = "abcd";
	Term term(content, 4);
	std::map<Term, size_t> output;
	output[term] = 1;
	char* same_content = "abcd";
	Term same_term(content, 4);
	std::map<Term, size_t>::const_iterator at = output.find(same_term);
	bool not_found = at == output.end();
	ASSERT_FALSE(not_found);
}


