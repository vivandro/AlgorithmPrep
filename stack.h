
#include <vector>
#include <exception>

namespace vvalgo {

template <typename T>
class Stack {

public:
bool push(T item) {
	try {
		items.push_back(item);
	} catch (...) {
		return false;
	}
	return true;
}

/*
 * I am attempting to avoid throwing exceptions from the classes that I write. This will force the
 * APIs to be slightly different than the ones seen ni the STL.  We return a bool to indicate whether 
 * we actually performed he operation or not. pop_back() has undefined behavior if the vector is empty.
 */
bool pop() {
	if (!is_empty()) {
		items.erase(items.begin()+items.size()-1);
		return true;
	} else {
		return false;
	}
}

bool peek(T &item) { // Asking for a ref instead of a pointer allows us to skip nullptr checking and thus saves us from related errors/extra code.
	if (!is_empty()) {
		item = items[items.size()-1];
		return true;
	} else {
		return false;
	}
}

bool is_empty() {
	return items.empty();
}

#if 0
// This function is redundant since the return value of push() gives a much more immediate feedback.
bool is_full() {
	/*
	T item; // NOTE: This statement does put an additional restriction on T - that it should have a default constructor.
		// Seems like a very bad idea. Update the logic.
	if (push(item)) {
		pop();
		return false;
	} else {
		return true;
	}
	*/

	return false; 	// We will be right until the system runs out of memory. Beyond that point, the return value of push() will
			// guarantee correctness of behavior. As such, this function is redundant.
}
#endif // 0

private:

std::vector<T> items;

};

}
