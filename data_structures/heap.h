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

#ifdef APFN_DATA_STRUCTURES_HEAP_H
#define APFN_DATA_STRUCTURES_HEAP_H

namespace vvalgo {

namespace MinHeap {	// The definition of the heap related algorithms seem to make it quite clear that
		// most facilities related to heap can stand on their own. So practically I need
		// to allow the callers to provide the begin and end iterators on their
		// random access container and the functions provided in MinHeap will work on those.
		// I could also provided a default implementation for all these functions (within a class) that woks
		// on an internal vector based storage, but it would be redundant as far as practice
		// code goes. It will definitely make sense in a full blown design, but I will
		// avoid providing such implementation here since I do not have enough time to test it.


template <typename T>
T leftChild(T b, T e, T parent) { // Have to use names like b and e since begin and end conflict with template functions
	if ( (b == e) || (parent == e) ) {
		return e;
	}

	unsigned long long n = e - b;
	unsigned long long pIndex = parent - b;
	// 0 -> 1, 2
	// 1 -> 3, 4
	// 2 -> 5, 6
	// 3 -> 7, 8
	unsigned long long lChildIndex = pIndex * 2 + 1;
	if (lChildIndex >= n) {
		return e;
	} else {
		return b + lChildIndex;
	}
}

template <typename T>
T rightChild(T b, T e, T parent) { // Have to use names like b and e since begin and end conflict with template functions
	T lChild = leftChild(b, e, parent);
	if (lChild != e) {
		return lChild + 1;
	} else {
		return lChild;
	}
}

template <typename T>
void buildHeap(T b, T e) {

	// Since the heap is an almost complete binary tree, 

}

} // NS : MinHeap

} // NS : vvalgo

#endif // APFN_DATA_STRUCTURES_HEAP_H
