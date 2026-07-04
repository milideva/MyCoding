/**
 * Problem: Random Shuffle an Array (Fisher-Yates Shuffle)
 * Given an array, shuffle its elements such that every permutation 
 * is equally likely.
 * 
 * Strategy: Fisher-Yates Algorithm
 * - Iterate from the last element to the first.
 * - In each step, pick a random index 'j' from 0 to current index 'i'.
 * - Swap elements at index 'i' and 'j'.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

/**
 * Shuffles an array in-place.
 */
void randomShuffle(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

int main() {
    srand(time(NULL));
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    randomShuffle(arr);

    cout << "Shuffled array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
