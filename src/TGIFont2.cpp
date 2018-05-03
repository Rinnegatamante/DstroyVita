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
#include "TGIFont2.h"

#include "TGIMain.h"

TGIFont2::TGIFont2(void)
{
	pSurface = NULL;
}

TGIFont2::~TGIFont2(void)
{
	if (this->pSurface)
	{
		delete this->pSurface;
		this->pSurface = NULL;
	}
}

bool TGIFont2::setSurface(TGISurface* pSurface)
{
	if (this->pSurface)
	{
		delete this->pSurface;
		this->pSurface = NULL;
	}

	this->pSurface = pSurface;

	return true;
}

bool TGIFont2::importFixedFont(bool bReset, TGIuint16 x, TGIuint16 y, TGIuint16 nWidth, TGIuint16 nHeight, TGIuint16 nCharWidth, TGIuint16 nCharHeight)
{
	if (!pSurface)
		return false;

	TGISprite sprite;
	sprite.setSurface(pSurface);
	
	TGIuint16 i;
	for (i=0;i<256;i++)
	{
		importLetter((unsigned char)i, bReset, i%(nWidth/nCharWidth)*nCharWidth+x, i/(nWidth/nCharWidth)*nCharHeight+y, nCharWidth, nCharHeight);
	}

	return true;
}

bool TGIFont2::importLetter(unsigned char cLetter, bool bReset, TGIuint16 x, TGIuint16 y, TGIuint16 nCharWidth, TGIuint16 nCharHeight)
{
	if (!pSurface)
		return false;

	if (bReset)
		asciiTable[cLetter].reset();

	TGISprite sprite;
	sprite.setSurface(pSurface);

	sprite.setPlacement(x, y, nCharWidth, nCharHeight);
	asciiTable[cLetter].addSprite(sprite);

	return true;
}

bool TGIFont2::writeText(std::string cstrText , TGIint x, TGIint y, TextAlign align, TGIuint16 nSprite, std::vector<TGIObject*>* pvecObject, bool bFixedOnScreen)
{
	if (pSurface == NULL)
		return false;

	if (pvecObject)
		pvecObject->clear();

	TGIObject* pObject = NULL;

	TGIuint16 i;
	TGIuint16 nTextLen = 0;
	for (i=0;i<cstrText.length();i++)
	{
		nTextLen += asciiTable[cstrText[i]].width;
	}

	switch(align)
	{
	case TAcenter:
		x -= nTextLen/2;
		break;
	case TAright:
		x -= nTextLen;
		break;
	default:
		break;
	}
	
	for (i=0;i<cstrText.length();i++)
	{
		pObject = new TGIObject(asciiTable[cstrText[i]]);
		pObject->bVisible = true;
		pObject->bFixedOnScreen = bFixedOnScreen;
		pObject->setCurrentSprite(nSprite);

		if (pObject->getSpriteCount() > 0)
		{
			pObject->setPos(x, y);
			x += asciiTable[cstrText[i]].width;
			
			if (pvecObject)
				pvecObject->push_back(pObject);
			TGIGlobals::theMain->addObject(pObject, 250);
		}
	}

	return true;
}