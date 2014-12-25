
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
#include <list>

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
    list<long> l = { 99, 89, 79, 69, 59, 49, 39, 29, 19, 9};
    Heap<decltype(v.begin())> heap(begin(v), end(v));
    Heap<decltype(l.begin())> leap(begin(l), end(l));

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
    
    cout << "Inerting something larger than all other elements : 2000 \n";
    heap.insert(2000);
    printAll(begin(heap), end(heap));
    
    cout << "Inerting something in the middle : 66 \n";
    leap.insert(66);
    printAll(begin(leap), end(leap));
    
    cout << "Inerting something smaller than all other elements : 2 \n";
    leap.insert(2);
    printAll(begin(leap), end(leap));
    
    cout << "Sorting the heap. If the insertions went flawlessly, it will be sorted correctly.\nThis is how it looks after sorting:\n";
    leap.sort();
    printAll(begin(leap), end(leap));
    
    leap.insert(2001);
    leap.insert(-1999);
    leap.insert(-200);
    leap.insert(21);
    printAll(begin(leap), end(leap));
    leap.popHead();
    leap.popHead();
    leap.popHead();
    printAll(begin(leap), end(leap));
    leap.sort();
    printAll(begin(leap), end(leap));

    auto f59 = leap.find(59);
    cout << *f59 << endl;
    leap.updateKey(f59, -1999);
    auto f49 = leap.find(49);
    cout << *f49 << endl;
    leap.updateKey(f49, -2000);
    
    printAll(begin(leap), end(leap));
    leap.sort();
    printAll(begin(leap), end(leap));
    
    
    leap.remove(29);
    printAll(begin(leap), end(leap));
    leap.sort();
    printAll(begin(leap), end(leap));
    leap.remove(2);
    printAll(begin(leap), end(leap));
    leap.sort();
    printAll(begin(leap), end(leap));
    
}
