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
#include "DstroyBonus.h"
#include "stdafx.h"

#include "DstroyGame.h"
#include "DstroyBonusText.h"

#include <string.h>

#define ANIM_ALIVE 8
#define ANIM_DESTROY 8

#define ANIM_SPEED 100

DstroyBonus::DstroyBonus(void)
{
	classId = CLASSID_BONUS;
	bDestroyed = false;

	setType(0);

	nAnimSpeed = 100;
}

DstroyBonus::~DstroyBonus(void)
{
}

bool DstroyBonus::changeSprite(void)
{
	setCurrentSprite((getCurrentSprite()+1)%8 + nType);
	if (bDestroyed)
		setCurrentSprite(getCurrentSprite() + ANIM_ALIVE);
	if (getCurrentSprite() - nType >= 15)
	{
		bVisible = false;
	}

	return true;
	//tgWhenToChangeSprite = TGITime::getCurrentTime();
	//tgWhenToChangeSprite += ANIM_SPEED;
}

void DstroyBonus::setType(TGIint nType, TGIint nSubType)
{
	strncpy(strName, "No", 3);
	this->nType = nType;
	setCurrentSprite(nType);

	this->nSubType = nSubType;
	switch (nSubType)
	{
	case  BONUSS_CHANGE:
		strncpy(strName, "Ch", 3);
		break;
	case  BONUSS_CONTROL:
		strncpy(strName, "Co", 3);
		break;
	case  BONUSS_CROSS:
		strncpy(strName, "Cr", 3);
		break;
	case  BONUSS_CROSSFIRE:
		strncpy(strName, "CF", 3);
		break;
	case  BONUSS_DROPBOMB:
		strncpy(strName, "DB", 3);
		break;
	case  BONUSS_FASTBOMB:
		strncpy(strName, "FB", 3);
		break;
	case  BONUSS_FREEZE:
		strncpy(strName, "Fr", 3);
		break;
	case  BONUSS_MONSTERFREEZE:
		strncpy(strName, "MF", 3);
		break;
	case  BONUSS_MONSTERSPEED:
		strncpy(strName, "MS", 3);
		break;
	case  BONUSS_REMOTE:
		strncpy(strName, "Re", 3);
		break;
	case  BONUSS_REVERSE :
		strncpy(strName, "Rv", 3);
		break;
	case  BONUSS_SHADOW:
		strncpy(strName, "Sa", 3);
		break;
	case  BONUSS_SHIELD:
		strncpy(strName, "Sh", 3);
		break;
	case  BONUSS_SLOW:
		strncpy(strName, "Sl", 3);
		break;
	case  BONUSS_SLOWBOMB:
		strncpy(strName, "SB", 3);
		break;
	case  BONUSS_EXPLOSION:
		strncpy(strName, "Xl", 3);
		break;
	case  BONUSS_LOOSER:
		strncpy(strName, "Lo", 3);
		break;
	case  BONUSS_NEXTLEVEL:
		strncpy(strName, "NL", 3);
		break;
	case  BONUSS_MONSTER:
		strncpy(strName, "Mo", 3);
		break;
	case  BONUSS_SWAP:
		strncpy(strName, "Sw", 3);
		break;
	case  BONUSS_TRANSFERT:
		strncpy(strName, "Tr", 3);
		break;
	case  BONUSS_REVERSEPLAYER:
		strncpy(strName, "RP", 3);
		break;
	default:
		strncpy(strName, "No", 3);
	}
}

void DstroyBonus::quePasa(void)
{
	if (bDestroyed && !bVisible)
	{
		TGIGlobals::theMain->deleteObject(this);
	}
}

void DstroyBonus::take(void)
{
	bDestroyed = true;
 
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

	switch (nType)
	{
	case BONUS_LIFE:
		pGame->soundXtraLife.play();
		break;
	case BONUS_BOMB:
		pGame->soundBomb.play();
		break;
	case BONUS_FLAME:
		pGame->soundFlame.play();
		break;
	default:
		if (nSubType != -1)
		{
			pGame->subTypeSound[nSubType]->play();
			
			if (pGame->options.bOptionsText)
			{
				DstroyBonusText* pObject = new DstroyBonusText;
				pObject->init(this->gridX(), this->gridY(), strName);
				pGame->addObject(pObject, 25);
				pObject = NULL;
			}
		}
		break;
	}

	nAnimSpeed = 50;
}

void DstroyBonus::chooseSpecial(void)
{
}
