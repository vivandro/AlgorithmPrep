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

/*
 * This algorithm gets you the nth fibonnacci number in lgn time!
 * fibo(n) can be found by finding the nth power of the following matrix:
 *   1  1
 *   1  0
 * The answer locations are:
 *   fibo(n+1)     fibo(n)
 *   fibo(n)       fibo(n-1)
 */

class FiboMatrix {
	typedef unsigned long long ull;
	public:
	FiboMatrix operator*(const FiboMatrix &other) const {
		FiboMatrix product = *this;
		product *= other;
		return product;
	}

	FiboMatrix &operator*=(const FiboMatrix &other) {
		ull a = dotProduct(*this, other, 0, 0);
		ull b = dotProduct(*this, other, 0, 1);
		ull c = dotProduct(*this, other, 1, 0);
		ull d = dotProduct(*this, other, 1, 1);
		mat[0][0] = a;
		mat[0][1] = b;
		mat[1][0] = c;
		mat[1][1] = d;
		return *this;
	}

	FiboMatrix(ull a, ull b, ull c, ull d):mat{a, b, c, d} {};
	FiboMatrix() {}
	unsigned long long mat[2][2] = {0};

	private:
	// Assumptions: 2 * 2 matrices.
	//              Order is a * b.
	unsigned long long dotProduct(const FiboMatrix &a, const FiboMatrix &b, int row, int col) const {
		return a.mat[row][0] * b.mat[0][col] + a.mat[row][1] * b.mat[1][col];
	}
};

FiboMatrix power(FiboMatrix fm, unsigned long long p) { // we cannot allow negative powers
	if (p < 2) {
		return fm;
	}

	FiboMatrix rv = power(fm, p/2);
	rv *= rv;

	if (p % 2) {
		rv = rv * fm;
	}

	return rv;
}

unsigned long long fibo(unsigned long long n) {
	if (n < 3) {
		return 1;
	}
	
	FiboMatrix base(1, 1, 1, 0);
	
	FiboMatrix basePowN = power(base, n);
	base = basePowN;
	
	return basePowN.mat[0][1];
}

void printFiboProgression(unsigned long long n) {

	FiboMatrix base(1, 1, 1, 0);

	for (int i = 0; i < n; i++) {
		FiboMatrix basePowN = power(base, i+1);
		printf("\n------------ %d --------------------------\n", i+1);
		printf("\n %llu, %llu,\n %llu, %llu \n", basePowN.mat[0][0], basePowN.mat[0][1], basePowN.mat[1][0], basePowN.mat[1][1]);
		printf("\n--------------------------------------\n");
	}

}

int main() {
	cout << "fibo table" << endl;
	cout << "  1 " << fibo(1) << endl;
	cout << "  2 " << fibo(2) << endl;
	cout << "  3 " << fibo(3) << endl;
	cout << "  4 " << fibo(4) << endl;
	cout << "  5 " << fibo(5) << endl;
	cout << "  6 " << fibo(6) << endl;
	cout << "  7 " << fibo(7) << endl;
	cout << "  8 " << fibo(8) << endl;
	cout << "  9 " << fibo(9) << endl;
	cout << " 10 " << fibo(10) << endl;
	cout << "100 " << fibo(100) << endl;
	cout << "999 " << fibo(999) << " Dont' think it's so close to fibo(100). Seems like overflow." << endl;
}
