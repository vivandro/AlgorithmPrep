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

#ifndef APFN_DATA_STRUCTURES_HEAP_H
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
void swap(T &a, T &b) {
	T t = a;
	a = b;
	b = t;
}

template <typename T>
void minHeapifyDown(T b, T e, T parent) {
	T lChild = leftChild(b, e, parent);
	T rChild = rightChild(b, e, parent);

	if (rChild == lChild) { // can only happen if both are equal to e
		return;
	}

	// Find the smaller of the chldren in order to decide if the parent satisfies the min heap condition.
	// At this point, we are sure that at least left child is valid.
	T minChild = lChild;
	if (rChild != e) { // If the right child exists as well, it may possibly be the smaller of the two children.
		minChild = (*lChild < *rChild) ? lChild : rChild;
	}

	if (*minChild < *parent) { // If the minimum child is smaller than the parent
		// Swap the parent and smaller child 
		swap(*parent, *minChild);
		minHeapifyDown(b, e, minChild);
	}
}

template <typename T>
void buildHeap(T b, T e) {
	if ( (b == e) || ((b + 1) == e) ) {
		return; // An array with 0 or 1 element is already a heap.
	}

	// Since the heap is an almost complete binary tree, the right half contains all leaves.
	// e.x., leftChild(n/2) --> n+1
	// But, leftChild(n/2 - 1) --> 2(n/2-1)+1 --> n - 1
	long n = e - b;
	for (long i = n / 2 - 1; i >= 0; --i) {
		minHeapifyDown(b, e, b+i);
	}
}

/*
 * Similar to STL algorithms, we take care to just modify the arrangement of the
 * elements in the array rather than delete any of them. As such, iterators suffice as input.
 */
template <typename T>
T extractMin(T b, T e) {
	if ( (b == e) || ((b + 1) == e) ) {
		return b;
	}

	long long N = e - b;
	swap(*b, *(b+N-1));
	minHeapifyDown(b, b + N - 1, b);
	return b + N - 1;
}

template <typename T>
void sortHeap(T b, T e) { // We are calling this sortHeap because we are going to sort with the assumption that 
			  // the container is already a heap (heapified possibly by calling buildHeap().
	long long N = e - b;

	for (long long i = 0; i < N; ++i) {
		T currentEnd = b + N - i;
		extractMin(b, currentEnd);
	}
}

} // NS : MinHeap

} // NS : vvalgo

#endif // APFN_DATA_STRUCTURES_HEAP_H
