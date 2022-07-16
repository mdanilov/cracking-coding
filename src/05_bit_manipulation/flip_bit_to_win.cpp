// Flip Bit to Win: You have an integer and you can flip exactly one bit from a
// 13 to a 1. Write code to find the length of the longest sequence of ls you
// could create.
//
// EXAMPLE
// Input: 1775 (or: 11011101111)
// Output: 8
//
// Hints: #159, #226, #314, #352

#include <vector>

#include "utils/bits.h"

// Solution #1
// Complexity: time O(b), space O(b), where b is the length of the sequence
// ------------------------------------------------------------------------------------------------
/* Return a list of the sizes of the sequences. The sequence starts off with the
  number of 0s (which might be 0) and then alternates with the counts of each
  value.*/
std::vector<int> getAlternatingSequences(int n) {
  std::vector<int> sequences;

  int searchingFor = 0;
  int counter = 0;

  for (int i = 0; i < sizeof(int) * 8; ++i) {
    if ((n & 1) != searchingFor) {
      sequences.push_back(counter);
      searchingFor = n & 1;  // Flip 1 to 0 or 0 to 1
      counter = 0;
    }
    counter++;
    n = utils::logicalShift(n, 1);
  }
  sequences.push_back(counter);

  return sequences;
}

/* Given the lengths of alternating sequences of 0s and 1s, find the longest one
 * we can build. */
int findLongestSequence(const std::vector<int> &seq) {
  int maxSeq = 1;

  for (int i = 0; i < seq.size(); i += 2) {
    int zerosSeq = seq[i];
    int onesSeqRight = i - 1 >= 0 ? seq[i - 1] : 0;
    int onesSeqLeft = i + 1 < seq.size() ? seq[i + 1] : 0;

    int thisSeq = 0;
    if (zerosSeq == 1) {  // can merge
      thisSeq = onesSeqLeft + 1 + onesSeqRight;
    }
    if (zerosSeq > 1) {  // Just add a zero to either side
      thisSeq = 1 + std::max(onesSeqLeft, onesSeqRight);
    } else if (zerosSeq == 0) {  // No zero, but take either side
      thisSeq = std::max(onesSeqLeft, onesSeqRight);
    }
    maxSeq = std::max(thisSeq, maxSeq);
  }

  return maxSeq;
}

int longestSequence(int n) {
  if (n == -1) return sizeof(int) * 8;
  std::vector<int> sequences = getAlternatingSequences(n);
  return findLongestSequence(sequences);
}

// Solution #2
// Complexity: time O(b), space O(1), where b is the length of the sequence
// ------------------------------------------------------------------------------------------------
int flipBit(int a) {
  /* If all 1S, this is already the longest sequence. */
  if (~a == 0) return sizeof(int) * 8;

  int currentLength = 0;
  int previousLength = 0;
  int maxLength = 1;  // We can always have a sequence of at least one 1
  while (a != 0) {
    if ((a & 1) == 1) {  // Current bit is a 1
      currentLength++;
    } else if ((a & 1) == 0) {  // Current bit is a 0
      /* Update to 0 (if next bit is 0) or currentLength (if next bit is 1). */
      previousLength = (a & 2) == 0 ? 0 : currentLength;
      currentLength = 0;
    }
    maxLength = std::max(maxLength, previousLength + currentLength + 1);
    a = utils::logicalShift(a, 1);
  }
  return maxLength;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(FlipBitToWinTest, Trivial) {
  int n = 1775;  // 0b11011101111
  EXPECT_EQ(longestSequence(n), 8);
  EXPECT_EQ(flipBit(n), 8);
}
