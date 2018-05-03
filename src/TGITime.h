/*
 * Dstroy, a remake of the bomberman-like DOS game from Fully Bugged Software
 * Copyright (C) Michael Doguet
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#pragma once

#include "TGIGlobals.h"

/* TGITime

	time class to be system independent
	uses the Ticks of the system (could be a problem?)

*/

class TGITime
{
	TGIlong lTicks;
public:
	TGITime(void);
public:
	~TGITime(void);
	void setTime(TGIlong ll);

	static TGITime getCurrentTime();

	//add time (in system dependent unit)
	void operator +=(TGIint n);

	//compare functions
	bool operator ==(const TGITime& from);
	bool operator <(const TGITime& from);
	bool operator >(const TGITime& from);
	bool operator <=(const TGITime& from);
	bool operator >=(const TGITime& from);

	/*TODO
	operator + - -= with TGIint
	*/

};
