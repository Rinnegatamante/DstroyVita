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
#include "DstroyNest.h"

#include "TGIGlobals.h"
#include "DstroyGame.h"

#define ANIMSPEED 60
#define ANIMSPEED_OUT 50;

DstroyNest::DstroyNest(void)
{
	classId = CLASSID_NEST;
	nAnimSpeed = 0;

	pNestOut = NULL;
	nPeriode = 0;
	nType = NESTTYPE_OUT;
	nLives = 0;
	nMonsterType = 1;
	bShield = false;

}

DstroyNest::~DstroyNest(void)
{
}

bool DstroyNest::changeSprite(void)
{
	TGIint nNew = getCurrentSprite()+1;

	if (nType == NESTTYPE_CREATOR)
	{
		if (nNew == 4)
			nNew = 0;
		if (nNew == 9)
			return true;
		if (nNew == 16)
		{
			bVisible = false;
			return true;
		}
	}
	if (nType == NESTTYPE_OUT && nNew == 9)
		return true;

	setCurrentSprite(nNew);

	return true;
}

void DstroyNest::quePasa(void)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

	if (pGame->bFinishedGame)
		return;

	if (!bVisible)
	{
		pGame->deleteObject(this);
		return;
	}
	if (bShield && tgWhenToEndShield < TGITime::getCurrentTime())
	{
		bShield = false;
	}

	if (nType == NESTTYPE_CREATOR && nMonsterMax > 0)
	{
		if (tgWhenToCreateMonster < TGITime::getCurrentTime())
		{
			tgWhenToCreateMonster = TGITime::getCurrentTime();
			tgWhenToCreateMonster += nPeriode;

			setCurrentSprite(4);
		}

		if (getCurrentSprite() == 8 && pNestOut)
		{
			pNestOut->prepareCreateMonster();
			setCurrentSprite(0);
			nMonsterMax--;
		}
	}
	else
	{
		if (getCurrentSprite() == 8)
		{
			createMonster();
		}
	}
}

void DstroyNest::prepareCreateMonster(void)
{
	if (nType != NESTTYPE_OUT)
		return;

	setCurrentSprite(1);
	nAnimSpeed = ANIMSPEED;
}

void DstroyNest::createMonster(void)
{
	if (nType != NESTTYPE_OUT)
		return;

	setCurrentSprite(0);
	nAnimSpeed = 0;

	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

	DstroyMonster* pMonster;
	if (nMonsterType == 1)
	{
		pMonster = new DstroyMonster(pGame->dsMonsterStandard1);
	}
	else
	{
		pMonster = new DstroyMonster(pGame->dsMonsterStandard2);
	}
	pMonster->bVisible = true;
	pMonster->setPosGrid(gridX(), gridY());
	pMonster->nIA = nIA;
	pMonster->nLife = nMonsterLife;

	pGame->addObject(pMonster,8);
}

void DstroyNest::destroy(void)
{
	if (nType != NESTTYPE_CREATOR)
		return;
	if (nLives == 0)
		return;
	if (bShield)
		return;

	nLives--;
	if (nLives == 0)
	{
		/*setCurrentSprite(9);
		nAnimSpeed = ANIMSPEED;*/
		bVisible = false;
	}
	else
	{
		bShield = true;
		tgWhenToEndShield = TGITime::getCurrentTime();
		tgWhenToEndShield += 1000;
	}
}

bool DstroyNest::initCreator(TGIuint8 nLives, TGIuint16 nPeriode, TGIuint16 nMonsterMax, DstroyNest* pNestOut)
{
	nType = NESTTYPE_CREATOR;
	this->nLives = nLives;
	this->nPeriode = nPeriode;
	this->pNestOut = pNestOut;
	this->nMonsterMax = nMonsterMax;
	setCurrentSprite(0);

	tgWhenToCreateMonster = TGITime::getCurrentTime();
	tgWhenToCreateMonster += nPeriode;

	if (pNestOut == NULL)
		return false;
	nAnimSpeed = ANIMSPEED;

	bVisible = true;

	return true;
}

bool DstroyNest::initOut(TGIuint8 nMonsterType, TGIuint8 nIA, TGIuint8 nMonsterLife)
{
	nType = NESTTYPE_OUT;
	this->nMonsterType = nMonsterType;
	this->nMonsterLife = nMonsterLife;
	this->nIA = nIA;
	setCurrentSprite(0);

	bVisible = true;

	return true;
}

void DstroyNest::copy(const DstroyNest& from)
{
	DstroyItem::copy(from);

	nType = from.nType;
	nLives = from.nLives;
	nPeriode = from.nPeriode;
	pNestOut = from.pNestOut;
	nMonsterType = from.nMonsterType;
}
