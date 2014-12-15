
#include <vector>

namespace vvalgo {

template <typename T>
class Stack {

/* 
 * I am attempting to write exception-blind code. I wouldn't call it exception free because I
 * am not preventing exception propogation (by catch(...) ). I am using this as an experiment to 
 * based on trends observed in Mozilla and Google's C++ style guides. 
 */
public:
void push(const T &item) { // We have no need for modifying the item, and we need not copy it directly here either.
	items.push_back(item);
}

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
		item = (items[items.size()-1]);
		return true;
	} else {
		return false;
	}
}

bool is_empty() {
	return items.empty();
}

private:

std::vector<T> items; // Backing store.

};

}
