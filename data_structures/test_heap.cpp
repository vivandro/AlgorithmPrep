
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

#include "heap.h"

using namespace std;
using namespace vvalgo;

template <typename T>
void printAll(T b, T e) {
	cout << "************************************************\n";
	for (T i = b; i != e; ++i) {
		cout << *i << " ";
	}
	cout << "\n************************************************\n";
}

int main () {
	vector<long> v = { 99, 89, 79, 69, 59, 49, 39, 29, 19, 9};
    Heap<decltype(v.begin())> heap(begin(v), end(v));

    cout << "Printing original array :\n";
	printAll(begin(v), end(v));
    
    cout << "Printing heap created from that array :\n";
    printAll(begin(heap), end(heap));
    
    cout << "Sorting the heap. This is how it looks after sorting:\n";
    heap.sort();
    printAll(begin(heap), end(heap));
    
    
    long head;
    heap.peekHead(head);
    cout << "head of the heap --> " << head << endl;
    heap.popHead();
    heap.peekHead(head);
    cout << "head of the heap --> " << head << endl;
    heap.popHead();
    heap.peekHead(head);
    cout << "head of the heap --> " << head << endl;
}
