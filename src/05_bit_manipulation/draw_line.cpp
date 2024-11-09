// Draw Line: A monochrome screen is stored as a single array of bytes, allowing
// eight consecutive pixels to be stored in one byte. The screen has width w,
// where w is divisible by 8 (that is, no byte will be split across rows). The
// height of the screen, of course, can be derived from the length of the array
// and the width. Implement a function that draws a horizontal line from (x1,
// y) to (x2, y).
// The method signature should look something like:
// drawLine(byte[] screen, int width, int x1, int x2, int y)
//
// Hints: #366, #381, #384, #391

#include <cstdint>
#include <vector>

// Solution
// ------------------------------------------------------------------------------------------------
void drawLine(std::vector<uint8_t> &screen, int width, int x1, int x2, int y) {
  int start_offset = x1 % 8;
  int first_full_byte = x1 / 8;
  if (start_offset != 0) {
    first_full_byte++;
  }

  int end_offset = x2 % 8;
  int last_full_byte = x2 / 8;
  if (end_offset != 7) {
    last_full_byte--;
  }

  // Set full bytes
  for (int b = first_full_byte; b <= last_full_byte; b++) {
    screen[(width / 8) * y + b] = 0xFFU;
  }

  // Create masks for start and end of line
  uint8_t start_mask = (0xFFU >> start_offset);
  uint8_t end_mask = ~(0xFFU >> (end_offset + 1));

  // Set start and end of line
  if ((x1 / 8) == (x2 / 8)) { // x1 and x2 are in the same byte
    uint8_t mask = (start_mask & end_mask);
    screen[(width / 8) * y + (x1 / 8)] |= mask;
  } else {
    if (start_offset != 0) {
      int byte_number = (width / 8) * y + first_full_byte - 1;
      screen[byte_number] |= start_mask;
    }
    if (end_offset != 7) {
      int byte_number = (width / 8) * y + last_full_byte + 1;
      screen[byte_number] |= end_mask;
    }
  }
}

// Test
// ------------------------------------------------------------------------------------------------

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(DrawLineTest, Trivial) {
  int width = 48;
  int height = 1;
  std::vector<uint8_t> screen((width / 8) * height, 0);
  drawLine(screen, width, 12, 28, 0);
  ASSERT_THAT(screen,
              ::testing::ElementsAre(0b00000000, 0b00001111, 0b11111111,
                                     0b11111000, 0b00000000, 0b00000000));
}
