
#include "insertion.h"

#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_container(T container) {
	for (auto i : container) {
		cout << i << " ";
	}
}

int main()  {

	vector<int> v {1, -22, 6, -8, 99, 20};

	print_container(v);
	cout << (is_sorted(v.begin(), v.end()) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::insertion_sort::sort(v.begin(), v.end());
	print_container(v);
	cout << (is_sorted(v.begin(), v.end()) ? "SORTED" : "UNSORTED") << endl;

}

