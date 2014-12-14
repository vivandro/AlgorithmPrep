
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
