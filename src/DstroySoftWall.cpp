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
#include "DstroySoftWall.h"

#include "DstroyGame.h"

#define ANIM_SPEED 50
#define ANIM_LAST 5

DstroySoftWall::DstroySoftWall(void)
{
	classId = CLASSID_SOFTWALL;

	bExploded = false;
	pBonus = NULL;
}

DstroySoftWall::~DstroySoftWall(void)
{
	if (pBonus)
	{
		delete pBonus;
	}
}

void DstroySoftWall::quePasa(void)
{
	/*DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);

	if (bExploded)
	{
		setCurrentSprite(getCurrentSprite() + 20);
		nAnimSpeed = 50;
		bExploded = false;
		return;
	}

	if (!bVisible)
	{
		if (pBonus)
		{
			pBonus->bVisible = true;		
			pGame->addObject(pBonus, 5);
		}
		pGame->deleteObject(this);
	}*/
}

bool DstroySoftWall::changeSprite(void)
{
	/*if (bExploded)
	{
		setCurrentSprite(getCurrentSprite() + 20);
		nAnimSpeed = 50;
		bExploded = false;
		return;
	}*/

	if (getCurrentSprite() < 20)
		return true;
	setCurrentSprite(getCurrentSprite() + 20);
	if (getCurrentSprite() >= ANIM_LAST*20)
	{
		DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);

		bVisible = false;
		if (pBonus)
		{
			TGIGlobals::Trace("bonus");
			pBonus->bVisible = true;		
			pGame->addObject(pBonus, 5);
			pBonus = NULL;
		}
		pGame->deleteObject(this);
		return false;
	}

	return true;
}

void DstroySoftWall::setBonus(DstroyGameParams* pParams)
{
	DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);

	if (this->pBonus)
	{
		delete this->pBonus;
		this->pBonus = NULL;
	}
		
	if (rand()%256 > pParams->probaHasBonus)
		return;

	this->pBonus = new DstroyBonus(pGame->dsBonusStandard);

	TGIint nRand, nRand2;
	nRand = rand()%256;
	nRand2 = rand()%pParams->nSubTypeSize;
	
	if (pBonus)
	{
		this->pBonus->setPos(X(), Y());
		this->pBonus->setType(pParams->type[nRand], pParams->subType[nRand2]);
	}
}

void DstroySoftWall::explode(void)
{
	setCurrentSprite(getCurrentSprite() + 20);
	nAnimSpeed = 60;
}
