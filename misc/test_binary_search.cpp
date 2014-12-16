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

#include "binary_search.h"

using namespace std;

template <typename T>
void printAll(T begin, T end) {
	for (; begin != end; ++begin) {
		cout << *begin << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> v = {34, 69, 9, -23, 42};

	sort(begin(v), end(v));

	printAll(begin(v), end(v));

	auto loc = vvalgo::binarySearch(begin(v), end(v), 9);
	cout << ((loc != end(v)) ? "FOUND" : "NOT FOUND") << endl;

	loc = vvalgo::binarySearch(begin(v), end(v), 7);
	cout << ((loc != end(v)) ? "FOUND" : "NOT FOUND") << endl;

	loc = vvalgo::binarySearch(begin(v), end(v), -23);
	cout << ((loc != end(v)) ? "FOUND" : "NOT FOUND") << endl;

	loc = vvalgo::binarySearch(begin(v), end(v), 69);
	cout << ((loc != end(v)) ? "FOUND" : "NOT FOUND") << endl;
}
