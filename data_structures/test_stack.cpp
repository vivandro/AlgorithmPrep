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
