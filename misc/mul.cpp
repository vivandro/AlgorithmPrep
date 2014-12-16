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

using namespace std;

// polish peasants multiplication table??
long long mul(long long a, long long b) {
	long long aCopy = a;
	long long bCopy = b;

	long long p = 0;
	int aSign = (a < 0) ? -1 : 1;
	a *= aSign;
	int bSign = (b < 0) ? -1 : 1;
	b *= bSign;

	for (; a; a >>= 1, b <<= 1) {
		if (1 == (a & 1)) {
			p += b;
		}
	}

	p *= (aSign * bSign);

	cout << aCopy << " * " << bCopy << " = " << p << endl;

	return p;
}

int main() {
	mul(0, 23);
	mul(1, 13);
	mul(4, 4);
	mul(25, 25);
	mul(4, 25);
	mul(-25, 25);
	mul(4, -25);

	return 0;
}
