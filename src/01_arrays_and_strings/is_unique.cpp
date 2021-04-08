// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?
//
// Hints: #44, #117, #132

#include <string>

using namespace std;

// ------------------------------------------------------------------------------------------------

bool isUniqueChars_1(const string& str) {
  if (str.length() > 128)
    return false;

  bool char_set[128] = {0};
  for (int i = 0; i < str.length(); ++i) {
    int val = str[i];
    if (char_set[val]) {
      return false;
    }
    char_set[val] = true;
  }
  return true;
}

// ------------------------------------------------------------------------------------------------

bool isUniqueChars_2(const string& str) {
  int checker = 0;
  for (int i = 0; i < str.length(); ++i) {
    int val = str[i] - 'a';
    if ((checker & (1 << val)) > 0) {
      return false;
    }
    checker |= (1 << val);
  }
  return true;
}

// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(IsUniqueTest, Trivial) {

  EXPECT_TRUE(isUniqueChars_1("abcd"));
  EXPECT_FALSE(isUniqueChars_1("abcc"));

  EXPECT_TRUE(isUniqueChars_2("abcd"));
  EXPECT_FALSE(isUniqueChars_2("abcc"));
}
