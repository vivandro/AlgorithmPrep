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
namespace vvalgo {

template <typename T>
class BinaryTree {
public:
T value;
BinaryTree * lChild; // TODO: convert to unique_ptr
BinaryTree * rChild; // TODO: convert to unique_ptr

// It is important to always allocate BinaryTree objects on the heap because we are calling delete 
// in the destructor for the children. Except for the root, every node in the BinsryTree needs to be
// allocated on the heap for this to work correctly. The ideal way would be to not use this exception and 
// just allocate the root on the heap as well.
BinaryTree(T val, BinaryTree * l=nullptr, BinaryTree *r = nullptr) : value(val), lChild(l), rChild(r) {}

~BinaryTree() {
	delete lChild; // It is safe to pass nullptr to delete, so no need to check for it.
	delete rChild; 
}

void replaceLeftChild(BinaryTree *newLChild) {
	delete lChild;
	lChild = newLChild;
}

void replaceRightChild(BinaryTree *newRChild) {
	delete rChild;
	rChild = newRChild;
}

// I'm leaving the traversal methods outside of this class because they are not tightly
// coupled with this implementation. They only require the object to have value, *lChild and *rchild
// public members.
// By keeping the traversal and related methods outside, I am enabling them to work
// on BinaryTree as well as BinarySearchTree (and potentially also on SinglyLinkedList in which I
// could set lChild always to nullptr).
private:

}; // CS : BinaryTree

/*
 * The function foo passed to the traversal function should process the node
 * and return true if it wants the traversal to continue and false if it
 * wants the traversal to stop.
 * expected signature: bool (*)(T *);
 */
template <typename T, typename V>
void inorderTraverse(T *root, V foo) {
	if (!root) {
		return;
	}
	bool fooAlreadyReturnedFalse = false;
	auto fooBar = [&fooAlreadyReturnedFalse, &foo](T *node) -> bool {
		bool foosReturnValue = foo(node);
		fooAlreadyReturnedFalse = (false == foosReturnValue);
		return foosReturnValue;
	};

	inorderTraverse(root->lChild, foo);
	if (fooAlreadyReturnedFalse || !foo(root)) {
		return;
	}
	inorderTraverse(root->rChild, foo);
	
} // FN : inorderTraverse

template <typename T, typename V>
T *findNodeWithValue(T *root, V value) {
	T *match = nullptr;

	auto finder = [&match, &value] (T *node) -> bool {
		if (node && (node->value == value)) {
			match = node;
			return false;
		}
		return true;
	};

	inorderTraverse(root, finder);

	return match;
}

/*
 * This method returns a pointer to the parent node of the node with value 'value'. The problem
 * with this scenario is that if the root contains 'value' then we do not have a parent. But another
 * case where we cannot have a parent is if there is no node with value equal to 'value'. To
 * differentiate between these two situations, it is not enough to just return the pointer to the parent
 * but also to indicate, in case of failure, if the failure is a result of finding the value in the
 * root node. We allow this by asking the caller to pass a reference to a bool which we will set
 * to true, if value is found in the root. It will be set to false if no node contains the value.
 * And it's value is false if we actually found the parent node. We return the parent node
 * when found, and return nullptr otherwise.
 */
template <typename T, typename V>
T *findParentOfNodeWithValue(T *root, V value, bool &foundValueInRoot) {
	T *parent = nullptr;
	if (root && root->value == value) {
		foundValueInRoot = true;
		return nullptr;
	}
	foundValueInRoot = false;// This parameter will not be changed in the rest of the code below.

	auto finder = [&parent, &value] (T *node) -> bool {
		if (node) {
			T *l = node->lChild;
			if (l && (l->value == value)) {
				parent = node;
				return false;
			}
			T *r = node->rChild;
			if (r && (r->value == value)) {
				parent = node;
				return false;
			}
		}
		return true;
	};

	inorderTraverse(root, finder);

	return parent;
}

} // NS : vvalgo

#include <iostream>

using namespace std;
using namespace vvalgo;

typedef long long ll;

int main() {
	auto *root = new BinaryTree<ll>{100};
	cout << root->value << endl;

	root->replaceLeftChild(new BinaryTree<ll>{50});
	root->replaceRightChild(new BinaryTree<ll>{200});

	cout << "\nInorder traversal\n";
	inorderTraverse(root, [](BinaryTree<ll> *node){
							cout << node->value << " "; 
							return true;
						      });
	cout << endl;

	auto node = findNodeWithValue(root, 100);
	auto node2 = findNodeWithValue(root, 200);

	cout << " 100 =?= " << node->value << endl;
	cout << " 200 =?= " << node2->value << endl;

	bool valueFoundInRoot = false;
	auto p0 = findParentOfNodeWithValue(root, 150, valueFoundInRoot);
	cout << " is 100 the parent of 150? --> ";
	p0 ? (cout << p0->value) : cout << "nope";
	cout << endl;
	p0 = findParentOfNodeWithValue(root, 50, valueFoundInRoot);
	cout << " is 100 the parent of 50? --> ";
	p0 ? (cout << p0->value) : cout << "nope";
	cout << endl;
}
