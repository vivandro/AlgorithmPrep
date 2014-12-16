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

namespace vvalgo {

namespace insertion_sort{
// Caller needs to pass sequential bi-directional iterators
template<class T>
void sort(T begin, T end) {
	if ( (begin == end) // empty "array".
	     || ((begin+1) == end) ) { // single element array.
		return; // These trivial cases are already sorted.
	}

	/*
	 * Loop Invariant: sub-array to the left of i is always sorted. 
	 */
	for (	auto i = begin + 1; 	// i indicates the original position of the element we plan to add into the sorted sub array.
		i != end; 		// We can stop adding new elements when we run out of them.
		++i) 			// Move one position ahead to look for a new element to add into the sorted sub array
		{ // Add the ith element into the sorted sub array on the left of i.
		for (	auto j = i; 	// j will indicate the current position of the element that we originally picked up from the ith position.
			(j != begin) 	// if we have moved it up to the beginning of the sorted sub array, we can move it no further left.
			&& (*j < *(j-1));// if it is no longer smaller than the element on its left, it need not be moved further left.
			 --j) 		// Since we moved it one position left in the block below, move j left to again refer to the newly introduced element.
			{ // Move the jth element one position to its left.
			// Swap with the left-side neighbour in order to move left.
			auto k = j-1;
			auto t = *k;
			*k = *j;
			*j = t;
		}
	}
} // FN: sort

} // NS: insertion_sort

} // NS: vvalgo


