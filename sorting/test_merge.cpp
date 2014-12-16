
#include <iostream>
#include <vector>

#include "merge.h"

using namespace std;

int main() {

	vector<long long> nums = {12, 45, -4, 0, 23, -99};
	int narr[] = {12, 45, -4, 0, 23, -99};

	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::merge::sort(nums.begin(), nums.end());	
	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;

	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::merge::sort(begin(narr), end(narr));	
	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;
}
