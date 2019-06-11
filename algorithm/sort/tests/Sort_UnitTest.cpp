#include "BubbleSort.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "QuickSort.hpp"
#include "MergeSort.hpp"
#include "PrintUtil.hpp"
#include "HeapSort.hpp"

#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>

/**
 *
 * BubbleSortTest
 * 
 */
TEST(BubbleSortTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(BubbleSort(arr));
}

// For 100 numbers
TEST(BubbleSortTest, Correctness_100) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            BubbleSort(arr);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(1, arr == res);
}

/**
 *
 * InsertionSortTest
 * 
 */

TEST(InsertionSortTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(InsertionSort(arr));
}

// For 100 numbers
TEST(InsertionSortTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            InsertionSort(arr);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

/**
 *
 * SelectionSortTest
 * 
 */
TEST(SelectionSortTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(SelectionSort(arr));
}

// For 100 numbers
TEST(SelectionSortTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            SelectionSort(arr);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

/**
 *
 * MergeSortTest - Recursive
 * 
 */
TEST(MergeSortTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(MergeSort(arr, 0 , arr.size() - 1));
}

// For 100 numbers
TEST(MergeSortTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            MergeSort(arr, 0 , arr.size() - 1);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

/**
 *
 * MergeSortTest Iterative
 * 
 */
TEST(MergeSortIterativeTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(MergeSortIterative(arr, 0 , arr.size() - 1));
}

// For 100 numbers
TEST(MergeSortIterativeTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            MergeSortIterative(arr, 0 , arr.size() - 1);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

/**
 *
 * QuickSortTest - Recursive
 * 
 */
TEST(QuickSortTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(QuickSort(arr, 0 , arr.size() - 1));
}

// For 100 numbers
TEST(QuickSortTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            QuickSort(arr, 0 , arr.size() - 1);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

/**
 *
 * QuickSortIterativeTest
 * 
 */

TEST(QuickSortIterativeTest, NULLTest) {
    std::vector<size_t> arr;
    EXPECT_NO_THROW(QuickSortIterative(arr, 0 , arr.size() - 1));
}

// For 100 numbers
TEST(QuickSortIterativeTest, Correctness) {
    std::vector<size_t> arr {38,98,79,69,14,76,59,
            2,47,3,26,99,12,52,51,22,15,1,39,18,46,
            44,16,50,36,72,9,100,23,37,20,89,92,5,53,
            74,75,56,30,88,49,87,78,94,57,48,85,31,60,
            90,62,27,6,61,43,21,73,7,81,63,58,24,83,86,
            67,25,54,68,97,28,13,95,29,40,91,65,70,66,33,
            55,77,41,8,71,17,64,96,45,34,84,32,19,11,10,42,
            35,4,80,82,93};
            QuickSortIterative(arr, 0 , arr.size() - 1);
            std::vector<size_t> res {1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                    26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                    56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,
                    71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                    86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
                    ASSERT_EQ(0, arr == res);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}