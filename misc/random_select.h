
/*
 *  Vivandro's algorithm prep material.
 *  Copyright (C) 2014 Vivandro. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef APFN_MISC_RANDOM_SELECT_H
#define APFN_MISC_RANDOM_SELECT_H

#include <random>
#include <iostream>

namespace vvalgo {

template <typename T>
void swap(T a, T b) {
	typename T::value_type t = *a;
	*a = *b;
	*b = t;
}

/*
 * begin and end define an unsorted subarray. We return the kth smallest number in this subarray
 * in O(n) expected worst case time with high probability by using a random pivot to recursively
 * partition the subarrays until the pivot turns out to be the kth smallest number.
 */
template <typename T>
T selectKthSmallest(T begin, T end, unsigned long long k) {
	if (k > (end - begin)) { // if we do not have k elements to begin with, return failure.
		return end; 	// The 'end' iterator indicates that we could not find the kth smallest number. 
	}

	// Create a helper lambda that partitions the sub-array in question around a randomly selected pivot.
	typedef unsigned long long ull;
	auto randomPartition = [](T begin, T end) -> T {
		// Number of elements in this sub array.
		ull n = end - begin;
		if (n == 0) {
			return end;
		}
		if (n == 1) {
			return begin;
		}
		
		// Random number generator that provides a uniform random number between - and n-1.
		std::default_random_engine generator;
		std::uniform_int_distribution<ull> distribution(0,n-1);
		
		// Index of the element we are selecting as the random pivot.
		ull pIndex = distribution(generator); // uniform_int_distribution guarantees this number to be between 0 and n-1

		// Swap the pivot element with the 0th element to bring the pivot element on one side of the sub array.
		swap(begin, begin+pIndex);
	
		/*
		 * Loop Invariant: 1. The sub array to the left of i is always correctly partitioned.
		 *                 2. In the partitioned sub array elements to the left of the pivot are less than the pivot,
		 *                    while those on the right are greater than or equal to the pivot.
		 */
		T pivot = begin;
		for (T i = pivot + 1; // i refers to the next element under consideration. pivot refers to the current position of the pivot.
		     i != end; 
		     ++i) 
		{
			if (*i >= *pivot) { 
				continue; // element is already on the correct side of the partition.
			}
			T b = pivot + 1;
			// Otherwise, we need to perform a 3 element rotation as follows:
			// current positions: ..a *pivot *b ..... *i ...
			// final positions:   ..a *i *pivot ..... *b ...
			typename T::value_type t = *pivot;
			*pivot = *i;
			*i = *b;
			*b = t;
		}

		return pivot;
	};

	 /*
	  * Since we are going to use the following lambda recursively we face a few interesting choices and issues.
	  * 1. auto: Cannot use auto to derive its type because, the name of the variable cannot be used in the initializer 
	  *    of the variable unless it's type is known.
	  * 2. One way to specify the type will be as follows
	  *    std::function< T (T, T, ull) > recursiveSelect = [&](T begin, T end, ull k) -> T {
	  *    Notice how we captured everything as reference in the capture list. It would be a good idea to instead capture only
	  *    what is needed.
	  *    std::function< T (T, T, ull) > recursiveSelect = [&recursiveSelect, &randomPartition](T begin, T end, ull k) -> T {
	  * 3. We could even use auto if we want to, but it meants that we cannot use the name of the lambda inside the lambda.
	  *    Technically we can overcome this limitation by accepting a parameter that the caller can use to pass us a reference 
	  *    to ourselves and call it to effectively get recursion. But that leaves out a dependency that is an invitation to buggy code.
	  *    And it also does not rid us of the need to determine the type of the lambda since it needs to be specified for the parameter.
	  */
	 std::function< T (T, T, ull) > recursiveSelect = [&recursiveSelect, &randomPartition](T begin, T end, ull k) -> T {
		T pivot = randomPartition(begin, end);
		ull pRank = pivot - begin;
		if (k == pRank) {
			return pivot;
		}

		if (k > pRank) { // k lies in the right partition
			return recursiveSelect(pivot+1, end, k - (pRank + 1));
		} else { // k lies in the left partition
			return recursiveSelect(begin, pivot, k);;
		}
	};

	return recursiveSelect(begin, end, k);
}

} // NS: vvalgo

#endif // APFN_MISC_RANDOM_SELECT_H
