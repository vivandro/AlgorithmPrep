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

#include "power.h"

using namespace std;

int main ()
{
	cout << "pow 5, 0 == " << vvalgo::power(5, 0) << endl;
	cout << "pow 5, 1 == " << vvalgo::power(5, 1) << endl;
	cout << "pow 5, 2 == " << vvalgo::power(5, 2) << endl;
	cout << "pow 5, 3 == " << vvalgo::power(5, 3) << endl;
	cout << "pow 5, 4 == " << vvalgo::power(5, 4) << endl;
	cout << "pow 5, 5 == " << vvalgo::power(5, 5) << endl;
	cout << "pow 5, -1 == " << vvalgo::power(5.0, -1) << endl;
	cout << "pow 5, -2 == " << vvalgo::power(5.0, -2) << endl;
	cout << "pow 5, -3 == " << vvalgo::power(5.0, -3) << endl;
	cout << "pow 5, -4 == " << vvalgo::power(5.0, -4) << endl;
	cout << "pow 5, -5 == " << vvalgo::power(5.0, -5) << endl;
}

