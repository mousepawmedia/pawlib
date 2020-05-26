/** Pawsort [PawLIB]
 * Version: 0.1
 *
 * A collection of common and original sorting algorithms, some of which
 * rivals std::sort in performance.
 *
 * Author(s): Jason C. McDonald, lulu731
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2019 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef PAWLIB_PAWSORT_HPP
#define PAWLIB_PAWSORT_HPP

#include <cmath>
#include <iterator>

class pawsort
{
public:
    /** An implementation of the selection sort algorithm.
     * Seriously, why would you even want to use this?
     * Consider `insertion_sort` instead.
     *
     * \param the array to sort
     * \param the length of the array
     */

    template<typename T> static void selection_sort(T arr[], int len)
    {
        int start;
        T minVal;

        for (start = 0; start < (len - 1); start++)
        {
            int minI = start;
            minVal = arr[start];
            for (int i = start + 1; i < len; i++)
            {
                if (arr[i] < minVal)
                {
                    minVal = arr[i];
                    minI = i;
                }
            }
            arr[minI] = arr[start];
            arr[start] = minVal;
        }
    }

    /** An implementation of the heap sort algorithm.
     * (See also the `sift_down()` and `heapify()` functions
     * contained in this class.
     *
     * Based on the pseudocode from Rosetta Code.
     * SOURCE: http://rosettacode.org/wiki/Sorting_algorithms/Heapsort#C.2B.2B
     *
     * \param the array to sort
     * \param the leftmost index to sort
     * \param the rightmost index to sort
     */
    template<typename T> static void heap_sort(T arr[], int left, int right)
    {
        /* Ensure the left index is less than the right index. */
        if (right < left)
        {
            int t = left;
            left = right;
            right = t;
        }

        const int LEN = (right - left) + 1;

        // heap_sort algorithm works on zero-based arrays
        if (left != 0)
        {
            T* ZeroBasedArr = &arr[left];
            heap_sort(ZeroBasedArr, 0, LEN - 1);
            return;
        }

        // Heapify...
        for (int i = (LEN - 2) / 2; i >= 0; i--)
        {
            /* sift down the node at index start to the proper
             * place such that all nodes below the start index
             * are in heap order */
            sift_down(arr, i, LEN - 1);
            /* after sifting down the root all nodes/elements
             * are in heap order. */
        }

        int i = LEN - 1;
        while (i > 0)
        {
            swap(arr[i], arr[0]);
            sift_down(arr, 0, --i);
        }
    }

    /** An implementation of the heap sort algorithm.
     * (Wrapper for `heap_sort(T arr[], int left, int right)`
     *
     * \param the array to sort
     * \param the length of the array
     */
    template<typename T> static void heap_sort(T arr[], int len)
    {
        heap_sort(arr, 0, len - 1);
    }

    /** An implementation of the insertion sort algorithm.
     *
     * Based on the C++ implementation at
     * http://www.algolist.net/Algorithms/Sorting/Insertion_sort
     *
     * \param the array to sort
     * \param the leftmost index to sort
     * \param the rightmost index to sort
     */
    template<typename T>
    static void insertion_sort(T arr[], int left, int right)
    {
        /* Ensure the left index is less than the right index. */
        if (right < left)
        {
            swap(left, right);
        }

        // cppcheck-suppress variableScope
        int i, j;
        T newValue;
        /* We go through the whole range (from 'left' to 'right')
         * The left part (below i) is already sorted*/
        for (i = left + 1; i < right + 1; ++i)
        {
            /* arr[i] is the value to be inserted at the good index */
            newValue = arr[i];
            j = i;
            /* Go through the already sorted part of array (left side of range)
             * and swap the values until arr[i] at the good place */
            while (j > left && arr[j - 1] > newValue)
            {
                arr[j] = arr[j - 1];
                --j;
            }
            /* arr[i] (= newValue) at the good index j */
            arr[j] = newValue;
        }
    }

    /** An implementation of the insertion sort algorithm.
     * (Wrapper for `insertion_sort(T arr[], int left, int right)`
     *
     * \param the array to sort
     * \param the length of the array
     */
    template<typename T> static void insertion_sort(T arr[], int len)
    {
        insertion_sort(arr, 0, len - 1);
    }

    /** An implementation of the Knuth shell sort algorithm.
     *
     * Based on the C++ implementation at
     * http://rosettacode.org/wiki/Sorting_algorithms/Shell_sort#C.2B.2B
     *
     * \param the array to sort
     * \param the length of the array
     */
    template<typename T> static void shell_sort(T arr[], int left, int right)
    {
        /* If the right index is smaller than the left, the user has
         * provided an invalid (nonsensical) range. Exit.*/
        if (right < left)
        {
            /* TODO: Revisit this behavior. */
            int t = left;
            left = right;
            right = t;
        }

        T tmp;
        int k = 1, len = (right - left) + 1, gap = (pow(3, k) - 1) / 2,
            cap = ceil(len / 3);

        /* The outer loop uses the Knuth sequence. */
        while (gap < cap)
        {
            for (int i = gap; i < len; ++i)
            {
                tmp = arr[i];
                int j;
                for (j = 1; j >= gap && arr[j - gap] > tmp; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }
                arr[j] = tmp;
            }
            gap = (pow(3, ++k) - 1) / 2;
        }
    }

    /** An implementation of the introspective sort algorithm by
     * David Musser (1997), combined with the dual-pivot quicksort
     * algorithm, originally written by Vladimir Yaroslavskiy. The
     * dual-pivot quicksort implementation is also based on
     * modifications by Arun Manivannan. C++ implementation by
     * Jason C. McDonald.
     *
     * SOURCE: http://www.cs.rpi.edu/~musser/gp/introsort.ps
     * http://permalink.gmane.org/gmane.comp.java.openjdk.core-libs.devel/2628
     * https://dzone.com/articles/algorithm-week-quicksort-three
     *
     * \param the array to sort
     * \param the leftmost index of the range to sort
     * \param the rightmost index of the range to sort
     * \param the maximum depth to allow quicksort to recursively sort
     */
    template<typename T>
    static void introsort(T arr[], int left, int right, int maxdepth = -1)
    {
        introsort(arr + left, arr + right, std::less<>(), maxdepth);
    }

    /** A wrapper for the introsort algorithm, which
     * accepts just the array and length.
     * \param the array to sort
     * \param the size of the array
     */
    template<typename T> static void introsort(T arr[], int len)
    {
        introsort(arr, 0, len - 1);
    }

    /** An implementation of the sorting using introspective sort algorithm
     * Sorts the elements in range [first; last) in ascending order.
     * This implementation is a replacement for std::sort
     * \param the first element
     * \param the last element, excluded in sorting.
     */
    template<class RandomIt> static void sort(RandomIt first, RandomIt last)
    {
        introsort(first, last - 1, std::less<>());
    }

    /** Sorting using introspective sort algorithm.
     * Sorts the elements in range [first; last) in ascending order.
     * \param the first element
     * \param the last element, excluded in sorting.
     *\param comparison function.
     */
    template<class RandomIt, class Compare>
    static void sort(RandomIt first, RandomIt last, Compare comp)
    {
        introsort(first, last - 1, comp);
    }

    /** An implementation of pure dual pivot quick sort algorithm by
     * Vladimir Yaroslavskiy. C++ implementation by lulu731.
     *
     * \param the array to sort
     * \param the leftmost index of the range to sort
     * \param the rightmost index of the range to sort
     */
    template<typename T>
    static void dual_pivot_quick_sort(T arr[], int left, int right)
    {
        dual_pivot_quick_sort(arr + left, arr + right);
    }

