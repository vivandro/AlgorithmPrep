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

#include <vector>

// Counting sort requires the keys to fall into a limited range. It creates as many buckets as
// the possible values in the range of keys. I am going to modify this requirement a little bit
// without breaking the counting sort algorithm. I am going to require the caller to provide the 
// number of items in the range, say N , and a function that will map the key to a number between
// 0 and N-1.

namespace vvalgo {

namespace counting_sort {

template <typename T, typename V>
void sort(T b, T e, std::function<unsigned long long(V)>mapToBucket, unsigned long long N) {
	// NOTE: Should not have used names begin and end for the arguments. It prevents me
	//       from using the begin(x) and end(x) templates to get x.begin() and x.end().
	using namespace std; // limit the effect of using to be within this function.
	vector<unsigned long long> buckets(N, 0); // N buckets all initialized to 0
	
	// Count the number of times each element maps to a particular bucket.
	for (T i = b; i != e; ++i) {
		++buckets[mapToBucket(*i)];
	}

	// In the same bucket table, replace the count with the effective index of the first entry
	// that maps to this bucket.
	// Goal is that, if an element maps to this bucket, the entry in the bucket should give
	// us the index where it should go in the output.
	for (unsigned long long i = 0, runningElementCount = 0; i < N; ++i) {
		unsigned long long itemsInIthBucket = buckets[i];
		buckets[i] = runningElementCount;// if we have found x elements by now, the next item 
						 // goes in location x.
		runningElementCount += itemsInIthBucket;
	}

	// Now, create a copy of the existing container into a vector so that 
	// we can refer to the original order of the elements even while we replace the 
	// elements in the original array with items in the sorted order.
	vector<V> elemCopy(b, e);

	// Now map each element from elemCopy to the original container at the location
	// indicated in buckets[]
	for (auto i = begin(elemCopy); i != end(elemCopy); ++i) {
		auto bucket = mapToBucket(*i);
		auto destIndex = buckets[bucket];
		*(b+destIndex) = *i;
		// since we have already added an element at destIndex, increment the location
		// specified in buckets[bucket]
		++buckets[bucket];
	}
}

} // NS : counting_sort

} // NS : vvalgo

