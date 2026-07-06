# merge_ranges

## About

Sketch of an algorithm that merges numeric ranges into a minimal
non-overlapping subset. The implementation, **MergeRanges()**, also
returns a minimal set of gaps covering the area between the ranges,
as well as a count of overlaps detected in the input.

## Applications

### Merging Object Code Files

Programming tools such as EEPROM burners or MCU programmers (e.g. avrdude) can
use text-based input files that represent object code. A common file format
used in this application is the Intel HEX format, which represents object code
in a series of records in a hexadecimal format.

It is sometimes necessary to merge one or more HEX files (when linking them
into a single binary, for example) but when doing so, it's critical to avoid
conflicts that could arise.

Consider if two HEX files specified different data to be written to the same
addresses in a device: this would invariably lead to problems.

To resolve this, data can be modeled as a sequence of bytes starting and
ending at a specific address, and processed using **MergeRanges** to ensure
that there are no conflicts.

## Potential Improvements

Some ideas for improving the algorithm:

1. Make the function more generic, accepting iterators to operate on inputs
   and outputs, if practical.

2. Provide more context around overlaps / conflicts. Rather than just a
   counter, it would be interesting to record details information about the
   nature of the conflicts discovered during the merge.

3. For the application described (Merging object code) the Range structure
   could include the code itself. If so, overlaps could be allowed iff the
   merged data was not in conflict.
