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
    template <typename T, typename U, typename V, typename W>
    void traverse(T *root, U pre, V in, W post) {
        bool stopTraversal = false;
        std::function<void (T *)> traversalHelper = [&](T *node) {
            if (stopTraversal || !node) {
                return;
            }
            
            if (pre(node)) { // Perform pre-order processing
                stopTraversal = true;
                return;
            }
            
            traversalHelper(node->left); // Traverse the left subtree.
            if (in(node)) { // // Perform inorder processing.
                stopTraversal = true;
            }
            if (stopTraversal) {// Keeping this out of the if (in(node)) block allows us to return if stopTraversal was
                                // initially set to true inside the call traversalHelper(node->left)
                return;
            }
            
            traversalHelper(node->right); // Traverse the righ subtree.
            if (post(node)) { // Perform post-order processing
                stopTraversal = true;
            }
        };
        
        // Kick off the traversal
        traversalHelper(root);
    }
    
    /*
     * Expected signature for foo(): bool (*)(T *); // return true if you have accomplished your goal and want traversal to stop prematurely.
     *
     * It is our responsibility to ensure that foo() is never called once it has returned true. This way,
     * all the complexity related to ensuring this behavior lies within the traversal code rather than being spread
     * out among all the implementations of foo(). This will result in less bugs in the system by reducing the
     * number of code-paths to be tested.
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
    
    namespace BST { // Encapsulating BST related functions inside a separate namespace.
        // find() will perform binary search since we are dealing with a binary search tree
        template <typename BSTType, typename ValueType>
        BSTType *find(BSTType *root, ValueType val) {
            if (!root || (val == root->value)) {
                return root;
            }
            if (val < root->value) {
                return find(root->left, val);
            }
            return find(root->right, val);
        }
        
        // insert() will perform a binary search to find the entry or insert the node at the right location
        template <typename BSTType, typename ValueType>
        BSTType *insert(BSTType **root, ValueType val) {
            if (!root) {
                return nullptr;
            }
            if (!(*root)) {
                *root = new BSTType(val);
                return *root;
            }
            if (val < (*root)->value) {
                return insert(&(*root)->left, val);
            }
            return insert(&(*root)->right, val);
        }
        
    } // NS : BST
    
    
    template <typename ValueType, typename OrderPredicateType = std::function<bool (const ValueType&, const ValueType&)>>
    class RBTree {
    public:
        ValueType value;
        RBTree *left;   // TODO: convert to unique_ptr
        RBTree *right;  // TODO: convert to unique_ptr
        RBTree *parent; // TODO: should NOT convert to unique_ptr. We need weak_ptr here.
        
        // It is important to always allocate RBTree objects on the heap because we are calling delete
        // in the destructor for the children. Except for the root, every node in the RBTree needs to be
        // allocated on the heap for this to work correctly. The ideal way would be to not use this exception and
        // just allocate the root on the heap as well.
        RBTree(ValueType val, RBTree *l=nullptr, RBTree *r = nullptr, RBTree *p = nullptr) : value(val), parent(p), left(l), right(r) {}
        
        ~RBTree() {
            delete left; // It is safe to pass nullptr to delete, so no need to check for it.
            delete right;
        }
        
        RBTree &insert(ValueType value){
            // Perform binary search.
            // If the node we found already contains this value, we are done.
            // Otherwise add this node as the child of the node we found.
        }
    }; // CS : RBTree

} // NS : vvalgo

#include <iostream>

using namespace std;
using namespace vvalgo;

typedef long long ll;

int main() {
    RBTree<ll> *root = nullptr;
    BST::insert(&root, 1000);
    BST::insert(&root, 500);
    BST::insert(&root, 1500);
    BST::insert(&root, 250);
    BST::insert(&root, 750);
    auto printer = [](decltype(root) node)->bool{
        cout << node->value << " ";
        return false;
    };
    inorderTraverse( root,
                     printer);
    cout << endl;
}
