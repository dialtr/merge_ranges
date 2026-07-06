#include <cassert>
#include <cstddef>
#include <iostream>

class Range {
 public:
  size_t offset = 0;
	size_t length = 0;
};

bool operator<(const Range& lhs, const Range& rhs) {
  if (lhs.offset < rhs.offset) {
		return true;
	} else if (lhs.offset > rhs.offset) {
		return false;
	} else if (lhs.length > rhs.length) {
		return true;
	} else if (lhs.length < rhs.length) {
		return false;
	}
	return false;
}

void RangeTest() {
	Range a{{0}, {10}};
	Range b{{0}, {20}};
	Range c{{10}, {10}};
	assert(b < a);
	assert(b < c);
	assert(a < c);
}

class RangeSet {
 public:
};

int main(int argc, char* argv[]) {
  RangeTest();
	return 0;
}
