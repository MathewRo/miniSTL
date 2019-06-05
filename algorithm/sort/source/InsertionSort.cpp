#include "InsertionSort.hpp"

/**
 * Function Implementing Insertion Sort
 * @param arr
 * TC O(n^2)
 * 
 * https://www.hackerearth.com/practice/algorithms/sorting/insertion-sort/tutorial/
 */
void InsertionSort(std::vector<uint64_t>& arr) {
    uint64_t N = arr.size();
    for (uint64_t i = 0; i < N; i++) {
        // For each loop we assume i as the max initially
        uint64_t max = arr[i];
        uint64_t j = i;
        // Iterate if j is atleast 1 and as long as arr[j-1] is bigger than temp
        while (j > 0 && arr[j - 1] > max) {
            // This is essentially pushing the elements by one
            arr[j] = arr[j-1];
            j -= 1;
        }
        // Finally save the temp to the index where the loop condition
        // was false
        arr[j] = max;
    }
}