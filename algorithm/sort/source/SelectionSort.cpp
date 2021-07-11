/*
 *
 * MIT License
 *
 * Copyright (c) 2021 Rohit Philip Mathew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the &quot;Software&quot;), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "SelectionSort.hpp"
#include <algorithm>

/**
 * Sort an array using the Selection Sort
 * algorithm. Time complexity is 
 * (N-1) + (N-2) + ... 1 = (N-1)(N-2)/2 = O(N^2)
 * @param arr
 * 
 */
void SelectionSort(std::vector<size_t>& arr) {
    int64_t N = arr.size();
    int64_t min;
    for (int64_t i = 0; i < N-1; i++) {
        min = i;
        for (int64_t j = i+1; j < N; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        std::swap(arr[min], arr[i]);
    }
}
