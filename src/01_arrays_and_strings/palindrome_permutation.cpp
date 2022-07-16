// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.
//
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat", "atco cta", etc.)
//
// Hints: #106, #121, #134, #136

#include <string>
#include <vector>

using namespace std;

// ------------------------------------------------------------------------------------------------

/* Map each character to a number. a -> 0, b -> 1, c -> 2, etc.
 * This is case insensitive. Non-letter characters map to -1. */
int getCharNumber(char c) {
  if ('a' <= c && c <= 'z') {
    return c - 'a';
  }
  return -1;
}

/* Count how many times each character appears. */
vector<int> buildCharFrequencyTable(const string &phrase) {
  vector<int> table('z' - 'a' + 1);
  for (char c : phrase) {
    int x = getCharNumber(c);
    if (x != -1) {
      table[x]++;
    }
  }
  return table;
}

/* Check that no more than one character has an odd count. */
bool checkMaxOneOdd(vector<int> &table) {
  bool foundOdd = false;
  for (int count : table) {
    if (count % 2 == 1) {
      if (foundOdd) {
        return false;
      }
      foundOdd = true;
    }
  }
  return true;
}

bool isPermutationOfPalindrome_1(const string &phrase) {
  vector<int> table = buildCharFrequencyTable(phrase);
  return checkMaxOneOdd(table);
}

// ------------------------------------------------------------------------------------------------

bool isPermutationOfPalindrome_2(const string &phrase) {
  int countOdd = 0;
  int table['z' - 'a' + 1] = {0};
  for (char c : phrase) {
    int x = getCharNumber(c);
    if (x != -1) {
      table[x]++;
      if (table[x] % 2 == 1) {
        countOdd++;
      } else {
        countOdd--;
      }
    }
  }
  return countOdd <= 1;
}

// ------------------------------------------------------------------------------------------------

/* Toggle the ith bit in the integer. */
int toggle(int bitVector, int index) {
  if (index < 0) return bitVector;
  int mask = 1 << index;
  if ((bitVector & mask) == 0) {
    bitVector |= mask;
  } else {
    bitVector &= ~mask;
  }
  return bitVector;
}

/* Create a bit vector for the string. For each letter with value i, toggle the
 * ith bit. */
int createBitVector(const string &phrase) {
  int bitVector = 0;
  for (char c : phrase) {
    int x = getCharNumber(c);
    bitVector = toggle(bitVector, x);
  }
  return bitVector;
}

/* Check that exactly one bit is set by subtracting one from the integer and
 * ANDing it with the original integer.*/
bool checkExactlyOneBitSet(int bitVector) {
  return (bitVector & (bitVector - 1)) == 0;
}

bool isPermutationOfPalindrome_3(const string &phrase) {
  int bitVector = createBitVector(phrase);
  return bitVector == 0 || checkExactlyOneBitSet(bitVector);
}

// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(PalindromePermutationTest, Trivial) {
  EXPECT_TRUE(isPermutationOfPalindrome_1("tact coa"));
  EXPECT_TRUE(isPermutationOfPalindrome_2("tact coa"));
  EXPECT_TRUE(isPermutationOfPalindrome_3("tact coa"));
}
