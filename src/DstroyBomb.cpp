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
#include "DstroyBomb.h"
#include "DstroyGame.h"
#include "DstroyPlayer.h"
#include "DstroyNest.h"

#define ANIMSPEED_EXPLODE 50
#define ANIMSPEED 1000

DstroyBomb::DstroyBomb(void)
{
	classId = CLASSID_BOMB;

	nFlames = 0;
	pOwner = NULL;
	bRemote = false;

	bToBeDestroyed = false;
}

DstroyBomb::~DstroyBomb(void)
{
}

bool DstroyBomb::initBomb(DstroyItem* pOwner, int x, int y, int nFlames, int nDurationLeft)
{
	bVisible = true;
	bToBeDestroyed = false;
	this->pOwner = pOwner;
	setPosGrid(x, y);
	this->nFlames = nFlames;

	this->nDurationLeft = nDurationLeft;

	if (nDurationLeft != 0)
	{
		nAnimSpeed = ANIMSPEED;
		setCurrentSprite(5 - nDurationLeft);	
		
	}
	else
	{
		//remote bomb, special sprite
		setCurrentSprite(9);
		bRemote = true;
		nAnimSpeed = 0;
		this->nDurationLeft = 5;
	}

	

	return true;
}

void DstroyBomb::quePasa(void)
{
	DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);

	if (bToBeDestroyed)
	{
		if (tgWhenToDestroy < TGITime::getCurrentTime())
			pGame->deleteObject(this);
		return;
	}

	if (getCurrentSprite() == 8)
		explode();
	if (getCurrentSprite() >= 4)
		nAnimSpeed = ANIMSPEED_EXPLODE;
	/*if (!bRemote)
	{
		nSousDuration++;
		if (nSousDuration >= BOMBSTEP)
		{
			nDurationLeft--;
			nCurrentSprite++;
			nSousDuration = 0;

			if (nDurationLeft <= 0)
			{
				explode();
				return;			
			}
		}
	}*/


}

bool DstroyBomb::changeSprite(void)
{
	if (getCurrentSprite() < 8)
	{
		setCurrentSprite(getCurrentSprite()+1);	
		if (nDurationLeft > 0)
			nDurationLeft--;
	}

	return true;
}

void DstroyBomb::explode(void)
{
	//setCurrentSprite(0);
	if (pOwner)
	{
		if (((DstroyPlayer*)pOwner)->nBombsLeft < ((DstroyPlayer*)pOwner)->nBombs)
				((DstroyPlayer*)pOwner)->nBombsLeft++;
	}
	DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);

	TGIint xe, ye, i;
	
	//center
	createExplosionAndContinue(gridX(),gridY(), 0, stand);

	//horizontal
	ye = gridY();
	xe = gridX();
	//left
	i=1;
	xe -= 1;
	while (createExplosionAndContinue(xe, ye, i, left))
	{
		xe -= 1;
		i++;
	}
	//right
	xe = gridX()+ 1;
	i=1;
	while (createExplosionAndContinue(xe, ye, i, right))
	{
		xe += 1;
		i++;
	}
	//up
	xe = gridX();
	ye -= 1;
	i=1;
	while (createExplosionAndContinue(xe, ye, i, up))
	{
		ye -= 1;
		i++;
	}
	//down
	ye = gridY() + 1;
	i=1;
	while (createExplosionAndContinue(xe, ye, i, down))
	{
		ye += 1;
		i++;
	}
	

	bToBeDestroyed = true;
	tgWhenToDestroy = TGITime::getCurrentTime();
	tgWhenToDestroy += 200;
	//pGame->deleteObject(this); //kill me!
	
	pGame->soundBoom.play();
}

bool DstroyBomb::createExplosionAndContinue(TGIint x, TGIint y, TGIint nFlame, Direction dir)
{
	DstroyGame* pGame = (DstroyGame*)(TGIGlobals::theMain);
	DstroyExplosion* pExplosion = NULL;

	if (nFlame == 1 && dir == left)
	{
		nFlame = 1;
	}

	bool bEnd = false;
	
	//test if something stops the flame
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;
	pGame->getObjectsOnPos(this, x, y, listObject);
	//for (TGIuint16 i=0;i<vecObject.size();i++)
	for (itObject=listObject.begin();itObject!=listObject.end() && !bEnd;itObject++)
	{
		switch ((*itObject)->classId)
		{
			case CLASSID_WALL:
				return false;
			case CLASSID_BOMB:  
			{
				bEnd = true;
				((DstroyBomb*)(*itObject))->makeExplode();
				break;
			}
			case CLASSID_SOFTWALL:
			{
				bEnd = true;
				((DstroySoftWall*)(*itObject))->explode();
				break;
			}
			case CLASSID_BONUS:
			{
				((DstroyBonus*)(*itObject))->bDestroyed = true;
				break;
			}
			case CLASSID_NEST:
			{
				((DstroyNest*)(*itObject))->destroy();
				break;
			}
		}
	}

	if (bEnd)
		return false;

	if (nFlame == nFlames)
	{
		//end of the flame	
		bEnd = true;
	} 

	//pExplosion = new DstroyExplosion(pGame->dsExplosionStandard);
	pExplosion = pGame->createExplosion();
	pExplosion->bVisible = true;

	switch(dir)
	{
	case stand:
		pExplosion->setCurrentSprite(EXPLOSION_ANIM_CENTER);
		break;
	case left:
		if (bEnd)
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_LEFT);
		else
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_HORIZONTAL);
		break;
	case right:
		if (bEnd)
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_RIGHT);
		else
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_HORIZONTAL);
		break;
	case up:
		if (bEnd)
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_TOP);
		else
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_VERTICAL);
		break;
	case down:
		if (bEnd)
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_BOTTOM);
		else
			pExplosion->setCurrentSprite(EXPLOSION_ANIM_VERTICAL);
		break;
	}
	pExplosion->setPosGrid(x, y);
	pGame->addObject(pExplosion, 3);

	return !bEnd;
}

void DstroyBomb::makeExplode(void)
{
	if (bToBeDestroyed)
		return;

	nAnimSpeed = ANIMSPEED_EXPLODE;
	setCurrentSprite(5);
	nDurationLeft = 0;
	bRemote = false;
}


