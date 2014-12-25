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
        typedef decltype(storage.begin()) Iterator;

        // Constructors :
        Heap(OrderPredicate op = std::less<ValueType>()):orderPredicate(op){}
        Heap(T b, T e, OrderPredicate op = std::less<ValueType>()):orderPredicate(op),storage(b, e) {buildHeap(storage.begin(), storage.end());}
        
        // Iterators :
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

        // Basics :
        // Returns true if the heap is empty
        bool isEmpty() {return storage.empty();}
        // Returns true if the heap has at least one element. Copies the head element into the passed
        // reference.
        bool peekHead(ValueType &head) {
            if (isEmpty()) {
                return false;
            }
            head = storage[0];
            return true;
        }
        
        // Updation :
        // Removes the head element from the heap.
        void popHead() { removeHead(); }

        // Inserts a new element into the heap.
        void insert(ValueType element) {
            storage.push_back(element);
            heapifyUp(storage.begin(), storage.end(), storage.begin() + (storage.size() - 1) );
        }
        
        // Removes the element from the heap.
        void remove(ValueType value) {
            remove(find(value));
        }
        void remove(Iterator element) {
            if (element == storage.end()) {
                return;
            }
            auto lastElement = (storage.begin() + (storage.size() - 1));
            std::swap(*element, *lastElement);
            storage.erase(lastElement);
            if (orderPredicate(*parent(storage.begin(), storage.end(), element), *element)) {
                heapifyDown(storage.begin(), storage.end(), element);
            } else {
                heapifyUp(storage.begin(), storage.end(), element);
            }
        }
        
        // Change the value of a key (this could happen in cases where an event forces us to update
        // priority of an entry - ex. priority inheritance to solve priority inversion)
        void updateKey(Iterator element, ValueType updatedVal) {
            if (element == storage.end()) {
                return;
            }
            // In order to avoid repetitive code, we can re-imagine update-key as
            // 1. remove old key.
            // 2. insert new key.
            remove(element);
            insert(updatedVal);
        }
                
        // Miscellaneous
        /* Something I need to fix soon. I think I need to study type deduction in a bit more detail - whenever I have time!
        const Iterator find(ValueType value) {
            return const_cast<Iterator>(std::find(storage.begin(), storage.end(), value));
        }
         */
        // The problem with this return value is that the user can modify the key. That could destroy the heap-ness of the heap.
        // We need to return a constant Iterator.
        Iterator find(ValueType value) {
            return std::find(storage.begin(), storage.end(), value);
        }
        
        size_t size() {return storage.size();}
        // Unlike the text-book heapsorts, I'm going to reverse the entries after we have finished the
        // usual heap sort. This will ensure that the heap still obeys the heap properties after being sorted.
        void sort() {sortHeap(storage.begin(), storage.end());reverse(storage.begin(), storage.end());}
        
    private: // I'm using begin and end iterators in all these private methods so that if need be, these can be
             // exported to the outside world for it to use them with their containers.
        Iterator leftChild(Iterator b, Iterator e, Iterator parent) { // Have to use names like b and e since begin and end conflict with template functions
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
        
        Iterator rightChild(Iterator b, Iterator e, Iterator parent) { // Have to use names like b and e since begin and end conflict with template functions
            auto lChild = leftChild(b, e, parent);
            if (lChild != e) {
                return lChild + 1;
            } else {
                return lChild;
            }
        }
        
        Iterator parent(Iterator b, Iterator e, Iterator child) {
            // 0 -> 1, 2
            // 1 -> 3, 4
            // 2 -> 5, 6
            // 3 -> 7, 8
            // l -> 2p+1, r = 2a+2 , this means that left child always has an odd index while the right
            //                       child has the immediately next even index.
            // so, p = (l-1)/2 and (r-2)/2
            // so we can just find the closest even number and conver it to rchild index
            unsigned long long childIndex = child - b;
            unsigned long long rChildIndex = childIndex + (childIndex%2);
            unsigned long long parentIndex = (rChildIndex - 2) / 2;
            // this formula does fail when childIndex is 0, so provide a short-circuit for that
            if (childIndex == 0) {
                return e; // The head/root of the hap has no parent.
            }
            return b + parentIndex;
        }
        
        void heapifyDown(Iterator b, Iterator e, Iterator parent) {
            auto lChild = leftChild(b, e, parent);
            auto rChild = rightChild(b, e, parent);
            
            if (rChild == lChild) { // can only happen if both are equal to e
                return;
            }
            
            // Find the smaller of the chldren in order to decide if the parent satisfies the min heap condition.
            // At this point, we are sure that at least left child is valid.
            auto minChild = lChild;
            if (rChild != e) { // If the right child exists as well, it may possibly be the smaller of the two children.
                minChild = orderPredicate(*lChild, *rChild) ? lChild : rChild;
            }
            
            if (!orderPredicate(*parent, *minChild)) { // If the minimum child is smaller than the parent
                // Swap the parent and smaller child
                std::swap(*parent, *minChild);
                //heapifyDown(b, e, minChild); // Tail-recursion (so can be optimized away by the compiler tools.
            }
            heapifyDown(b, e, minChild); // Tail-recursion (so can be optimized away by the compiler tools.
        }
        
        void heapifyUp(Iterator b, Iterator e, Iterator element) {
            if (element == b) { // If we are trying to heapify up the head/root.
                return; // Heapification has successfully completed.
            }
            auto l_parent = parent(b, e, element); // I am considering using come standard coding guidelines after having to use l_parent for my local variable.
            if (!orderPredicate(*l_parent, *element)) { // If the ordering between parent and child satisfies the heap orderPredicate
                std::swap(*l_parent, *element);
                //return; // heapification has been successfully completed and we need not proceed further up.
            }
            
            heapifyUp(b, e, l_parent); // Tail-recursion (so can be optimized away by the compiler tools.
        }
        
        void buildHeap(Iterator b, Iterator e) {
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
        Iterator extractHead(Iterator b, Iterator e) {
            if ( (b == e) || ((b + 1) == e) ) {
                return b;
            }
            
            long long N = e - b;
            std::swap(*b, *(b+N-1));
            heapifyDown(b, b + N - 1, b);
            return b + N - 1;
        }
        
        void removeHead() {
            auto headsNewLocation = extractHead(storage.begin(), storage.end());
            if (headsNewLocation != storage.end()) {
                storage.erase(headsNewLocation);
            }
        }

        void sortHeap(Iterator b, Iterator e) { // We are calling this sortHeap because we are going to sort with the assumption that
            // the container is already a heap (heapified possibly by calling buildHeap().
            long long N = e - b;
            
            for (long long i = 0; i < N; ++i) {
                auto currentEnd = b + N - i;
                extractHead(b, currentEnd);
            }
        }
        
    }; // CS : Heap
    
} // NS : vvalgo

#endif // APFN_DATA_STRUCTURES_HEAP_H
