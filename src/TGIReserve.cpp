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
#include "TGIReserve.h"

#include "TGIObject.h"

TGIReserve::TGIReserve(void)
{
}

TGIReserve::~TGIReserve(void)
{
	clear();
}

void TGIReserve::clear()
{
	std::list<TGIObject*>::iterator it;

	for (it=listReserve.begin();it!=listReserve.end();it++)
	{
		delete (*it);
	}

	listReserve.clear();
}
	
bool TGIReserve::add(void* pp)
{
	((TGIObject*)pp)->bVisible = false;

	listReserve.push_back((TGIObject*)pp);
	return true;
}
	

bool TGIReserve::get(void** pp)
{
	if (listReserve.empty())
	{
		*pp = NULL;
		return false;
	}

	*pp = *listReserve.begin();
	listReserve.pop_front();

	return true;

}

