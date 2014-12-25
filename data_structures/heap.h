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

#ifndef APFN_DATA_STRUCTURES_HEAP_H
#define APFN_DATA_STRUCTURES_HEAP_H

#include <vector>       // std::vector for internal storage that grows in amortised linear time.
#include <functional>   // std::less (the default ordering predicate)
#include <algorithm>    // std::swap

namespace vvalgo {
    /*
     A Heap is an in-place Priority Queue. It is defined by the following properties:
     1. A transitive ordering between the parent and its children. In a min-heap, the min function defines the order
     as *parent <= *children. Based on this requirement, we want the ordering function to be supplied by the
     creator of the instance. We want it to be parametrized. We also want to assume a default ordering function.
     2. We will use our own internal storage for the heap instead of mrely providing functions
     that a caller can use on his/her own storage. This is for the sake of simplification as well
     as for providing a more powerful and well rounded heap data structure.
     */
    
    template <typename T, typename ValueType = typename T::value_type, typename OrderPredicate = std::function<bool (ValueType, ValueType) > >
    class Heap {
    private: // private data. Needs to be declared before I can use it in the decltypes below.
        std::vector<ValueType> storage;
        OrderPredicate orderPredicate;
        
    public:
        Heap(OrderPredicate op = std::less<ValueType>()):orderPredicate(op){}
        Heap(T b, T e, OrderPredicate op = std::less<ValueType>()):orderPredicate(op),storage(b, e) {buildHeap(storage.begin(), storage.end());}
        
        // We only return const iterators because allowing the user to modify
        // the values of the heap contents at random locations will
        // destroy the heap proprty. Instead, the user needs to use the operator[]
        // for such modifications. // TODO: It should be possible to write my own
        // iterator classes tha will allow such modifications by translating the
        // iterator content modification call to operator[] call. Am keeping it simple for now.
        auto begin() -> decltype (storage.cbegin()) const {return storage.cbegin();}
        auto end() -> decltype (storage.cend()) const {return storage.cend();}
        auto rbegin() -> decltype (storage.crbegin()) const {return storage.crbegin();}
        auto rend() -> decltype (storage.crend()) const {return storage.crend();}
        // TODO: add operator[]() here
        
        
        // Unlike the text-book heapsorts, I'm going to reverse the entries after we have finished the
        // usual heap sort. This will ensure that the heap still obeys the heap properties after being sorted.
        void sort() {sortHeap(storage.begin(), storage.end());reverse(storage.begin(), storage.end());}
        bool isEmpty() {return storage.empty();}
        bool peekHead(ValueType &head) {
            if (isEmpty()) {
                return false;
            }
            head = storage[0];
            return true;
        }
        void popHead() { removeHead(); }
        
    private:
        T leftChild(T b, T e, T parent) { // Have to use names like b and e since begin and end conflict with template functions
            if ( (b == e) || (parent == e) ) {
                return e;
            }
            
            unsigned long long n = e - b;
            unsigned long long pIndex = parent - b;
            // 0 -> 1, 2
            // 1 -> 3, 4
            // 2 -> 5, 6
            // 3 -> 7, 8
            unsigned long long lChildIndex = pIndex * 2 + 1;
            if (lChildIndex >= n) {
                return e;
            } else {
                return b + lChildIndex;
            }
        }
        
        T rightChild(T b, T e, T parent) { // Have to use names like b and e since begin and end conflict with template functions
            T lChild = leftChild(b, e, parent);
            if (lChild != e) {
                return lChild + 1;
            } else {
                return lChild;
            }
        }
        
        void heapifyDown(T b, T e, T parent) {
            T lChild = leftChild(b, e, parent);
            T rChild = rightChild(b, e, parent);
            
            if (rChild == lChild) { // can only happen if both are equal to e
                return;
            }
            
            // Find the smaller of the chldren in order to decide if the parent satisfies the min heap condition.
            // At this point, we are sure that at least left child is valid.
            T minChild = lChild;
            if (rChild != e) { // If the right child exists as well, it may possibly be the smaller of the two children.
                minChild = orderPredicate(*lChild, *rChild) ? lChild : rChild;
            }
            
            if (orderPredicate(*minChild, *parent)) { // If the minimum child is smaller than the parent
                // Swap the parent and smaller child
                std::swap(*parent, *minChild);
                heapifyDown(b, e, minChild);
            }
        }
        
        void buildHeap(T b, T e) {
            if ( (b == e) || ((b + 1) == e) ) {
                return; // An array with 0 or 1 element is already a heap.
            }
            
            // Since the heap is an almost complete binary tree, the right half contains all leaves.
            // e.x., leftChild(n/2) --> n+1
            // But, leftChild(n/2 - 1) --> 2(n/2-1)+1 --> n - 1
            long n = e - b;
            for (long i = n / 2 - 1; i >= 0; --i) {
                heapifyDown(b, e, b+i);
            }
        }
        
        /*
         * Similar to STL algorithms, we take care to just modify the arrangement of the
         * elements in the array rather than delete any of them. As such, iterators suffice as input.
         */
        T extractHead(T b, T e) {
            if ( (b == e) || ((b + 1) == e) ) {
                return b;
            }
            
            long long N = e - b;
            std::swap(*b, *(b+N-1));
            heapifyDown(b, b + N - 1, b);
            return b + N - 1;
        }
        
        void removeHead() {
            T headsNewLocation = extractHead(storage.begin(), storage.end());
            if (headsNewLocation != storage.end()) {
                storage.erase(headsNewLocation);
            }
        }

        void sortHeap(T b, T e) { // We are calling this sortHeap because we are going to sort with the assumption that
            // the container is already a heap (heapified possibly by calling buildHeap().
            long long N = e - b;
            
            for (long long i = 0; i < N; ++i) {
                T currentEnd = b + N - i;
                extractHead(b, currentEnd);
            }
        }
        
    }; // CS : Heap
    
} // NS : vvalgo

#endif // APFN_DATA_STRUCTURES_HEAP_H
