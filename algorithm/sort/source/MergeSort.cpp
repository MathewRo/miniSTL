/*
 *
 * MIT License
 *
 * Copyright (c) 2021 Rohit Philip Mathew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "MergeSort.hpp"
#include <algorithm>


/**
 * This a private helper function which does the merge and sort
 * TC - O(N1) + O(N2) + O(N1 + N2) ~= O(n) 
 * WC complexity is O(n) when high - low = n
 * @param arr
 * @param low
 * @param high
 */
static void Merge(std::vector <size_t> & arr, const int64_t &low, const int64_t &mid, const int64_t &high) {
    int64_t N1 = mid + 1 - low;
    int64_t N2 = high - mid;
    // We need to copy the data to temp left and right arrays before merging.
    // Merge is not an in place algorithm
    int64_t L[N1], R[N2];
    // O(N1)
    for (int64_t i = 0; i < N1; i++) {
        L[i] = arr[i + low]; 
    }
    
    // O(N2)
    for (int64_t i = 0; i < N2; i++) {
        R[i] = arr[i + mid + 1];
    }
    int64_t i = 0;
    int64_t j = 0;
    // This should start from low
    int64_t k = low;
    // Merge O(N1 + N2)
    while ( i < N1 && j < N2) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < N1) {
        arr[k] = L[i];
        k++;
        i++;
    }
    
    while (j < N2) {
        arr[k] = R[j];
        k++;
        j++; 
    }
}

/**
 * Recursevely breaks the given array until it can no longer be divided
 * Recurrence Reln T(n) = 2T(n/2) + Theta(n)
 * Total Complexity = Theta(nLogn)
 * @param arr
 * @param low
 * @param high
 */
void MergeSort(std::vector <size_t> & arr, const int64_t & low, const int64_t & high) {
    if (high > low) {
        int64_t mid = (low + high)/2;
        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        // this is called approx log(n) times
        Merge(arr, low, mid, high);
    }
}

/**
 * Iterative approach to merge sort
 * @param arr
 * @param low
 * @param high
 */
void MergeSortIterative(std::vector <size_t> & arr, const int64_t & low, const int64_t & high) {
    
    for (int64_t i = 1; i <= (high - low); i *= 2) {
        for (int64_t left_end = 0; left_end < (high - low); left_end += 2*i) {
            int64_t mid = std::min(left_end + i - 1, high - low);
            int64_t right_end = std::min (left_end + 2*i - 1, high - low);
            // this is called approx log(n) times
            Merge(arr, left_end, mid, right_end);
        }
    }
}
