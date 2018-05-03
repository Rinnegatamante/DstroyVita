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
#include "DstroyMonster.h"

#include "DstroyGame.h"

//private data for the player
#define ANIM_SIZE 9
#define ANIM_LEFT 18
#define ANIM_RIGHT 27
#define ANIM_UP 9
#define ANIM_DOWN 0
#define ANIM_DIE 36
#define ANIM_WIN 45

#define ANIM_SPEED 50;

DstroyMonster::DstroyMonster(void)
{
	classId = CLASSID_MONSTER;
	setCurrentSprite(ANIM_DOWN);

	lSpeed = 1;
	bAlive = true;
	bWinner = false;

	bFreeze = false;
	bSpeed = false;
	bShield = false;

	nIA = 0;
	nLife = 1;

	nAnimSpeed = 50;
}

DstroyMonster::~DstroyMonster(void)
{
}

bool DstroyMonster::changeSprite()
{
	int nStart, nNew;

	if (!bAlive && getCurrentSprite() == ANIM_WIN-1)
	{
		bVisible = false;
	}

	if (bFreeze)
		return true;
		

	switch (dirMoving)
	{
	case left:
		nStart = ANIM_LEFT;
		//x-=lSpeed;
		break;
	case right:
		nStart = ANIM_RIGHT;
		//x+=lSpeed;
		break;
	case up:
		nStart = ANIM_UP;
		//y-=lSpeed;
		break;
	case down:
		nStart = ANIM_DOWN;
		//y+=lSpeed;
		break;
	default: //stand
		if (bAlive)
		{
			if (bWinner)
			{
				nStart = ANIM_WIN;
				nAnimSpeed = 100;
			}
			else
			{
				nStart = ANIM_DOWN;
				setCurrentSprite(nStart);
			//	tgWhenToChangeSprite = TGITime::getCurrentTime();
			//	tgWhenToChangeSprite += ANIM_SPEED;
				return true;
			}
		}
		else
		{
			nStart = ANIM_DIE;
		}
		break;
	}	
	nNew = (getCurrentSprite() + 1)%ANIM_SIZE + nStart;

	setCurrentSprite(nNew);

	return true;

	//tgWhenToChangeSprite = TGITime::getCurrentTime();
	//tgWhenToChangeSprite += ANIM_SPEED;
}
void DstroyMonster::quePasa(void)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;

	if (!bVisible && !bAlive)
	{
		pGame->deleteObject(this);
		return;
	}

	if (!bAlive || bWinner)
		return;

	if (tgEndBonus < TGITime::getCurrentTime())
	{
		bFreeze = false;
		bSpeed = false;
	}
	if (bShield)
	{
		if (tgEndShield < TGITime::getCurrentTime())
		{
			bShield = false;
			bVisible = true;
		}
		else
		{
			bVisible = !bVisible;
		}
	}

	pGame->getObjectsOnPos(this, gridX(), gridY(), listObject);
	//for (TGIuint16 i=0;i<vecObject.size();i++)
	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		//test de mort
		if ((*itObject)->classId == CLASSID_EXPLOSION && !bShield)
		{
			nLife--;
			if (nLife == 0)
			{
				dirMoving = stand;
				bAlive = false;
				bFreeze = false;
				bSpeed = false;
				setCurrentSprite(ANIM_DIE);
				return;
			}
			else
			{
				bShield = true;
				tgEndShield = TGITime::getCurrentTime();
				tgEndShield += 1000;
			}
		}
	}

	TGIint tSpeed = lSpeed;
	if (bSpeed)
	{
		tSpeed = lSpeed*2;
		if (X()%2) setX(X()-1);
		if (Y()%2) setY(Y()-1);
	}
	if (bFreeze)
		tSpeed = 0;

	switch(dirMoving)
	{
	case left:
		setX(X()-tSpeed);
		break;
	case right:
		setX(X()+tSpeed);
		break;
	case up:
		setY(Y()-tSpeed);
		break;
	case down:
		setY(Y()+tSpeed);
		break;
	default: //stand
		break;
	}
}

void DstroyMonster::win(void)
{
	bWinner = true;
	nAnimSpeed = 100;
	dirMoving = stand;
}

void DstroyMonster::go(Direction dir)
{
	if (!bWinner && bAlive)
		dirMoving = dir;
}
