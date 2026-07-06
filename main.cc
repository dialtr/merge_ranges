#include <cassert>
#include <compare>
#include <cstddef>
#include <iostream>
#include <set>

class Range {
 public:
  size_t start = 0;
  size_t end = 0;
  auto operator <=>(const Range&) const = default;
};

void RangeTest() {
  Range a{{0}, {10}};
  Range b{{0}, {20}};
  Range c{{20}, {30}};
  assert(a < b);
  assert(b < c);
  assert(a < c);
}

class RangeSet {
 public:
  enum { kOk = 0, kCollision = 1 };

  struct Result {
    int status = kOk;
    Range range{{0}, {0}};
  };

	Result Add(const Range& range) {
		Result r;
		return r;
	}

 private:
  std::set<Range> ranges_;
};

int main(int argc, char* argv[]) {
  RangeTest();
  return 0;
}
