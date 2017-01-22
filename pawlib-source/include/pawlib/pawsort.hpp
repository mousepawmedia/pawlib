/** Pawsort [PawLIB]
  * Version: 1.0
  *
  * A collection of common and original sorting algorithms, some of which
  * rivals std::sort in performance.
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
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
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */


#ifndef PAWSORT_HPP_INCLUDED
#define PAWSORT_HPP_INCLUDED

#include <cmath>

namespace pawlib
{
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

            template <typename T>
            static void selection_sort(T arr[], int len)
            {
                int start;
                T minVal;

                for(start = 0; start < (len - 1); start++)
                {
                    int minI = start;
                    minVal = arr[start];
                    for(int i = start + 1; i < len; i++)
                    {
                        if(arr[i] < minVal)
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
            template <typename T>
            static void heap_sort(T arr[], int left, int right)
            {
                /* Ensure the left index is less than the right index. */
                if(right < left)
                {
                    int t = left;
                    left = right;
                    right = t;
                }

                int len = (right-left) + 1;
                T tmp;

                // Heapify...
                for(int i = (len - 2) / 2; i >= 0; i--)
                {
                    /* sift down the node at index start to the proper
                     * place such that all nodes below the start index
                     * are in heap order */
                    sift_down(arr, i, len-1);
                    /* after sifting down the root all nodes/elements
                     * are in heap order. */
                }

                //for(int i = len-1; i > 0; i)
                int i = len-1;
                while(i > 0)
                {
                    tmp = arr[i];
                    arr[i] = arr[0];
                    arr[0] = tmp;
                    sift_down(arr, 0, --i);
                }

            }

            /** An implementation of the heap sort algorithm.
              * (Wrapper for `pawlib::heap_sort(T arr[], int left, int right)`
              *
              * \param the array to sort
              * \param the length of the array
              */
            template <typename T>
            static void heap_sort(T arr[], int len)
            {
                heap_sort(arr, 0, len-1);
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
            template <typename T>
            static void insertion_sort(T arr[], int left, int right)
            {
                /* Ensure the left index is less than the right index. */
                if(right < left)
                {
                    int t = left;
                    left = right;
                    right = t;
                }

                T tmp;
                for(int i = left+1, j=i; i < right; ++i)
                {
                    j = i;
                    while(j > 0 && arr[j - 1] > arr[j])
                    {
                        tmp = arr[j];
                        arr[j] = arr[j - 1];
                        arr[j - 1] = tmp;
                        --j;
                    }
                }
            }

            /** An implementation of the insertion sort algorithm.
              * (Wrapper for `pawlib::insertion_sort(T arr[], int left, int right)`
              *
              * \param the array to sort
              * \param the length of the array
              */
            template <typename T>
            static void insertion_sort(T arr[], int len)
            {
                insertion_sort(arr, 0, len-1);
            }

            /** An implementation of the Knuth shell sort algorithm.
              *
              * Based on the C++ implementation at
              * http://rosettacode.org/wiki/Sorting_algorithms/Shell_sort#C.2B.2B
              *
              * \param the array to sort
              * \param the length of the array
              */
            template <typename T>
            static void shell_sort(T arr[], int left, int right)
            {
                /* Ensure the left index is less than the right index. */
                if(right < left)
                {
                    int t = left;
                    left = right;
                    right = t;
                }

                T tmp;
                int k = 1,
                    len = (right-left) + 1,
                    gap = (pow(3,k) - 1) / 2,
                    cap = ceil(len/3);

                /* The outer loop uses the Knuth sequence. */
                while(gap < cap)
                {
                    for(int i=gap; i<len; ++i)
                    {
                        tmp = arr[i];
                        int j;
                        for(j=1; j >= gap && arr[j-gap] > tmp; j -= gap)
                        {
                            arr[j]=arr[j-gap];
                        }
                        arr[j]=tmp;
                    }
                    gap = (pow(3, ++k) -1) / 2;
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
              * You can acquire a copy of the original and reformatted
              * whitepapers from MousePaw Games' website.
              * - Introspective Sorting and Selection Algorithms, Musser
              * - Dual-Pivot Quicksort, Yaroslavskiy (rev 22 Sep 2009)
              * - Dual-Pivot Quicksort, Yaroslavisky (rev by Jason C. McDonald)
              * TODO: Put link here.
              *
              * \param the array to sort
              * \param the leftmost index of the range to sort
              * \param the rightmost index of the range to sort
              * \param the maximum depth to allow quicksort to recursively sort
              */
            template <typename T>
            static void introsort(T arr[], int left, int right, int maxdepth=-1)
            {
                /* Ensure the left index is less than the right index. */
                if(right < left)
                {
                    int t = left;
                    left = right;
                    right = t;
                }

                const int TINY_SIZE = 17;
                int len = (right-left+1);

                /* If this is the first run (maxdepth == -1), run through
                 * once and ensure we don't have an already sorted array. */
                if(maxdepth == -1)
                {
                    for(int i=left+1; i<=right; ++i)
                    {
                        /* If the current value is greater than the
                         * previous value...
                         */
                        if(arr[i] > arr[i-1])
                        {
                            //The array is NOT sorted. Break loop.
                            break;
                        }

                        //If we get to the end without breaking...
                        if(i == right)
                        {
                            // ...then the array is already sorted! End function.
                            return;
                        }
                    }

                    /* If we have no specified maximum depth, calculate it. */
                    // cppcheck-suppress unpreciseMathCall
                    maxdepth = (log(right-left+1)) * 2;
                    /* NOTE: Multiplying by 2 is arbitrary. We may be able
                     * to improve performance by adjusting that number. */
                }

                // Define a variable for temporary storage during swaps.
                T tmp;

                //If size is less than threshold, use insertion sort.
                if(len <= TINY_SIZE)
                {
                    shell_sort(arr, left, right);
                    return;
                    //insertion_sort(arr, left, right);
                }
                /* Otherwise, if we are supposed to stop recursively
                 * quicksorting partitions, stop and use heapsort. */
                else if(maxdepth == 0)
                {
                    //TODO: This is where performance is getting tanked...?
                    heap_sort(arr, left, right);
                    return;
                }

                /* This will be our loop iterator, but we're also using it
                 * for ensuring pivot1 and pivot2 are different. Thus, we'll
                 * first assign the rightmost index to it.*/
                int i = right;

                /* Introsort typically uses median-of-three to find its
                 * pivot value. However, because we need TWO pivot values,
                 * we need a variant on median-of-three that has a good
                 * probability of approximating the 1/3 median and 2/3 median
                 * values.
                 *
                 * Given three values, selected from the first, middle, and
                 * last positions (same as with the median-of-three),
                 * where a < b < c...
                 * pivot1 = ⌊(b-a)/2)⌋ + a
                 * pivot2 = ⌊(c-b)/2)⌋ + b
                 *
                 * Even in the worst case scenario, this algorithm will never
                 * select the lowest or highest values. It is considerably less
                 * vulnerable to median-of-three killers as a result - in a
                 * so-called "pathological" median-of-three-killer test,
                 * the first, middle, and last values were overridden to be
                 * equal and low, and yet this algorithm still beat std::sort.
                 *
                 * Important distinction: These need to be the VALUES at the
                 * first, middle, and last indices! In an earlier version, the
                 * indices themselves were mistakeningly being used, and the
                 * pivot values were therefore always grabbing the values at
                 * the 1/3 and 2/3 indices - a strategy which fails under a
                 * number of common scenarios.
                 */
                T a=arr[left],
                    b=arr[len/2],
                    c=arr[right],
                    tmp_i;

                /* Put three values in correct order. */
                if(a > b)
                {
                    // Swap
                    tmp_i = a;
                    a = b;
                    b = tmp_i;
                }
                if(a > c)
                {
                    // Swap
                    tmp_i = a;
                    a = c;
                    c = tmp_i;
                }
                if(b > c)
                {
                    // Swap
                    tmp_i = b;
                    b = c;
                    c = tmp_i;
                }

                /* Calculate the first pivot value as the median between
                 * the first and second sampled values. */
                T pivot1 = ((b - a) / 2) + a;
                /* Calculate the second pivot value as the median between
                 * the second and third samples valued. */
                T pivot2 = ((c - b) / 2) + b;

                /* Because we ordered a, b, and c, we can assume that the
                 * pivot values are already in proper order. */

                /* BASIC ALGORITHM: By defining two pivots, we are sorting into
                 * three partitions, in the following positions:
                 * | I | III | II |
                 * Partition I: value < pivot1
                 * Partition II: value > pivot2
                 * Partition III: pivot1 <= value <= pivot2
                 *
                 * We have two markers which start at the outer boundaries
                 * of partitions I and II respectively. By the time the
                 * main sorting loop has completed, these markers will be
                 * just past the inner boundaries of partitions I and II,
                 * and thus mark the boundaries of partition III.
                 */

                /* Set the lower marker to one more than the leftmost index,
                 * and the upper marker to one less than the rightmost index. */
                int lower = (left + 1),
                    upper = (right - 1);

                /* Loop through the array from the lower to upper markers.
                 * Note that these markers move as we sort to prevent swapping
                 * values out of correct positions, therefore the range that
                 * we are sorting on will shrink as we go. */
                for(i = lower; i <= upper; ++i)
                {
                    /* If the current value is less than the first pivot... */
                    if(arr[i] < pivot1)
                    {
                        /* Swap the value into partition I and increment the
                         * lower marker. */
                        tmp = arr[i];
                        arr[i] = arr[lower];
                        arr[lower++] = tmp;
                    }
                    /* Else if the current value is greater than the
                     * second pivot... */
                    else if(arr[i] > pivot2)
                    {
                        /* Before we continue, let's make sure we're not sitting on
                         * any values that belong in partition II. */
                        while(arr[upper] > pivot2)
                        {
                            upper--;
                        }

                        /* Swap the value into partition II and decrement the
                         * upper marker. */
                        tmp = arr[i];
                        arr[i] = arr[upper];
                        arr[upper--] = tmp;
                    }
                    /* If the value is equal to or between the two pivots,
                     * just leave it where it is. If it is currently in the wrong
                     * partition, it will be pushed out of it naturally. */
                }

                /* Swap the leftmost position (same as pivot1) with the value
                 * at the inner boundary of partition I. */
                tmp = arr[left];
                arr[left] = arr[lower-1];
                arr[lower-1] = tmp;

                /* Swap the rightmost position (same as pivot2) with the value
                 * at the inner boundary of partition II. */
                tmp = arr[right];
                arr[right] = arr[upper+1];
                arr[upper+1] = tmp;

                // We have now sorted all values into the three partitions!

                /* Recursively sort partition I, passing in one less than
                 * the maxdepth. */
                introsort(arr, left, lower-1, maxdepth-1);
                /* Recursively sort partition II, passing in one less than
                 * the maxdepth. */
                introsort(arr, right, upper+1, maxdepth-1);
                /* Recursively sort partition III, passing in one less than
                 * the maxdepth. */
                introsort(arr, lower, upper, maxdepth-1);

                /* NOTE: In case of infinite recursion on the previous three lines,
                 * make sure that this function (the one being recursively called)
                 * uses insertion sort if the array is small, and that maxdepth
                 * is behaving appropriately. */

                /* With the three partitions sorted, the entire array is also
                 * now sorted correctly. */
            }

            /** A wrapper for the introsort algorithm, which
              * accepts just the array and length.
              * \param the array to sort
              * \param the size of the array
              */
            template <typename T>
            static void introsort(T arr[], int len)
            {
                introsort(arr, 0, len-1);
            }

        private:
            template <typename T>
            /** A component of heap sort. Should only be called from within
              * `heap_sort()`, so use that function to sort an array using
              * the heap sort algorithm.
              *
              * \param the array to sort.
              * \param the leftmost index to sort.
              * \param the rightmost index to sort.
              */
            static void sift_down(T arr[], int left, int right)
            {
                /* Ensure the left index is less than the right index. */
                if(right < left)
                {
                    int t = left;
                    left = right;
                    right = t;
                }

                T tmp;
                int root = left;

                // While the root had at least one child...
                while(root * 2 + 1 <= right)
                {
                    //root*2+1 points to the left child
                    int child = root * 2 + 1;
                    if(child + 1 <= right && arr[child] < arr[child+1])
                    {
                        ++child;
                    }
                    if(arr[root] < arr[child])
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
}

#endif // PAWSORT_HPP_INCLUDED
