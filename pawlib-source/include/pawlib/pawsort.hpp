/** Pawsort [PawLIB]
  * Version: 0.1
  *
  * A collection of common and original sorting algorithms, some of which
  * rivals std::sort in performance.
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016-2019 MousePaw Media.
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

                const int LEN = (right-left) + 1;

                //heap_sort algorithm works on zero-based arrays
                if (left != 0)
                {
                    T* ZeroBasedArr = &arr[left];
                    heap_sort(ZeroBasedArr, 0, LEN-1);
                    return;
                }

                // Heapify...
                for(int i = (LEN - 2) / 2; i >= 0; i--)
                {
                    /* sift down the node at index start to the proper
                     * place such that all nodes below the start index
                     * are in heap order */
                    sift_down(arr, i, LEN-1);
                    /* after sifting down the root all nodes/elements
                     * are in heap order. */
                }

                int i = LEN-1;
                while(i > 0)
                {
                    swap(arr[i], arr[0]);
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
                    swap(left, right);
                }

                int i, j;
                T newValue;
                /* We go through the whole range (from 'left' to 'right')
                  * The left part (below i) is already sorted*/
                for(i = left+1; i < right+1; ++i)
                {
                    /* arr[i] is the value to be inserted at the good index */
                    newValue = arr[i];
                    j = i;
                    /* Go through the already sorted part of array (left side of range)
                      * and swap the values until arr[i] at the good place */
                    while(j > left && arr[j - 1] > newValue)
                    {
                        arr[j] = arr[j - 1];
                        --j;
                    }
                    /* arr[i] (= newValue) at the good index j */
                    arr[j] = newValue;
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
                /* If the right index is smaller than the left, the user has
                 * provided an invalid (non-sensical) range. Exit.*/
                if(right < left)
                {
                    /* TODO: Revisit this behavior. */
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
              * \param the array to sort
              * \param the leftmost index of the range to sort
              * \param the rightmost index of the range to sort
              * \param the maximum depth to allow quicksort to recursively sort
              */
            template <typename T>
            static void introsort(T arr[], int left, int right, int maxdepth=-1)
            {
                /* If the right index is smaller than the left,
                no matter, swap the indexes.*/
                if(right <= left) { swap(arr[left], arr[right]); }

                //threshold, if reached end recursive algo with insertion sort
                const int TINY_SIZE = 17;

                const int LEN = (right-left+1);

                /* If this is the first run (maxdepth == -1), run through
                 * once and ensure we don't have an already sorted array. */
                if(maxdepth == -1)
                {
                    for(int i=left+1; i<=right; ++i)
                    {
                        /* If the current value is greater than the
                         * previous value...
                         */
                        if(arr[i] < arr[i-1])
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
                    maxdepth = (log2(right-left+1)) * 2;
                    /* NOTE: maxdepth value is empirical (see
                     * http://www.cs.rpi.edu/~musser/gp/introsort.ps*/
                }

                //If size is less than threshold, use insertion sort.
                if(LEN <= TINY_SIZE)
                {
                    insertion_sort(arr, left, right);
                    return;
                }

                //if number of levels reached, end with heap_sort
                if(maxdepth == 0)
                {
                    heap_sort(arr, left, right);
                    return;
                }

                 /* Introsort typically uses median-of-three to find its
                 * pivot value. However, because we need TWO pivot values,
                 * we need a variant :
                 *    - divide the array into 2 arrays ([left-middle] and [middle-right]);
                 *    - apply median-of-3 on two sub-arrays
                 *          (left-middle sub arr-middle and middle-middle sub arr-right)
                 *
                 * Given three values a, b, c from each subarray, where a < b < c...
                 * pivot_subarray = b
                 */

                int middle(left + LEN/4);
                sort_three(arr[left], arr[middle], arr[left + LEN/2]);
                swap(arr[left], arr[middle]);

                middle = right - LEN/4;
                sort_three(arr[left + LEN/2], arr[middle], arr[right]);
                swap(arr[right], arr[middle]);

                /* Swap values at left and right indices to ensure pivots are selected properly*/
                if(arr[right] < arr[left]) { swap(arr[right], arr[left]); }

                T pivot1 = arr[left];
                T pivot2 = arr[right];

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
                int lower = (left + 1),
                      upper = (right - 1);

                /* Loop through the array from the lower to upper markers.
                 * Note that these markers move as we sort to prevent swapping
                 * values out of correct positions, therefore the range that
                 * we are sorting on will shrink as we go. */
                int i;
                for(i = lower; i <= upper; ++i)
                {
                    // arr[i] is in section IV
                    /* If the current value is less than the first pivot... */
                    if (arr[i] < pivot1)
                    {
                        swap(arr[i], arr[lower]);
                        lower++;
                    }
                    /* Else if the current value is greater than the
                     * second pivot... */
                    else if(arr[i] > pivot2)
                        {
                        /* Before we continue, let's make sure we're not sitting on
                         * any values that belong in partition II. */
                                while(i < upper && arr[upper] > pivot2)
                                {
                                    upper--;
                                }

                        /* Swap the value into partition II and decrement the
                         * upper marker. */
                         swap(arr[i], arr[upper]);
                         upper--;
                         /* new arr[i] should be checked before movong i.
                          * We know it is not > pivot2, but is it < pivot1
                          */
                         if (arr[i] < pivot1)
                          {
                                swap(arr[i], arr[lower]);
                                lower++;
                          }
                          /* if not < pivot 1, then leave it where it is, in section III*/
                        }
                }

                /* Swap the leftmost position (same as pivot1) with the value
                 * at the inner boundary of partition I. */
                swap(arr[left], arr[lower-1]);

                /* Swap the rightmost position (same as pivot2) with the value
                 * at the inner boundary of partition II. */
                swap(arr[upper+1], arr[right]);

                // We have now sorted all values into the three partitions!

                /* Recursively sort partition I, passing in one less than
                 * the maxdepth. */
                introsort(arr, left, lower-1, maxdepth-1);
                /* Recursively sort partition II, passing in one less than
                 * the maxdepth. */
                introsort(arr, upper+1, right, maxdepth-1);
                /* Recursively sort partition III, passing in one less than
                 * the maxdepth. */
                introsort(arr, lower, upper, maxdepth-1);

                /* NOTE: In case of infinite recursion on the previous three lines,
                 * make sure that this function (the one being recursively called)
                 * uses insertion sort if the array is small (LEN < threshold), and that maxdepth
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

            /** A component of introsort.
              * Sorts three params.
              *
              * \param element to be sorted.
              * \param element to be sorted.
              * \param element to be sorted.
              */
            static void sort_three(T& a, T& b, T& c)
            {
                //T tmp_i;
                /* Put three values in correct order. */
                if(a > b)
                {
                    swap(a, b);
                }
                if(a > c)
                {
                    swap(a, c);
                }
                if(b > c)
                {
                    swap(b,c);
                }
            }

            /** Swaps two params.
              *
              * \param First element.
              * \param Second element.
              */
            template <typename T>
            static void swap(T& a, T& b){
                T tmp = a;
                a = b;
                b = tmp;
            }

            /** A component of heap sort. Should only be called from within
              * `heap_sort()`, so use that function to sort an array using
              * the heap sort algorithm.
              *
              * \param the array to sort.
              * \param the leftmost index to sort.
              * \param the rightmost index to sort.
              */
            template <typename T>
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

#endif // PAWLIB_PAWSORT_HPP
