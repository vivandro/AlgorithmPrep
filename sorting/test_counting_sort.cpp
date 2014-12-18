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
#include "counting_sort.h"

using namespace std;

template <typename T>
void printAll(T b, T e) {

	cout << "-------------------------- \n";
	for (; b != e; ++b) {
		std::cout << *b << " ";
	}
	cout << "\n-------------------------- \n";

}

int main() {

	vector<long long> nums = {12, 45, -12, -4, 4, 0, 23, -99};
	int narr[] = {12, 45, -12, -4, 4, 0, 23, -99};

	// Cannot use auto to declare map256 because template resolution does not perform
	// type conversion (here it is needed from lambda to std::function.
	// I should get back to this later and see I can parametrize the whole type of mapToBucket
	// without losing anything useful.
	// By the time I finished the counting sort code I realized that I need V. This means that 
	// I either learn some type system magic (probably typeof or typeid) in orger to get to V
	// or expose the std:function.... type to the user forcing him to specify it explicitly
	// for his parameter. I better learn type magic soon!
	std::function<unsigned long long(long long)> map256 = [](long long num) -> unsigned long long {
		if (num < 0) {
			num *= -1; // Since -ve numbers have special binary representation, make them positive first.
		}
		return num & 0xFF;
	};

	printAll(begin(nums), end(nums));
	vvalgo::counting_sort::sort(begin(nums), end(nums), map256, 256);	
	printAll(begin(nums), end(nums));

	printAll(begin(narr), end(narr));
	vvalgo::counting_sort::sort(begin(narr), end(narr), map256, 256);
	printAll(begin(narr), end(narr));

	vector<long long> nonums = {};
	int *noarr = NULL;

	printAll(begin(nonums), end(nonums));
	vvalgo::counting_sort::sort(nonums.begin(), nonums.end(), map256, 256);
	printAll(begin(nonums), end(nonums));

	printAll((noarr), (noarr));
	vvalgo::counting_sort::sort((noarr), (noarr), map256, 256);	
	printAll((noarr), (noarr));
}
