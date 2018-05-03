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
#include "TGISurface.h"

#include <SDL_image.h>
#include <string.h>

TGISurface::TGISurface(void)
{
	pSurface = NULL;
	r = b = g = -1;
}

TGISurface::~TGISurface(void)
{
	reset(); 
}

bool TGISurface::reset()
{
	if (pSurface)
	{
		SDL_FreeSurface(pSurface);
		pSurface = NULL;
	}

	return true;
}

bool TGISurface::loadImage(std::string strFileName, bool bSetPalette)
{
	reset();

	SDL_Surface* pTemp;
	TGIuint16 x, y, z;
	TGIuint8 i=0,j=0;
	char strDebug[256];

	pTemp = IMG_Load(strFileName.c_str());
    if (pTemp==NULL)
    {
		sprintf(strDebug, "file %s not found\n", strFileName.c_str());
		TGIGlobals::Trace(strDebug);
        return false;
    }
	sprintf(strDebug, "%s loaded (%dx%d)\n", strFileName.c_str(), pTemp->w, pTemp->h);
	TGIGlobals::Trace(strDebug);

	//put the palette to the screen
	if (bSetPalette)
	{
		SDL_SetPalette(TGIGlobals::pScreen, SDL_LOGPAL|SDL_PHYSPAL, pTemp->format->palette->colors, 0, 256);
	}

	TGIuint8 *pPixels = NULL;
	
	if (TGIGlobals::nSpriteSize > 1)
	{
		TGIGlobals::Trace("nSpriteSize > 1");
		TGIuint8 nSpriteSize = TGIGlobals::nSpriteSize;

		SDL_LockSurface(pTemp);

		pPixels = new TGIuint8[pTemp->w*pTemp->h*pTemp->format->BytesPerPixel*nSpriteSize*nSpriteSize];
		memset(pPixels, 128, pTemp->w*pTemp->h*pTemp->format->BytesPerPixel*nSpriteSize*nSpriteSize);
		
		

		
		for (y=0;y<pTemp->h;y++)
		for (x=0;x<pTemp->w;x++)
		{
			for (z=0;z<pTemp->format->BytesPerPixel;z++)
			{
				for (i=0;i<nSpriteSize;i++)
				for (j=0;j<nSpriteSize;j++)
				{
					pPixels[(x*nSpriteSize+i + (pTemp->w*nSpriteSize)*(y*nSpriteSize+j))*pTemp->format->BytesPerPixel + z] = ((TGIuint8*)(pTemp->pixels))[(x + pTemp->w*y)*pTemp->format->BytesPerPixel + z];
				}
			}
		}	

		SDL_UnlockSurface(pTemp);

		//copie dans une nouvelle surface
		SDL_Surface* pTemp2 = SDL_CreateRGBSurfaceFrom(pPixels, pTemp->w*nSpriteSize, pTemp->h*nSpriteSize,
			pTemp->format->BitsPerPixel, pTemp->pitch*nSpriteSize, 0, 0, 0, 0);

		if (pTemp->format->palette)
			SDL_SetPalette(pTemp2, SDL_LOGPAL|SDL_PHYSPAL, pTemp->format->palette->colors, 0, 256);


		SDL_FreeSurface(pTemp);

		pTemp = pTemp2;
	}
	
	if (TGIGlobals::bRotateScreen)
	{
		TGIGlobals::Trace("bRotateScreen");
		for (z=0;z<pTemp->format->BytesPerPixel;z++)
		{
			for (y=0;y<pTemp->h/2;y++)
			{
				for (x=0;x<pTemp->w;x++)
				{
					i = ((TGIuint8*)(pTemp->pixels))[(x + pTemp->w*y)*pTemp->format->BytesPerPixel + z];
					((TGIuint8*)(pTemp->pixels))[(x + pTemp->w*y)*pTemp->format->BytesPerPixel + z] = ((TGIuint8*)(pTemp->pixels))[(pTemp->w - x - 1 + pTemp->w*(pTemp->h - y - 1))*pTemp->format->BytesPerPixel + z];
					((TGIuint8*)(pTemp->pixels))[(pTemp->w - x - 1 + pTemp->w*(pTemp->h - y - 1))*pTemp->format->BytesPerPixel + z] = i;
				}
			}
		}
	}

	//SDL_SaveBMP(pTemp, "c:\\test.pcx");

	if (r != -1)
	{
		Uint32 key = SDL_MapRGB(pTemp->format, r, g, b);
		SDL_SetColorKey(pTemp, SDL_SRCCOLORKEY, key);
	}

	pSurface = SDL_DisplayFormat(pTemp);
	
	SDL_FreeSurface(pTemp);

	if (pPixels)
	{
		delete [] pPixels;
	}

	return true;
}

void TGISurface::setInvisibleColor(TGIint r, TGIint g, TGIint b)
{
	/*if (pSurface == NULL)
		return;*/

	this->r = r;
	this->g = g;
	this->b = b;

	//Uint32 key = SDL_MapRGB(pSurface->format, r, g, b);
	//SDL_SetColorKey(pSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, key);
}	


bool TGISurface::createPlainSurface(TGIuint16 w, TGIuint16 h, TGIuint8 r, TGIuint8 g, TGIuint8 b)
{
	reset();

	SDL_Surface* pTemp;
	TGIuint8 *pPixels = NULL;
	int i;

	pPixels = new TGIuint8[w*h*3*TGIGlobals::nSpriteSize*TGIGlobals::nSpriteSize];
	for (i=w*h*3*TGIGlobals::nSpriteSize*TGIGlobals::nSpriteSize-3;i>=0;i-=3)
	{
		pPixels[i] = r;
		pPixels[i+1] = g;
		pPixels[i+2] = b;
	}	

	pTemp = SDL_CreateRGBSurfaceFrom(pPixels, w*TGIGlobals::nSpriteSize, h*TGIGlobals::nSpriteSize,
			24, w*3*TGIGlobals::nSpriteSize, 0, 0, 0,0);

	pSurface = SDL_DisplayFormat(pTemp);

	SDL_FreeSurface(pTemp);
	delete [] pPixels;

	return true;
}
