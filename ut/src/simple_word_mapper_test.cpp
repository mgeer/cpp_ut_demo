#include "using_bytes.h"
#include "simple_word_mapper.h"
using namespace UTSample;

class SimpleWordMapperTest : public UsingBytes {
protected:
	SimpleWordMapper mapper;
};

TEST_F(SimpleWordMapperTest, it_finds_out_word_seperated_by_tab) {
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\thello\tblablabla\n";
	std::vector<Term> terms, basic_words;
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(1, terms.size());
}

TEST_F(SimpleWordMapperTest, it_finds_out_nothing_when_eighth_tab_is_not_found) {
    std::string line = "1\t2\t3\t4\tblablabla\n";
    std::vector<Term> terms, basic_words;
    mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
    ASSERT_EQ(0, terms.size());
    ASSERT_EQ(0, basic_words.size());
}

TEST_F(SimpleWordMapperTest, it_finds_out_nothing_when_nineth_tab_is_not_found) {
    std::string line = "1\t2\t3\t4\t5\t6\t7\t8\thellotblablabla\n";
    std::vector<Term> terms, basic_words;
    mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
    ASSERT_EQ(0, terms.size());
    ASSERT_EQ(0, basic_words.size());
}

TEST_F(SimpleWordMapperTest, it_seperates_words_with_blank) {
	std::vector<Term> terms, basic_words;
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\thello world\tblablabla\n";
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(2, terms.size());
}

TEST_F(SimpleWordMapperTest, it_uses_terms_count_as_total_words_count) {
	Term hello("hello", 5);
	Term world("world", 5);
	Term basic("world", 5);
	std::vector<Term> terms, basic_words;
	terms.push_back(hello);
	terms.push_back(world);
	basic_words.push_back(basic);

	Output output;
	mapper.map(terms, basic_words, output);
	ASSERT_EQ(2, output.total_word_count);
}

TEST_F(SimpleWordMapperTest, it_adds_cut_terms_to_terms_only) {
	std::vector<Term> terms, basic_words;
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\thello world\tblablabla\n";
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(2, terms.size());
	ASSERT_EQ(0, basic_words.size());
	ASSERT_TEXT("hello", terms[0].content, terms[0].size);
	ASSERT_TEXT("world", terms[1].content, terms[1].size);
}

TEST_F(SimpleWordMapperTest, it_adds_single_term_to_terms_and_basic_words) {
	std::vector<Term> terms, basic_words;
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\tbasic\tblablabla\n";
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(1, terms.size());
	ASSERT_TEXT("basic", terms[0].content, terms[0].size);
	ASSERT_EQ(1, basic_words.size());
	ASSERT_TEXT("basic", basic_words[0].content, basic_words[0].size);
}

TEST_F(SimpleWordMapperTest, it_maps_for_offset) {
	std::vector<Term> terms, basic_words;
	std::string str = "headdata\n1\t2\t3\t4\t5\t6\t7\t8\thello world\tblablabla\n";
	mapper.map(str.c_str(), 9, str.size() - 9, terms, basic_words);
	ASSERT_EQ(2, terms.size());
	ASSERT_TEXT("hello", terms[0].content, terms[0].size);
	ASSERT_TEXT("world", terms[1].content, terms[1].size);
}

TEST_F(SimpleWordMapperTest, it_updates_terms) {
	std::vector<Term> terms, basic_words;
	Term hello("hello", 5);
	terms.push_back(hello);
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\thello world\tblablabla\n";
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(3, terms.size());
	ASSERT_TEXT("hello", terms[0].content, terms[0].size);
	ASSERT_TEXT("hello", terms[1].content, terms[1].size);
	ASSERT_TEXT("world", terms[2].content, terms[2].size);
}

TEST_F(SimpleWordMapperTest, it_updates_basic_words) {
	std::vector<Term> terms, basic_words;
	Term basic("basic", 5);
	basic_words.push_back(basic);
	std::string line = "1\t2\t3\t4\t5\t6\t7\t8\tbasic\tblablabla\n";
	mapper.map(line.c_str(), 0, line.size(), terms, basic_words);
	ASSERT_EQ(2, basic_words.size());
	ASSERT_TEXT("basic", basic_words[0].content, basic_words[0].size);
	ASSERT_TEXT("basic", basic_words[1].content, basic_words[1].size);
}

TEST_F(SimpleWordMapperTest, it_maps_another_output) {
	Term hello("hello", 5);
	Term world("world", 5);
	Term basic("basic", 5);
	Term any("any", 3);
	Output output1;
	output1.total_word_count = 2;
	output1.terms[hello] = 1;
	output1.basic_words[basic] = 1;
	
	Output output2;
	output2.total_word_count = 5;
	output2.terms[hello] = 1;
	output2.terms[world] = 1;
	output2.basic_words[basic] = 1;
	output2.basic_words[any] = 2;

	mapper.map(output1, output2);

	ASSERT_EQ(7, output1.total_word_count);
	ASSERT_EQ(2, output1.terms[hello]);
	ASSERT_EQ(1, output1.terms[world]);
	ASSERT_EQ(2, output1.basic_words[basic]);
	ASSERT_EQ(2, output1.basic_words[any]);
}

TEST_F(SimpleWordMapperTest, it_maps_terms_into_output) {
	Term a("a", 1);
	Term b("b", 1);
	Term c("c", 1);

	std::vector<Term> terms;
	terms.push_back(a);
	terms.push_back(b);
	terms.push_back(c);
	
	terms.push_back(a);
	terms.push_back(b);
	terms.push_back(c);

	std::vector<Term> basic_words;
	basic_words.push_back(a);
	basic_words.push_back(a);

	Output output;
	mapper.map(terms, basic_words, output);

	ASSERT_EQ(6, output.total_word_count);
	ASSERT_EQ(2, output.terms[a]);
	ASSERT_EQ(2, output.terms[b]);
	ASSERT_EQ(2, output.terms[c]);

	ASSERT_EQ(2, output.basic_words[a]);
}


