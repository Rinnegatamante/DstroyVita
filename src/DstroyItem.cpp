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
#include "DstroyItem.h"

#include "DstroyGame.h"

DstroyItem::DstroyItem(void)
{
	grid_x = X()*width;
	grid_y = Y()*height;
	dirMoving = stand;
	lSpeed = 0;
}

DstroyItem::DstroyItem(const DstroyItem&  from)
{
	copy(from); 
}

DstroyItem::~DstroyItem(void)
{
}

void DstroyItem::copy(const DstroyItem&  from)
{	
	TGIObject::copy(from);

	classId = from.classId;
	dirMoving = from.dirMoving;
	lSpeed = from.lSpeed;
}

DstroyItem& DstroyItem::operator=(const DstroyItem&  from)
{
	copy(from);
	return *this;
}

void DstroyItem::setX(TGIint x)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

	TGIint dif = x + width/2;

	if (dif < 0)
	{
		x = (pGame->nWidth)*width - width/2 - 2;
	}
	else if (dif > pGame->nWidth*width)
	{
		x = -width/2 + 2;
	}

	TGIObject::setX(x);
	grid_x = (x + width/2)/width;
}

void DstroyItem::setY(TGIint x)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

	TGIint dif = x + height/2;

	if (dif < 0)
	{
		x = (pGame->nHeight)*height - height/2 - 2;
	}
	else if (dif > pGame->nHeight*height)
	{
		x = -height/2 + 2;
	}

	TGIObject::setY(x);
	grid_y = (x+height/2)/height;
}

void DstroyItem::setPos(TGIint x, TGIint y)
{
	/*TGIObject::setPos(x, y);
	grid_x = (x+width/2)/width;
	grid_y = (y+height/2)/height;*/
	setX(x);
	setY(y);
}
void DstroyItem::setPosGrid(TGIint x, TGIint y)
{
	/*grid_x = x; 
	grid_y = y;
	TGIObject::*/setPos(x*width, y*height);
}

TGIint DstroyItem::gridX()
{ 
	return grid_x;
}

TGIint DstroyItem::gridY()
{
	return grid_y;
}

bool DstroyItem::isPlain(void)
{
	return (classId == CLASSID_WALL || classId == CLASSID_BOMB || classId == CLASSID_SOFTWALL || classId == CLASSID_NO);
}
