#include <cassert>
#include <compare>
#include <cstddef>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>

using std::cout;
using std::endl;

// This program demonstrates an algorithm for merging a set of numeric ranges
// that may contain overlaps into a minimal set that covers the same range
// with no overlaps. Numeric ranges are represented by a Range object
// consisting of a [start, end) point.
//
// The Merge() function returns a MergeResult object that contains the
// following members:
//
// 1. ranges   - The minimal set of ranges covering the input.
// 2. gaps     - A set of ranges that span gaps between the above.
// 3. overlaps - The count of overlapping ranges / conflicts detected.

// Range: a range on a number line covering [start, end).
class Range {
 public:
  size_t start = 0;
  size_t end = 0;
  auto operator<=>(const Range&) const = default;
};

// Canonical stream inseration operator for a Range.
std::ostream& operator<<(std::ostream& os, const Range& r) {
  os << "Range [" << r.start << ", " << r.end << ")";
  return os;
}

// MergeResult: described in more detail above.
struct MergeResult {
  std::set<Range> ranges;
  std::set<Range> gaps;
  int overlaps = 0;
};

// MergeRanges() merges a set of input ranges, providing a result that
// includes the minimal set output ranges, the gaps between those ranges,
// and the number of overlaps that were detected in the input set during
// processing.
[[nodiscard]] MergeResult MergeRanges(const std::set<Range> input_set) {
  MergeResult result;

  // Handle the degenerate case: an empty input set.
  if (input_set.size() == 0) {
    return result;
  }

  // Initialize values to track the current range with the first item.
  auto it = input_set.begin();
  Range current{{it->start}, {it->end}};
  ++it;

  // For all remaining ranges in the input set..
  for (; it != input_set.end(); ++it) {
    if (it->start < current.end) {
      // The item under consideration conflicts with current range, so we
      // merge it into the current range and increment the overlap counter.
      ++result.overlaps;
      current.end = it->end;
    } else if (it->start == current.end) {
      // The item under consideration perfectly extends the current range,
      // so we me merge it without incrementing the overlap counter.
      current.end = it->end;
    } else if (it->start > current.end) {
      // The item under consideration is disjoint from the current range;
      // add the current range to the output set.
      result.ranges.insert(current);
      // Add the gap beteeen the end of that range and the start of the
      // item under consideration.
      result.gaps.insert(Range{{current.end}, {it->start}});
      // Finally, update the current range to be the same as this item.
      current.start = it->start;
      current.end = it->end;
    }
  }

  // Finally, we add the current range left over upon completing the loop.
  result.ranges.insert(current);

  // Return the merged set.
  return result;
}

int main(int argc, char* argv[]) {
  // Define some ranges.
  Range a{{0}, {10}};
  Range b{{10}, {20}};
  Range c{{30}, {40}};
  Range d{{40}, {50}};
  Range e{{45}, {65}};  // overlaps previous and next
  Range f{{60}, {70}};

  std::set<Range> ranges{a, b, c, d, e, f};

  auto result = MergeRanges(ranges);

  if (result.overlaps > 0) {
    cout << "There were merge overlaps." << endl;
  } else {
    cout << "No merge overlaps detected." << endl;
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
