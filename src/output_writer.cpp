#include "output_writer.h"

namespace UTSample {

std::string to_string(const Term& term) {
    return std::string(term.content, term.content + term.size);
}

size_t OutputWriter::write(const Output& output) {
    FILE *file_ptr = fopen(file, "w");
    if (NULL == file_ptr) {
        return 0;
    }
    std::stringstream ss;
    ss << "basic words:\n";
    std::map<Term, size_t>::const_iterator iter;

    for (iter = output.basic_words.begin(); iter != output.basic_words.end(); iter++) {
        ss << to_string((*iter).first) 
            << "(" << (*iter).second << "/" 
            << output.total_word_count << ")" << '\t';
    }
    ss << "\nterms:\n";
    for (iter = output.terms.begin(); iter != output.terms.end(); iter++) {
        ss << to_string((*iter).first) 
            << "(" << (*iter).second << "/" 
            << output.total_word_count << ")" << '\t';
    }
    ss << '\0';

    size_t file_size = ss.str().length();
    fwrite(ss.str().c_str(), 1, file_size, file_ptr);
    fclose(file_ptr);
    return file_size;
}

}
