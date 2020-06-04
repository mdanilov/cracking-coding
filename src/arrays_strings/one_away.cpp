// One Away: There are three types of edits that can be performed on strings:
// insert a character, remove a character, or replace a character. Given two
// strings, write a function to check if they are one edit (or zero edits) away.
//
// EXAMPLE
// pale, ple -> true
// pales, pale -> true
// pale, bale -> true
// pale, bake -> false
//
// Hints: #23, #97, #130

#include <cmath>
#include <string>

using namespace std;

// Solution #1
// ------------------------------------------------------------------------------------------------

/* Check if you can insert a character into s1 to make s2. */
bool oneEditInsert(const string &s1, const string &s2) {
  int index1 = 0;
  int index2 = 0;
  while (index2 < s2.length() && index1 < s1.length()) {
    if (s1[index1] != s2[index2]) {
      if (index1 != index2) {
        return false;
      }
      index2++;
    } else {
      index1++;
      index2++;
    }
  }
  return true;
}

bool oneEditReplace(const string &s1, const string &s2) {
  bool foundDifference = false;
  for (int i = 0; i < s1.length(); ++i) {
    if (s1[i] != s2[i]) {
      if (foundDifference) {
        return false;
      }
      foundDifference = true;
    }
  }
  return true;
}

bool oneEditAway_1(const string &first, const string &second) {
  if (first.length() == second.length()) {
    return oneEditReplace(first, second);
  } else if (first.length() + 1 == second.length()) {
    return oneEditInsert(first, second);
  } else if (first.length() - 1 == second.length()) {
    return oneEditInsert(second, first);
  }
  return false;
}

// Solution #2
// ------------------------------------------------------------------------------------------------

bool oneEditAway_2(const string &first, const string &second) {
  /* Length checks. */
  if (abs(static_cast<int>(first.length() - second.length())) > 1) {
    return false;
  }

  /* Get shorter and longer string.*/
  const string &s1 = first.length() < second.length() ? first : second;
  const string &s2 = first.length() < second.length() ? second : first;
  int index1 = 0;
  int index2 = 0;
  bool foundDifference = false;
  while (index2 < s2.length() && index1 < s1.length()) {
    if (s1[index1] != s2[index2]) {
      /* Ensure that this is the first difference found.*/
      if (foundDifference)
        return false;
      foundDifference = true;
      if (s1.length() == s2.length()) {
        // On replace, move shorter pointer
        index1++;
      }
    } else {
      index1++; // If matching, move shorter pointer
    }
    index2++; // Always move pointer for longer string
  }
  return true;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(OneAwayTest, Trivial) {

  EXPECT_TRUE(oneEditAway_1("pale", "ple"));
  EXPECT_TRUE(oneEditAway_1("pales", "pale"));
  EXPECT_TRUE(oneEditAway_1("pale", "bale"));
  EXPECT_FALSE(oneEditAway_1("pale", "bake"));

  EXPECT_TRUE(oneEditAway_2("pale", "ple"));
  EXPECT_TRUE(oneEditAway_2("pales", "pale"));
  EXPECT_TRUE(oneEditAway_2("pale", "bale"));
  EXPECT_FALSE(oneEditAway_2("pale", "bake"));
}
