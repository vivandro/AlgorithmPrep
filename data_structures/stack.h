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

bool peek(T &item) const { // Asking for a ref instead of a pointer allows us to skip nullptr checking and thus saves us from related errors/extra code.
	if (!is_empty()) {
		item = (items[items.size()-1]);
		return true;
	} else {
		return false;
	}
}

bool is_empty() const {
	return items.empty();
}

private:

std::vector<T> items; // Backing store.

};

}
