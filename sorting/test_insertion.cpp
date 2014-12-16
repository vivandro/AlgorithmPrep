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

