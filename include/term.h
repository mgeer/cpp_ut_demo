#ifndef __UT_SAMPLE_TERM_H__
#define __UT_SAMPLE_TERM_H__
namespace UTSample {
struct Term {
	Term(const char* content, size_t size) : content(content), size(size) {}
	const char* content;
	size_t size;

	bool operator==(const Term& another) const {
		if (another.size != size) {
			return false;
		}
		size_t pointer = 0;
		for (; pointer < size && *(another.content + pointer) == *(content + pointer); pointer++);
		return pointer == size;
	}

	bool operator < (const Term& another) const {
		size_t pointer = 0;
		for (; pointer < another.size && pointer < size &&
            *(another.content + pointer) == *(content + pointer); pointer++) {}
		if (pointer == another.size || pointer == size) {
			return size < another.size;
		}
		return *(content + pointer) < *(another.content + pointer);
	}

	bool operator > (const Term& another) const {
		size_t pointer = 0;
		for (; pointer < another.size && pointer < size &&
			*(another.content + pointer) == *(content + pointer); pointer++) {}
		if (pointer == another.size || pointer == size) {
			return size > another.size;
		}
		return *(content + pointer) > *(another.content + pointer);
	}
};
}
#endif

