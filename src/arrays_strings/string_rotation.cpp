// String Rotation: Assume you have a method isSubstring which checks if one
// word is a substring of another. Given two strings, s1 and s2, write code to
// check if s2 is a rotation of s1 using only one call to isSubstring (e.g.,
// "waterbottle" is a rotation of "erbottlewat").
//
// Hints: #34, #88, #104

#include <string>

using namespace std;

bool isSubstring(const string &s1, const string &s2) {
  return s1.find(s2) != string::npos;
}

// Solution #1
// ------------------------------------------------------------------------------------------------

bool isRotation(const string &s1, const string &s2) {
  int len = s1.length();
  /* Check that s1 and s2 are equal length and not empty */
  if (len == s2.length() && len > 0) {
    /* Concatenate s1 and s1 within new buffer */
    string s1s1 = s1 + s1;
    return isSubstring(s1s1, s2);
  }
  return false;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(StringRotation, Trivial) {
  EXPECT_TRUE(isRotation("waterbottle", "erbottlewat"));
}
