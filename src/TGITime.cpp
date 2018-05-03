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
#include "stdafx.h"
#include "TGITime.h"

#include "TGIGlobals.h"

TGITime::TGITime(void)
{
	lTicks = SDL_GetTicks();
}

TGITime::~TGITime(void) 
{
}


 TGITime TGITime::getCurrentTime()
 {
	TGITime tgTime;
	return tgTime;
 }

 void TGITime::setTime(TGIlong ll)
 {
	lTicks = ll;
 }

bool TGITime::operator ==(const TGITime& from)
{
	return lTicks == from.lTicks;
}

bool TGITime::operator <(const TGITime& from)
{
	return lTicks < from.lTicks;
}

bool TGITime::operator >(const TGITime& from)
{
	return lTicks > from.lTicks;
}

bool TGITime::operator <=(const TGITime& from)
{
	return lTicks <= from.lTicks;
}

bool TGITime::operator >=(const TGITime& from)
{
	return lTicks >= from.lTicks;
}

void TGITime::operator +=(TGIint n)
{
	lTicks += n;
}

