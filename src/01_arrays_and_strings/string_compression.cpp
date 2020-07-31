// String Compression: Implement a method to perform basic string compression
// using the counts of repeated characters. For example, the string aabcccccaaa
// would become a2b1c5a3. If the "compressed" string would not become smaller
// than the original string, your method should return the original string. You
// can assume the string has only uppercase and lowercase letters (a - z).
//
// Hints: #92, #110

#include <string>

using namespace std;

// Solution #1
// ------------------------------------------------------------------------------------------------

string compress_1(const string &str) {
  string compressedString;
  unsigned countConsecutive = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    countConsecutive++;

    /* If next character is different than current,
        append this char to result.*/
    if (i + 1 >= str.length() || str[i] != str[i + 1]) {
      compressedString += str[i] + to_string(countConsecutive);
      countConsecutive = 0;
    }
  }
  return compressedString.length() < str.length() ? compressedString : str;
}

// Solution #2
// ------------------------------------------------------------------------------------------------

int countCompression(const string &str) {
  int compressedLength = 0;
  int countConsecutive = 0;
  for (int i = 0; i < str.length(); i++) {
    countConsecutive++;

    /* If next character is different than current, increase the length. */
    if (i + 1 >= str.length() || str[i] != str[i + 1]) {
      compressedLength += 1 + to_string(countConsecutive).length();
      countConsecutive = 0;
    }
  }
  return compressedLength;
}

string compress_2(const string &str) {
  /* Check final length and return input string if it would be longer. */
  int finalLength = countCompression(str);
  if (finalLength > str.length())
    return str;

  string compressed;
  compressed.reserve(finalLength); // initial capacity
  int countConsecutive = 0;
  for (int i = 0; i < str.length(); i++) {
    countConsecutive++;

    /* If next character is different than current, append this char to result. */
    if (i + 1 >= str.length() || str[i] != str[i + 1]) {
      compressed.push_back(str[i]);
      compressed.append(to_string(countConsecutive));
      countConsecutive = 0;
    }
  }
  return compressed;
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gtest/gtest.h"

TEST(StringCompressionTest, Trivial) {

  EXPECT_EQ(compress_1("aabcccccaaa"), "a2b1c5a3");
  EXPECT_EQ(compress_2("aabcccccaaa"), "a2b1c5a3");
}