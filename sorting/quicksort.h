
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

#ifndef APFN_SORTING_QUICKSORT_H
#define APFN_SORTING_QUICKSORT_H

#include <random>

namespace vvalgo {

namespace quicksort {

// Forward references : ***** Begin ******
template <typename T>
T randomPartition(T begin, T end);
// Forward references : ****** End *******

// T should be a randon iterator type.
// T should have a type defined as T::value_type
// *T should implement the less than operator (in other code I have sometimes used  >, but I should avoid 
// doing that in order to impose minimal requirement on *T
template <typename T>
void sort(T begin, T end) {

	if ( (begin == end)		// If the container has : Zero elements
	     || ((begin + 1) == end) ) {// Or, One element.
		return;			// Reutrn right away because the cnotainer is trivially sorted.
	}

	// Partition the "array" (it can be abstractly viewed as an array because it allows random and
	// sequential access iterators).
	T pivot = randomPartition(begin, end); 
	// pivot will never be equal to end because it refers to the pivot element, and we will
	// never have an element at 'end'.

	// Then sort the two partitions recursively.
	sort(begin,     pivot);
	sort(pivot + 1, end);
	
} // FN : sort

// Although I had defined randomPartition as a lambda before (in the algorithm for selecting the Kth smallest number),
// I will extract it out as a method here because it is useful in a more general sense.
template <typename T>
T randomPartition(T begin, T end) {
	if ( (begin == end)		// if the container has zero elements,
	     || ((begin + 1) == end) ) {// or a single element
		return begin;		// We can trivially partition this.
	}

	// ref for random number generator: http://www.stroustrup.com/C++11FAQ.html#std-random
	auto randomIteratorPointingToValidElement = [&begin, &end]() -> T {
		static std::default_random_engine re;
		static std:: uniform_int_distribution<unsigned long long> uid;
		// We are using static variables above so that every next call continues from where we 
		// left off rather than re-init the random number engine.
		unsigned long long low = 0;
		unsigned long long high = end - begin;
		unsigned long long pivotIndex = uid(re, std::uniform_int_distribution<unsigned long long>::param_type{low, high});

		return begin + pivotIndex;
	};

	auto swap = [](T a, T b) {
		//typename T::value_type t = *a;
		// C++11 FTW! In C++98, if I wanted this to work for pointers, I would have had to
		//            create a template overload which used (T *begin, T *end) just because
		//            the pointers (which would be needed when we want to sort arrays) may not
		//            necessarily point to elements of types that defined the type value_type.
		// In C++11 I just needed to replace the explicit type definition with auto that defers
		// the type inference to the template type inference machinery and finds the correct
		// value type for us.
		auto t = *a;
		*a = *b;
		*b = t;
	};

	// a -> b -> c -> a
	// If I read up on variadic templates(I think) I should be able to merge swap and threeItemCircularSwap
	// into a single lambda expression.
	auto threeItemCircularSwap = [](T a, T b, T c) {
		//typename T::value_type t = *a;
		auto t = *a;
		*a = *c;
		*c = *b;
		*b = t;
	};

	// Find a random pivot element
	T pivot = randomIteratorPointingToValidElement();
	swap(begin, pivot);
	
	/*
	 * Loop Invariant: Everything to the left of i is partitioned correctly.
	 *                 At entry, i refers to the next element we want to add into the already
	 *                 partitioned subarray on its left.
	 *                 pivot refers to the current location of the pivot.
	 */
	pivot = begin;
	for (auto i = pivot + 1; i != end; ++i) {
		if (*i > *pivot) { // The element is already on the right side of the partition. Literally.
			continue;
		}
		// *i needs to be moved to the left of the pivot, and the pivot needs to be moved one place to its right.
		threeItemCircularSwap(pivot, pivot + 1, i);
		++pivot;// need to move the pivot reference to the right since we moved it into (pivot + 1)
	}
	return pivot;
}

} // NS : quicksort

} // NS : vvalgo

#endif // APFN_SORTING_QUICKSORT_H

