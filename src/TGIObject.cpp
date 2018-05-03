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
#include "TGIObject.h"

TGIObject::TGIObject(void)
{
	nCurrentSprite = 0;
	x = y = 0;
	lId = 0;
	bVisible = false;
	bFixedOnScreen = false;
	nAnimSpeed = 0;
	bDoChangeSprite = true;
}

TGIObject::TGIObject(const TGIObject& from)
{
	copy(from);
}

TGIObject::~TGIObject(void)
{
}

bool TGIObject::changeSprite()
{
	//nothing here...
	return true;
}

bool TGIObject::addSprite(const TGISprite& sprite)
{
	vecSprite.push_back(sprite);
	width = sprite.getWidth();
	height = sprite.getHeight();

	return true;
} 



void TGIObject::treatMessage(TGIInputMessage* pMessage)
{
	//nothing here
}

void TGIObject::quePasa(void)
{
}

void TGIObject::copy(const TGIObject& from)
{
	bVisible = from.bVisible;
	height = from.height;
	width = from.width;
	lId = from.lId;
	nCurrentSprite = from.nCurrentSprite;
	x = from.x;
	y = from.y;
	tgWhenToChangeSprite = tgWhenToChangeSprite;
	bFixedOnScreen = from.bFixedOnScreen;
	nAnimSpeed = from.nAnimSpeed;
	bDoChangeSprite = from.bDoChangeSprite;

	vecSprite.clear();
	for (TGIuint16 i=0;i<from.vecSprite.size();i++)
	{
		vecSprite.push_back(from.vecSprite[i]);
	}
}

TGIObject& TGIObject::operator =(const TGIObject& from)
{
	copy(from);
	return *this;
}

void TGIObject::reset(void)
{
	nCurrentSprite = 0;
	x = y = 0;
	height = width = 0;
	lId = 0;
	bVisible = false;
	bFixedOnScreen = false;

	vecSprite.clear();
}

void TGIObject::setCurrentSprite(TGIint nSprite)
{
	nCurrentSprite = nSprite;
	tgWhenToChangeSprite = TGITime::getCurrentTime();
	tgWhenToChangeSprite += nAnimSpeed;
}
