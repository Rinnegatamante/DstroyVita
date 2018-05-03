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
#include "TGIObject.h"

#define CLASSID_NO 0
#define CLASSID_FLOOR 1
#define CLASSID_WALL 2
#define CLASSID_MONSTER 3
#define CLASSID_PLAYER 4
#define CLASSID_BOMB 5
#define CLASSID_EXPLOSION 6
#define CLASSID_SOFTWALL 7
#define CLASSID_BONUS 8
#define CLASSID_NEST 9
#define CLASSID_TELEPORTING 10
#define CLASSID_BONUSTEXT 11


class DstroyItem : public TGIObject
{
	TGIint grid_x, grid_y;
protected:
	
	
public:
	Direction dirMoving;
	
	DstroyItem(void);
	DstroyItem(const DstroyItem&  from);
	virtual ~DstroyItem(void);

	TGIuint16 classId;
	TGIlong lSpeed;
	void copy(const DstroyItem&  from);
	DstroyItem& operator=(const DstroyItem&  from);

	void setX(TGIint x);
	void setY(TGIint x);
	void setPos(TGIint x, TGIint y);
	void setPosGrid(TGIint x, TGIint y);
	TGIint gridX();
	TGIint gridY();
	bool isPlain(void);
};
