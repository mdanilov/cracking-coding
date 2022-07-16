// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.
//
// Hints: #1, #84, #722, #737

#include <algorithm>
#include <string>

using namespace std;

// ------------------------------------------------------------------------------------------------

string sort(const string &s) {
  string sort_s(s);
  sort(sort_s.begin(), sort_s.end());
  return sort_s;
}

bool permutation_1(const string &s, const string &t) {
  if (s.length() != t.length()) {
    return false;
  }
  return sort(s) == sort(t);
}

// ------------------------------------------------------------------------------------------------

bool permutation_2(const string &s, const string &t) {
  if (s.length() != t.length()) {
    return false;
  }

  int letters[128] = {0};
  for (const char &c : s) {
    letters[c]++;
  }

  for (int i = 0; i < t.length(); ++i) {
    char c = t[i];
    letters[c]--;
    if (letters[c] < 0) {
      return false;
    }
  }

  return true;
}

// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(CheckPermutationTest, Trivial) {
  EXPECT_TRUE(permutation_1("abcd", "dcba"));
  EXPECT_FALSE(permutation_1("abcd", "daba"));

  EXPECT_TRUE(permutation_2("abcd", "dcba"));
  EXPECT_FALSE(permutation_2("abcd", "daba"));
}
