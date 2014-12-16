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

#ifndef APFN_MISC_BINARY_SEARCH_H
#define APFN_MISC_BINARY_SEARCH_H

namespace vvalgo {
// T needs to be a random access iterator.
template <typename T, typename V>
T binarySearch(T begin, T end, const V &value) { // Why no const for begin and end? Because they are copies, so it doesnt matter.
	if (begin == end) { // If there are no elements in the "array", we cannot find the value.
		return end; // Hence, we have trivially finished the binary search in the negative.
	}

	// We want to find the middle element with a bias towards 'begin' rather than 'end' because the range is [begin, end).
	T mid = begin + (end - begin) / 2;
	// The bias towards begin ensures that if (begin != end), then mid always points to a valid element.

	if (*mid == value) {
		return mid;
	} else if (*mid > value) {
		T loc = binarySearch(begin, mid, value);
		// if the value was not found, the above call will return its 'end' which is the 'mid'.
		// Since we want to use 'end' t indicate failure, we need to translate that mid to end.
		return (loc == mid) ? end : loc;
	} else {
		return binarySearch(mid + 1, end, value);
	}
} // FN: binarySearch

} // NS : vvalgo

#endif // APFN_MISC_BINARY_SEARCH_H
