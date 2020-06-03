// URLify: Write a method to replace all spaces in a string with %20: You may
// assume that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string. (Note: If
// implementing in Java, please use a character array so that you can perform
// this operation in place.)
//
// EXAMPLE
// Input: "Mr John Smith    ", 13
// Output: "Mr%20John%20Smith"
//
// Hints: #53, #118

#include <string>

using namespace std;

// ------------------------------------------------------------------------------------------------

void replaceSpaces(string &str, int trueLength) {
  size_t index = str.length() - 1;
  for (int i = trueLength - 1; i >= 0; --i) {
    if (str[i] == ' ') {
      str[index] = '0';
      str[index - 1] = '2';
      str[index - 2] = '%';
      index -= 3;
    } else {
      str[index] = str[i];
      --index;
    }
  }
}

// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(URLifyTest, Trivial) {
  string str("Mr John Smith    ");
  replaceSpaces(str, 13);
  EXPECT_EQ(str, "Mr%20John%20Smith");
}
