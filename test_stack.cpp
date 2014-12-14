
#include <iostream>
#include "stack.h"

int main() {

	vvalgo::Stack<int> st;
	
	st.push(25);
	st.push(100);

	int i = 0;

	st.peek(i);
	st.pop();
	std::cout << i << std::endl;

	st.peek(i);
	st.pop();
	std::cout << i << std::endl;

	if (st.peek(i)) {
		st.pop();
		std::cout << i << std::endl;
	}

	return 0;
}
