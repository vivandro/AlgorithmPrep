
#include "insertion.h"

#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_container(T beg, T end) {
	for (; beg != end; ++beg) {
		cout << *beg << " ";
	}
}

int main()  {

	vector<int> v {1, -22, 6, -8, 99, 20};

	print_container(begin(v), end(v));
	cout << (is_sorted(v.begin(), v.end()) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::insertion_sort::sort(v.begin(), v.end());
	print_container(begin(v), end(v));
	cout << (is_sorted(v.begin(), v.end()) ? "SORTED" : "UNSORTED") << endl;

	int narr[] = {12, 45, -4, 0, 23, -99};
	print_container(begin(narr), end(narr));
	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::insertion_sort::sort(begin(narr), end(narr));	
	print_container(begin(narr), end(narr));
	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;
}

