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

/* TGISurface

	very system dependent
	data of an image.

*/

class TGISurface
{
friend class TGIScreen;
friend class TGIMain;

	//SDL related
	SDL_Surface* pSurface;
	int r,g,b;
public:
	TGISurface(void);
	virtual ~TGISurface(void);

	//load an image (a BMP...)
	virtual bool loadImage(std::string strFileName, bool bSetPalette=false);
	//delete surface
	virtual bool reset();
	//set the invisble color (a bit system dependent - color depth...)
	void setInvisibleColor(TGIint r, TGIint g, TGIint b);
public:

	inline TGIuint16 getWidth(void)
	{
		return pSurface->w;
	}

	inline TGIuint16 getHeight(void)
	{
		return pSurface->h;
	}
	bool createPlainSurface(TGIuint16 w, TGIuint16 h, TGIuint8 r, TGIuint8 g, TGIuint8 b);
};
