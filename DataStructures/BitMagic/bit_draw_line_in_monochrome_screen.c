#include <stdio.h>
#include <stdint.h>

/*
  Problem: Draw Horizontal Line on Monochrome Screen

  Problem Description:
  A monochrome screen is stored as a single array of bytes, 
  allowing eight consecutive pixels to be stored in one byte. 
  The screen has width `w`, where `w` is divisible by 8. 
  Implement a function `drawLine(byte[] screen, int width, int x1, 
  int x2, int y)` which draws a horizontal line from `(x1, y)` 
  to `(x2, y)`.

  Algorithm: Byte-aligned Optimization
  1. Calculate the starting and ending byte indices.
  2. For bytes strictly between the start and end bytes, set them 
     to `0xFF` (all pixels ON).
  3. For the partial start byte:
     - Create a mask that has 1s from `x1 % 8` to the end of the byte.
  4. For the partial end byte:
     - Create a mask that has 1s from the start of the byte to `x2 % 8`.
  5. If `x1` and `x2` are in the same byte, combine the masks.

  Complexity Analysis:
  - Time Complexity: O(width/8)
    Reason: We iterate through the bytes that the line covers.
  - Space Complexity: O(1).
*/

typedef uint8_t byte;

void drawLine(byte screen[], int width, int x1, int x2, int y) {
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

    // 1. Set full bytes
    for (int b = first_full_byte; b <= last_full_byte; b++) {
        screen[(width / 8) * y + b] = 0xFF;
    }

    // 2. Handle partial start and end bytes
    byte start_mask = (byte)(0xFF >> start_offset);
    byte end_mask = (byte)~(0xFF >> (end_offset + 1));

    if ((x1 / 8) == (x2 / 8)) {
        // Line is within a single byte
        byte mask = (byte)(start_mask & end_mask);
        screen[(width / 8) * y + (x1 / 8)] |= mask;
    } else {
        if (start_offset != 0) {
            int byte_number = (width / 8) * y + (x1 / 8);
            screen[byte_number] |= start_mask;
        }
        if (end_offset != 7) {
            int byte_number = (width / 8) * y + (x2 / 8);
            screen[byte_number] |= end_mask;
        }
    }
}

void printScreen(byte screen[], int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 8; x++) {
            byte b = screen[y * (width / 8) + x];
            for (int i = 7; i >= 0; i--) {
                printf("%c", (b & (1 << i)) ? '#' : '.');
            }
        }
        printf("\n");
    }
}

int main() {
    int w = 32;
    int h = 5;
    byte screen[32 * 5 / 8] = {0};

    printf("Drawing line from (5, 2) to (25, 2):\n");
    drawLine(screen, w, 5, 25, 2);
    printScreen(screen, w, h);

    return 0;
}
