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

#ifndef APFN_MISC_POWER_H
#define APFN_MISC_POWER_H

namespace vvalgo {

template <typename T, typename V>
T power(T base, V pow) {
	if (0 == pow) {
		return 1;
	}

	bool negativePower = (pow < 0);
	if (negativePower) {
		pow *= -1;
	}
	T rv = power(base, pow/2);
	rv *= rv;
	if (pow %2) {
		rv *= base;
	}

	if (negativePower) {
		rv = 1 / rv;
	}

	return rv;
} // FN : power

} // NS : vvalgo
#endif // APFN_MISC_POWER_H
