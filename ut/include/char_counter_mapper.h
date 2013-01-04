#include "mapper.h"

class CharCounterMapper : public UTSample::Mapper {
public:
	void map(UTSample::Output& first, UTSample::Output& another) {
		first.total_word_count += another.total_word_count;
	}

	void map(const char* input, size_t offset, size_t count, 
            std::vector<UTSample::Term>& terms, std::vector<UTSample::Term>& basic_words) {
		size_t line_count_without_return = count - 1;
		for (size_t i = 0, i_end = line_count_without_return; i < i_end; i++) {
			terms.push_back(UTSample::Term(input + offset + i, 1));
		}
	}
	
	void map(std::vector<UTSample::Term>& terms, std::vector<UTSample::Term>& basic_words, 
                                                                    UTSample::Output& output) {
		output.total_word_count += terms.size();
	}
};

