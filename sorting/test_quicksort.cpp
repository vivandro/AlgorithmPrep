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

#include <iostream>
#include <vector>

#include "quicksort.h"

using namespace std;

int main() {

	vector<long long> nums = {12, 45, -4, 0, 23, -99};
	int narr[] = {12, 45, -4, 0, 23, -99};

	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::quicksort::sort(nums.begin(), nums.end());	
	cout << (is_sorted(begin(nums), end(nums)) ? "SORTED" : "UNSORTED") << endl;

	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::quicksort::sort(begin(narr), end(narr));	
	cout << (is_sorted(begin(narr), end(narr)) ? "SORTED" : "UNSORTED") << endl;

	vector<long long> nonums = {};
	int *noarr = NULL;

	cout << (is_sorted(begin(nonums), end(nonums)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::quicksort::sort(nonums.begin(), nonums.end());	
	cout << (is_sorted(begin(nonums), end(nonums)) ? "SORTED" : "UNSORTED") << endl;

	cout << (is_sorted((noarr), (noarr)) ? "SORTED" : "UNSORTED") << endl;
	vvalgo::quicksort::sort((noarr), (noarr));	
	cout << (is_sorted((noarr), (noarr)) ? "SORTED" : "UNSORTED") << endl;
}
