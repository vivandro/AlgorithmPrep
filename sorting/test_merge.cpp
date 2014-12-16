
#include <iostream>
#include <vector>

#include "merge.h"

using namespace std;

int main() {

	vector<long long> nums = {12, 45, -4, 0, 23, -99};

	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;

	vvalgo::merge::sort(nums.begin(), nums.end());	

	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;
}
