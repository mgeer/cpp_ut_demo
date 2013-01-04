#include "word_cutter.h"
#include "using_bytes.h"

using namespace UTSample;
class WordCutterTest : public UsingBytes {
    protected:
    std::vector<Term> terms;
    WordCutter cutter;
    void cut(std::string word) {
        terms.clear();
        Term term(word.c_str(), word.size());
        cutter.cut(term, terms);
    }
};

TEST_F(WordCutterTest, it_cutts_words_by_blank) {
    cut("hello world");
    ASSERT_EQ(2, terms.size());
    ASSERT_TEXT("hello", terms[0].content, terms[0].size);
    ASSERT_TEXT("world", terms[1].content, terms[1].size);
}

TEST_F(WordCutterTest, it_trims_head_tail) {
    cut("  hello  ");
    ASSERT_EQ(1, terms.size());
    ASSERT_TEXT("hello",terms[0].content, terms[0].size);
}

TEST_F(WordCutterTest, it_get_empty_when_cut_blank) {
    cut(" ");
    ASSERT_EQ(0, terms.size());

    cut("");
    ASSERT_EQ(0, terms.size());
}
