#ifndef __FC_EXERCISE_TEST_USING_RESULT__
#define __FC_EXERCISE_TEST_USING_RESULT__
#include "using_bytes.h"
class UsingResult : public UsingBytes {
protected:
		void create_result(UTSample::Result* result, std::string head, std::string tail, size_t total_words) {
		std::vector<char> vector_head;
		for (size_t i = 0; i < head.size(); i++) {
			result->head.push_back(head[i]);
		}
		std::vector<char> vector_tail;
		for (size_t i = 0; i < tail.size(); i++) {
			result->tail.push_back(tail[i]);
		}

		UTSample::Output output;
		output.total_word_count = total_words;
		output.terms = std::map<UTSample::Term, size_t>();
		output.basic_words = std::map<UTSample::Term, size_t>();
		result->output = output;
	}
};

#endif

