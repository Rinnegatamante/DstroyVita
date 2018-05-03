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
#include "TGISurface.h"
#include "TGIObject.h"
#include "TGIRect.h"

/* TGIScreen

	sub part of the screen
	used only by the TGIMain

	you should use the TGIMain::addScreen to add screens

*/

class TGIScreen
{
	
public:
	TGIScreen(void);
	~TGIScreen(void);

	//object on which the current screen is centered (can be NULL)
	TGIObject* pCenterObject;
	//limits of the position on the screen (no use if pObjectCenter is NULL)
	TGIRect rectLimit;

	//rect from which to take objects
	TGIRect rectSrc;
	//rect where to draw objects;
	TGIRect rectDest;
	

	//position in the game
	TGIint x0,y0;
public:
	//called by the draw thread of TGIMain
	void drawScreen(void* pData);

	/*TODO

	init function

	*/
};
