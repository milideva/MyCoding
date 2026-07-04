/**
 * Problem: Implement rand7() using rand5()
 * Given a function rand5() that returns a random integer in the range [1, 5] 
 * with uniform probability, implement rand7() that returns a random integer 
 * in the range [1, 7] with uniform probability.
 * 
 * Strategy: Rejection Sampling
 * 1. Generate a range larger than [1, 7] using rand5(). 
 *    5 * (rand5() - 1) + rand5() gives a uniform range [1, 25].
 * 2. If the generated number is <= 21, return (num % 7) + 1.
 * 3. If the generated number is > 21, reject it and try again.
 * This ensures that every outcome in [1, 7] has a 3/25 probability.
 * 
 * Time Complexity: O(1) amortized. 
 * Space Complexity: O(1).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Mock rand5() implementation.
 */
int rand5() {
    return (rand() % 5) + 1;
}

/**
 * Implementation of rand7() using rand5().
 */
int rand7() {
    while (1) {
        // Generate uniform random number in range [1, 25]
        int num = 5 * (rand5() - 1) + rand5();
        
        // Use numbers in [1, 21] as they are divisible by 7
        if (num <= 21) {
            return (num - 1) % 7 + 1;
        }
        // Reject numbers 22, 23, 24, 25 and try again
    }
}

int main() {
    srand(time(NULL));
    int counts[8] = {0};
    int iterations = 70000;

    printf("Generating %d random numbers using rand7()...\n", iterations);
    for (int i = 0; i < iterations; i++) {
        counts[rand7()]++;
    }

    printf("Distribution:\n");
    for (int i = 1; i <= 7; i++) {
        printf("%d: %d (%.2f%%)\n", i, counts[i], (double)counts[i] * 100 / iterations);
    }

    return 0;
}
