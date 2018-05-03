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
#include "TGISprite.h"

TGISprite::TGISprite(TGISurface* pTGISurface, TGIint x, TGIint y)
{
	this->pTGISurface = pTGISurface;
	this->x = x;
	this->y = y;
	 
}
TGISprite::TGISprite()
{
	pTGISurface = NULL;
	x = 0;
	y = 0;
	w = h = 0;
}

TGISprite::TGISprite(const TGISprite& from)
{
	copy(from);
}
	
TGISprite& TGISprite::operator =(const TGISprite& from)
{
	return copy(from);
}
	
TGISprite& TGISprite::copy(const TGISprite& from)
{
	this->pTGISurface = from.pTGISurface;
	this->x = from.x;
	this->y = from.y;
	this->w = from.w;
	this->h = from.h;

	return *this;
}

TGISprite::~TGISprite(void)
{
	pTGISurface = NULL;

}


void TGISprite::setSurface(TGISurface* pTGISurface)
{
	this->pTGISurface = pTGISurface;
}

void TGISprite::setPlacement(TGIint x, TGIint y, TGIint w, TGIint h)
{
	if (TGIGlobals::bRotateScreen)
	{
		this->x = (pTGISurface->getWidth() - x - w)*TGIGlobals::nSpriteSize;
		this->y = (pTGISurface->getHeight() - y - h)*TGIGlobals::nSpriteSize;
		this->w = w*TGIGlobals::nSpriteSize;
		this->h = h*TGIGlobals::nSpriteSize;
	}
	else
	{
		this->x = x*TGIGlobals::nSpriteSize;
		this->y = y*TGIGlobals::nSpriteSize;
		this->w = w*TGIGlobals::nSpriteSize;
		this->h = h*TGIGlobals::nSpriteSize;
	}
}

