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
#include "DstroyItem.h"

class DstroyBonusText :	public DstroyItem
{
	char strName[8];
	TGIuint16 yStart;
	std::vector<TGIObject*> vecObject;
	TGITime tgWhenToMove;
public:
	DstroyBonusText(void);
public:
	~DstroyBonusText(void);
public:
	bool init(TGIuint16 x, TGIuint16 y, char* strN);
public:
	void quePasa(void);
};