private:
    /** pair insertion sort algorithm with iterators.
     *
     * \param the first element to sort
     * \param the last element to sort
     */
    template<class RandomIt, class Compare>
    static void insertion_sort(RandomIt first, RandomIt last, Compare comp)
    {
        /* Ensure the left index is less than the right index. */
        if (last < first)
        {
            auto tmp = first;
            first = last;
            last = tmp;
        }

        const int LEN = last - first + 1;

        int i(0);
        while (i < LEN - 1)
        {
            /*x and y are the two next elements*/
            auto x(*(first + i)), y(*(first + i + 1));
            /*Be sure value in x is greater than that in y*/
            if (comp(x, y))
            {
                swap(x, y);
            }

            /*find insertion point for x
             * j goes from right to left*/
            auto j = i - 1;
            while (j >= 0 && comp(x, *(first + j)))
            {
                /*shift content by 2*/
                *(first + j + 2) = *(first + j);
                j--;
            }
            /*insert x*/
            *(first + j + 2) = x;

            /*keep on with j to find y insertion point*/
            while (j >= 0 && comp(y, *(first + j)))
            {
                *(first + j + 1) = *(first + j);
                j--;
            }
            *(first + j + 1) = y;

            i = i + 2;
        }

        /*if LEN is odd, we need to find insertion point
         * for last element*/
        if (i == LEN - 1)
        {
            auto y = *(first + i);
            auto j = i - 1;

            while (j >= 0 && comp(y, *(first + j)))
            {
                *(first + j + 1) = *(first + j);
                j--;
            }
            *(first + j + 1) = y;
        }
    }

    /** A component of introsort.
     * Returns median of three elements.
     * iterators should be in comp order :
     * a < b < c, with comp = '<'
     *
     * \param first iterator.
     * \param second iterator.
     * \param third iterator.
     * \param comparaison function
     */
    template<class RandomIt, class Compare>
    static RandomIt median_of_three(RandomIt a, RandomIt b, RandomIt c,
                                    Compare comp)
    {
        if ((comp(*b, *a) && comp(*a, *c)) || (comp(*c, *a) && comp(*a, *b)))
        {
            return a;
        }
        if ((comp(*b, *c) && comp(*c, *a)) || (comp(*a, *c) && comp(*c, *b)))
        {
            return c;
        }
        return b;
    }

    /** A component of heap sort. Should only be called from within
     * `heap_sort()`, so use that function to sort an array using
     * the heap sort algorithm.
     *
     * \param the iterator on a container.
     * \param the leftmost index to sort.
     * \param the rightmost index to sort.
     */
    template<class RandomIt, class Compare>
    static void sift_downIt(RandomIt it, int left, int right, Compare comp)
    {
        /* Ensure the left index is less than the right index. */
        if (right < left)
        {
            int t = left;
            left = right;
            right = t;
        }

        int i(left);
        auto root(it + left);
        auto last(it + right);
        RandomIt child;
        // While the root had at least one child...
        while ((it + 2 * i + 1) <= last)
        {
            // it + 2 i +1 points to the left child
            child = it + (2 * i) + 1;
            if ((child + 1) <= last && comp(*child, *(child + 1)))
            {
                child++;
            }
            if (comp(*root, *child))
            {
                // Swap root and child...
                auto tmp = *root;
                *root = *child;
                *child = tmp;
                // Repeat to continue sifting down.
                i = child - it;
                root = child;
            }
            else
            {
                return;
            }
        }
    }

    /** Implementation of heap_sort wth iterators.
     *
     * \param the first element to sort
     * \param the last element to sort
     */
    template<class RandomIt, class Compare>
    static void heap_sort(RandomIt first, RandomIt last, Compare comp)
    {
        /* Ensure the left index is less than the right index. */
        if (last < first)
        {
            auto t = first;
            first = last;
            last = t;
        }

        const int LEN = (last - first) + 1;

        // Heapify...
        for (int i = (LEN - 2) / 2; i >= 0; i--)
        {
            /* sift down the node at index start to the proper
             * place such that all nodes below the start index
             * are in heap order */
            sift_downIt(first, i, LEN - 1, comp);
            /* after sifting down the root all nodes/elements
             * are in heap order. */
        }
        int i = LEN - 1;
        while (i > 0)
        {
            std::iter_swap(first, first + i);
            sift_downIt(first, 0, --i, comp);
        }
    }

    template<class RandomIt>
    static void dual_pivot_quick_sort(RandomIt first, RandomIt last)
    {
        // threshold, if reached end recursive algo with insertion sort
        const int TINY_SIZE = 17;
        const int DIST_SIZE = 13;
        auto len = last - first + 1;

        // If size is less than threshold, use insertion sort.
        if (len < TINY_SIZE)
        {
            insertion_sort(first, last, std::less<>());
            return;
        }

        /*Dual Pivot Quick Sort uses two pivot values.
         * This implementation chooses one pivot at 1/3 and 2/3 of array.
         */
        int third(len / 3);
        RandomIt m1(first + third), m2(last - third);
        if (*m1 < *m2)
        {
            std::iter_swap(m1, first);
            std::iter_swap(m2, last);
        }
        else
        {
            std::iter_swap(m1, last);
            std::iter_swap(m2, first);
        };

        RandomIt pivot1(first);
        RandomIt pivot2(last);
        bool diffPivots(*pivot1 != *pivot2);

        /* BASIC ALGORITHM: By defining two pivots, we are sorting into
         * three partitions, in the following positions:
         * | I | III | IV | II |
         * Partition I: value < pivot1
         * Partition II: value > pivot2
         * Partition III: pivot1 <= value <= pivot2
         * Section IV is the remaining values to be sorted
         *
         * We have two markers which start at the outer boundaries
         * of partitions I and II respectively. By the time the
         * main sorting loop has completed, these markers will be
         * just past the inner boundaries of partitions I and II,
         * and thus mark the boundaries of partition III.
         */

        /* Set the lower marker to one more than the pivot1 index,
         * and the upper marker to one less than the pivot2 index. */

        // pointers
        RandomIt less(first + 1);
        RandomIt great(last - 1);

        // sorting
        if (diffPivots)
        {
            for (RandomIt k = less; k <= great; k++)
            {
                if (*k < *pivot1)
                {
                    std::iter_swap(k, less++);
                }
                else if (*k > *pivot2)
                {
                    while (*great > *pivot2 && k < great)
                    {
                        great--;
                    }
                    std::iter_swap(k, great);
                    great--;
                    if (*k < *pivot1)
                    {
                        std::iter_swap(k, less);
                        less++;
                    }
                }
            }
        }
        else
        {
            for (RandomIt k = less; k <= great; k++)
            {
                if (*k == *pivot1)
                {
                    continue;
                }
                if (*k < *pivot1)
                {
                    std::iter_swap(k, less);
                    less++;
                }
                else
                {
                    while (*great > *pivot2 && k < great)
                    {
                        great--;
                    }
                    std::iter_swap(k, great);
                    great--;
                    if (*k < *pivot1)
                    {
                        std::iter_swap(k, less);
                        less++;
                    }
                }
            }
        }

        // swap
        std::iter_swap(less - 1, first);
        std::iter_swap(great + 1, last);

        // left and right parts
        if (less - 1 != first)
        {
            dual_pivot_quick_sort(first, less - 2);
        }
        if (great + 1 != last)
        {
            dual_pivot_quick_sort(great + 2, last);
        }

        if (great - less > len - DIST_SIZE && diffPivots)
        {
            for (RandomIt k = less; k <= great; k++)
            {
                if (*k == *pivot1)
                {
                    std::iter_swap(k, less++);
                }
                else if (*k == *pivot2)
                {
                    std::iter_swap(k, great--);
                    if (*k == *pivot1)
                    {
                        std::iter_swap(k, less++);
                    }
                }
            }
        }

        // center part
        if (diffPivots)
        {
            dual_pivot_quick_sort(less, great);
        }
    }

    /** Loop for introsort function.
     * Range is from "first" to "last",included.
     * \param first element to be sorted
     * \param last element to be sorted
     */
    template<class RandomIt, class Compare>
    static void introsort_loop(RandomIt first, RandomIt last, Compare comp,
                               int maxdepth = -1)
    {
        // threshold, if reached end recursive algo with insertion sort
        const int TINY_SIZE = 100;

        const int LEN = last - first + 1;

        // If size is less than threshold, use insertion sort.
        if (LEN <= TINY_SIZE)
        {
            insertion_sort(first, last, comp);
            return;
        }

        // if number of levels reached, end with heap_sort
        if (maxdepth == 0)
        {
            heap_sort(first, last, comp);
            return;
        }

        /* Introsort typically uses median-of-three to find its
         * pivot values. However, because we need TWO pivot values,
         * we need a variant :
         *    - divide the array into 2 arrays ([left-middle] and
         * [middle-right]);
         *    - apply median-of-3 on two sub-arrays
         *          (left-middle sub arr-middle and middle-middle sub arr-right)
         *
         * Given three values a, b, c from each subarray, where a < b < c...
         * pivot_subarray = b
         */
        RandomIt middle(first + LEN / 4);
        RandomIt mot = median_of_three(first, middle, (first + LEN / 2), comp);
        if (first != mot)
        {
            std::iter_swap(first, mot);
        }

        middle = last - LEN / 4;
        mot = median_of_three((first + LEN / 2), middle, last, comp);
        if (last != mot)
        {
            std::iter_swap(mot, last);
        }

        /* Swap values at left and right indices to ensure pivots are selected
         * properly*/
        if (comp(*last, *first))
        {
            std::iter_swap(first, last);
        }

        RandomIt pivot1(first);
        RandomIt pivot2(last);

        /* BASIC ALGORITHM: By defining two pivots, we are sorting into
         * three partitions, in the following positions:
         * | I | III | IV | II |
         * Partition I: value < pivot1
         * Partition II: value > pivot2
         * Partition III: pivot1 <= value <= pivot2
         * Section IV is the remaining values to be sorted
         *
         * We have two markers which start at the outer boundaries
         * of partitions I and II respectively. By the time the
         * main sorting loop has completed, these markers will be
         * just past the inner boundaries of partitions I and II,
         * and thus mark the boundaries of partition III.
         */

        /* Set the lower marker to one more than the pivot1 index,
         * and the upper marker to one less than the pivot2 index. */
        RandomIt lower(first + 1), upper(last - 1);

        /* Check if values at beginning of array are at the good place
         * before looping.*/
        while (comp(*lower, *pivot1) && lower < upper)
        {
            lower++;
        }

        /* Loop through the array from the lower to upper markers.
         * Note that these markers move as we sort to prevent swapping
         * values out of correct positions, therefore the range that
         * we are sorting on will shrink as we go. */

        for (RandomIt i = lower; i <= upper; ++i)
        {
            // i iterator is in section IV
            /* If the current value is less than the first pivot... */
            if (comp(*i, *pivot1))
            {
                std::iter_swap(i, lower);
                lower++;
            }
            /* Else if the current value is greater than the
             * second pivot... */
            else if (comp(*pivot2, *i))
            {
                /* Before we continue, let's make sure we're not sitting on
                 * any values that belong in partition II. */
                while (i < upper && comp(*pivot2, *upper))
                {
                    upper--;
                }

                /* Swap the value into partition II and decrement the
                 * upper marker. */
                std::iter_swap(i, upper);
                upper--;
                /* new arr[i] should be checked before moving i.
                 * We know it is not > pivot2, but is it < pivot1 ?
                 */
                if (comp(*i, *pivot1))
                {
                    std::iter_swap(i, lower);
                    lower++;
                }
                /* if not < pivot 1, then leave it where it is, in section III*/
            }
        }

        /* Swap the leftmost position (same as pivot1) with the value
         * at the inner boundary of partition I. */
        std::iter_swap(first, lower - 1);

        /* Swap the rightmost position (same as pivot2) with the value
         * at the inner boundary of partition II. */
        std::iter_swap(upper + 1, last);

        // We have now sorted all values into the three partitions!

        /* Recursively sort partition I, passing in one less than
         * the maxdepth. */
        introsort_loop(first, lower - 1, comp, maxdepth - 1);
        /* Recursively sort partition II, passing in one less than
         * the maxdepth. */
        introsort_loop(upper + 1, last, comp, maxdepth - 1);
        /* Recursively sort partition III, passing in one less than
         * the maxdepth. */
        introsort_loop(lower, upper, comp, maxdepth - 1);

        /* NOTE: In case of infinite recursion on the previous three lines,
         * make sure that this function (the one being recursively called)
         * uses insertion sort if the array is small (LEN < threshold), and that
         * maxdepth is behaving appropriately. */

        /* With the three partitions sorted, the entire array is also
         * now sorted correctly. */
    }

    /** Sorts the elements in ascending order.
     * Range is from "first" to "last",included.
     * \param first element to be sorted
     * \param last element to be sorted
     */
    template<class RandomIt, class Compare>
    static void introsort(RandomIt first, RandomIt last, Compare comp,
                          int maxdepth = -1)
    {
        /* If the right index is smaller than the left,
        no matter, swap the indexes.*/
        if (last < first)
        {
            RandomIt tmp = first;
            first = last;
            last = tmp;
        }

        /* If this is the first run (maxdepth == -1), run through
         * once and ensure we don't have an already sorted array. */
        if (maxdepth == -1)
        {
            /* If we have no specified maximum depth, calculate it. */
            maxdepth = (log2(last - first + 1)) * 2;
            /* NOTE: maxdepth value is empirical (see
             * http://www.cs.rpi.edu/~musser/gp/introsort.ps*/
        }
        introsort_loop(first, last, comp, maxdepth);
    }

    /** Swaps two params.
     *
     * \param First element.
     * \param Second element.
     */
    template<typename T> inline static void swap(T& a, T& b)
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }

    /** A component of heap sort. Should only be called from within
     * `heap_sort()`, so use that function to sort an array using
     * the heap sort algorithm.
     *
     * \param the array to sort.
     * \param the leftmost index to sort.
     * \param the rightmost index to sort.
     */
    template<typename T> static void sift_down(T arr[], int left, int right)
    {
        /* Ensure the left index is less than the right index. */
        if (right < left)
        {
            int t = left;
            left = right;
            right = t;
        }

        T tmp;
        int root = left;

        // While the root had at least one child...
        while (root * 2 + 1 <= right)
        {
            // root*2+1 points to the left child
            int child = root * 2 + 1;
            if (child + 1 <= right && arr[child] < arr[child + 1])
            {
                ++child;
            }
            if (arr[root] < arr[child])
            {
                // Swap root and child...
                tmp = arr[root];
                arr[root] = arr[child];
                arr[child] = tmp;
                // Repeat to continue sifting down.
                root = child;
            }
            else
            {
                return;
            }
        }
    }
};

#endif // PAWLIB_PAWSORT_HPP
