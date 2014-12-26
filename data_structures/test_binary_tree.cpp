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
 * General traversal function. It invokes pre(), in() and post() callbacks in the pre-order, inorder 
 * and post-order traversal fashion.
 *
 * Important Points to Note:
 * - On Callbacks: If we perform a particular traversal, we guarantee that the relevant callback will be executed.
 * - On Traversal: Once a callback returns true, to indicate that the traversal can stop, we prevent further traversal.
 *
 * As a result of these two points, an interesting situation arises. If we have gone down the left
 * subtree and some callback returns true, do we invoke the in() callback of the node? If we had gone
 * down the right subtree and then a callback returned true, do we invoke the post() callback?
 * The answer is, yes we do. This comes from the first of the two assurances we mentioned above. If
 * we have performed a particular traversal, we will invoke the relevant callback.
 *
 * This has a very interesting repurcussions on the way you would write callbacks. Since all the pre() callbacks
 * are called once we descend down a tree, pre() will never be invoked once any of the callbacks stops the traversal.
 * in() is performed after the left subtree has been traversed (may be partially traversed if a callback stopped the
 * traversal). This means, in() should be invoked regardless of whether or not further traversal has been cancelled.
 * Similar situation applies for post(). Once we have traversed down the right subtree, we are obliged to invoke
 * post() regardless of any indications related to stopping traversal.
 *
 */
template <typename T, typename U, typename V, typename W> // TIP: Always use different typenames for template arguments.
                                                          // Template argument deduction is best left to the compiler. Trying
                                                          // to force some of the apparently equivalent signatures is not a good
                                                          // idea because template instantiation does not do type conversion, making
                                                          // it too easy to fail during compilation.
void traverse(T *root, U pre, V in, W post) {
    bool stopTraversal = false;
    std::function<void (T *)> traversalHelper = [&](T *node) {
        if (stopTraversal || !node) {
            return;
        }
        
        if (pre(node)) { // Perform pre-order processing
            stopTraversal = true; // I'm avoiding if (stopTraversal = foo(node)) because that has the potential to
            // set stopTraversal to false. We don't ever want to do that except during
            // initialization. This simple constraint on stopTraversal will help us avoid
            // bugs where it gets reset to false after it was set to true. Once set to true,
            // it should always remain true. Plus, that condition also has the potential of
            // confusing future generations who might just look at it as a bug where we used
            // a single '=' instead of '=='.
            return;
        }
        
        traversalHelper(node->lChild); // Traverse the left subtree.
        if (in(node)) { // // Perform inorder processing.
            stopTraversal = true;
        }
        if (stopTraversal) {
            return;
        }
        
        traversalHelper(node->rChild); // Traverse the righ subtree.
        if (post(node)) { // Perform post-order processing
            stopTraversal = true;
        }
    };
    
    // Kick off the traversal
    traversalHelper(root);
}

/*
 * The function foo passed to the traversal function should process the node
 * and return true if it wants the traversal to continue and false if it
 * wants the traversal to stop.
 * expected signature for foo(): bool (*)(T *); // return true if you have accomplished your goal and want traversal to stop prematurely.
 * It is our responsibility to ensure that foo() is never called once it has returned true. This way,
 * all the complexity related to ensuring this lies within the traversal code rather than being spread 
 * out among all the implementations of foo(). It would incur a much higher overall test load if that
 * were the case. And that will result in less bugs in the overall system.
 */
template <typename T, typename V>
    void inorderTraverse(T *root, V foo) {
    auto noop = [](T *){return false;};
    traverse(root, noop, foo, noop);
} // FN : inorderTraverse

template <typename T, typename V>
void preorderTraverse(T *root, V foo) {
    auto noop = [](T *){return false;};
    traverse(root, foo, noop, noop);
} // FN : preorderTraverse

template <typename T, typename V>
void postorderTraverse(T *root, V foo) {
    auto noop = [](T *){return false;};
    traverse(root, noop, noop, foo);
} // FN : postorderTraverse

template <typename T, typename V>
T *findNodeWithValue(T *root, V value) {
	T *match = nullptr;
    
	auto finder = [&match, &value] (T *node) -> bool {
		if ( node && (node->value == value) ) {
			match = node;
            return true;// True indicates that we have accomplished our task and traversal can end prematurely.
		}
        return false;
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
                return true;
			}
			T *r = node->rChild;
			if (r && (r->value == value)) {
				parent = node;
                return true;
			}
		}
        return false;
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
	inorderTraverse(root, [](BinaryTree<ll> *node) -> bool{
        cout << node->value << " ";
        // since we do not want the traversal to stop prematurely, we always return false.
        return false;
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
    
    auto printer = [](const BinaryTree<ll> *node) -> bool {
        cout << node->value << " ";
        // since we do not want the traversal to stop prematurely, we always return false.
        return false;
    };
    auto dummy = [](const BinaryTree<ll> *node) -> bool {return false;};
    cout << "\nPreorder traversal\n";
    preorderTraverse(root, printer);
    cout << endl;
    cout << "\nInorder traversal\n";
    traverse( root,
             dummy,
             printer,
             dummy);
    cout << endl;
    cout << "\nPostorder traversal\n";
    postorderTraverse(root, printer);
    cout << endl;
}
