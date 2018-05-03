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

#include "TGISurface.h"

/* TGISprite

	piece of TGISurface, used by objects for animation

*/

class TGISprite
{
friend class TGIScreen;
friend class TGIMain;

	//pointer to the TGISurface
	TGISurface* pTGISurface;
	//position in the TGISurface
	TGIint x;
	TGIint y;
	TGIint w,h;
	
public:
	TGISprite();
	~TGISprite(void);
	TGISprite(TGISurface* pTGISurface, TGIint x, TGIint y);
	TGISprite(const TGISprite& from);
	TGISprite& operator =(const TGISprite& from);
	TGISprite& copy(const TGISprite& from);

	//set surface
	void setSurface(TGISurface* pTGISurface);
	//set position in surface
	void setPlacement(TGIint x, TGIint y, TGIint w, TGIint h);

	//gets
	TGIint getWidth() const { return w/TGIGlobals::nSpriteSize; } 
	TGIint getHeight() const { return h/TGIGlobals::nSpriteSize; }
	TGISurface* getSurface() const { return pTGISurface; }
	
public:
	
};
