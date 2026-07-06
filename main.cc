#include <cassert>
#include <compare>
#include <cstddef>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>

using std::cout;
using std::endl;

class Range {
 public:
  size_t start = 0;
  size_t end = 0;
  auto operator<=>(const Range&) const = default;
};

std::ostream& operator<<(std::ostream& os, const Range& r) {
  os << "Range [" << r.start << ", " << r.end << ")";
  return os;
}

void RangeTest() {
  Range a{{0}, {10}};
  Range b{{0}, {20}};
  Range c{{20}, {30}};
  assert(a < b);
  assert(b < c);
  assert(a < c);
  cout << a << endl << b << endl << c << endl;
}

// Accept a set of ranges as input.
// Return a set of merged ranges as output, along with a bool indicating
// whether any collisions occurred in the ranges during coalescing.

struct MergeResult {
  std::set<Range> ranges;
  std::set<Range> gaps;
  int conflicts = 0;
};

[[nodiscard]] MergeResult Merge(std::set<Range> input_set) {
  // The results of the operation.
  MergeResult result;

  // Handle degenerate case: empty input set.
  if (input_set.size() == 0) {
    return result;
  }

  // Initialize current range to the first item's range.
  auto it = input_set.begin();
  size_t start = it->start;
  size_t end = it->end;
  ++it;

  // For all remaining ranges in the input set.
  for (; it != input_set.end(); ++it) {
    if (it->start < end) {
      // The range under consideration conflicts with current range, so we
      // merge it into the current range and set the conflict flag.
      ++result.conflicts;
      end = it->end;
    } else if (it->start == end) {
      // The range under consideration perfectly extends the current range,
      // so we me merge it without setting the conflict flag.
      end = it->end;
    } else if (it->start > end) {
      // The range under consideration is disjoint from the current range,
      // so we add the current range to the output set, and then reinitialize
      // the current range to the range of this item.
      result.ranges.insert(Range{{start}, {end}});
      // We also add a range to the set of gap ranges.
      result.gaps.insert(Range{{end}, {it->start}});
      start = it->start;
      end = it->end;
    }
  }

  // Finally, we add the current range left over upon completing the loop.
  result.ranges.insert(Range{{start}, {end}});

  // Return the merged set.
  return result;
}

int main(int argc, char* argv[]) {
  // RangeTest();

  Range a{{0}, {10}};
  Range b{{10}, {20}};
  Range c{{30}, {40}};
  Range d{{40}, {50}};
  Range e{{45}, {65}};  // conflict
  Range f{{60}, {70}};

  std::set<Range> ranges{a, b, c, d, e, f};

  auto result = Merge(ranges);

  if (result.conflicts > 0) {
    cout << "There were merge conflicts." << endl;
  } else {
    cout << "No merge conflicts detected." << endl;
  }

  cout << "Merged Ranges:" << endl;
  for (auto e : result.ranges) {
    cout << "  " << e << endl;
  }
  cout << "Gaps: " << endl;
  for (auto e : result.gaps) {
    cout << "  " << e << endl;
  }

  return 0;
}
