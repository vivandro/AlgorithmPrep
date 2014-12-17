
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

#include "random_select.h"

using namespace std;

template <typename T>
void printAll(T begin, T end) {
	cout << "========================================================\n";
	for (; begin != end; ++begin) {
		cout << *begin  << " ";
	}
	cout << "\n========================================================\n";
}
int main()
{
	vector<long long> v = { 23, 43, 6 , 9, -2, 100, -6, 200};
	printAll(begin(v), end(v));
	cout << " 1 --> " << *(vvalgo::selectKthSmallest(begin(v), end(v), 1)) << endl;
	printAll(begin(v), end(v));
	cout << " 2 --> " << *(vvalgo::selectKthSmallest(begin(v), end(v), 2)) << endl;
	printAll(begin(v), end(v));
	cout << " 3 --> " << *(vvalgo::selectKthSmallest(begin(v), end(v), 3)) << endl;
	printAll(begin(v), end(v));
	cout << " 4 --> " << *(vvalgo::selectKthSmallest(begin(v), end(v), 4)) << endl;
	printAll(begin(v), end(v));
}
