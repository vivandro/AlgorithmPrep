#ifndef APFN_SORTING_MERGE_H
#define APFN_SORTING_MERGE_H

#include <vector>

namespace vvalgo {

namespace merge {

// Forward declarations:
template <typename T, typename V>
void sortHelper(T begin, T end, V scratchpad);
template <typename T, typename V>
void mergeHelper(T beg1, T end1, T beg2, T end2, T begDest, V scratchpad);
// End of forward declarations.


template <typename T>
void sort(T begin, T end) {
	typedef typename T::value_type V;
	std::vector<V> scratchpad(end-begin);
	sortHelper(begin, end, scratchpad);
} // FN : sort

// Overloaded template method for handling pointers
template <typename T>
void sort(T *begin, T *end) {
	std::vector<T> scratchpad(end-begin);
	sortHelper(begin, end, scratchpad);
} // FN : sort

template <typename T, typename V>
void sortHelper(T begin, T end, V scratchpad) {
	using namespace std;
	if ( (begin == end) 		// Empty container.
	     || ((begin+1) == end) ) 	// Single element in the container.
	{
		return; // Container is trivially sorted.
	}

	T mid = begin + (end - begin) / 2;

	sortHelper(begin, mid, scratchpad);
	sortHelper(mid, end, scratchpad);
	mergeHelper(begin, mid, mid, end, begin, scratchpad);
} // FN : sortHelper

// LL (Lesson Learnt) : Function names can cause name conflicts with namespace names. cannot use merge as the name for this function.
template <typename T, typename V>
void mergeHelper(T beg1, T end1, T beg2, T end2, T begDest, V scratchpad) {
	auto i = scratchpad.begin();	// Refers to the location in scratchpade that can be written on.
	for ( ; 
	      (beg1 != end1) 	// while first container has elements
	      && (beg2 != end2);// AND, the second one also has elements
	      ++i)
	{ // compare the next available elements from the two sorted arrays and copy the smallest into the scratchpad
		if (*beg1 < *beg2) {
			*i = *beg1;
			++beg1;
		} else {
			*i = *beg2;
			++beg2;
		}
	}

	for (; beg1 != end1; ++i, ++beg1) {
		*i = *beg1;
	}

	for (; beg2 != end2; ++i, ++beg2) {
		*i = *beg2;
	}

	// At this point, i refers to one past the last element that was written to the scratchpad
	for (auto j = scratchpad.begin(); j != i; ++j, ++begDest) {
		*begDest = *j;
	}
} // FN : mergeHelper

} // NS : merge

} // NS: vvalgo

#endif // APFN_SORTING_MERGE_H
