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
#include "DstroyTeleporting.h"

#include "TGIMain.h"

#define ANIM_SPEED 50

DstroyTeleporting::DstroyTeleporting(void)
{
	classId = CLASSID_TELEPORTING;
	pNextToAppear = NULL;

	nAnimSpeed = 50;
}

DstroyTeleporting::~DstroyTeleporting(void)
{
}

bool DstroyTeleporting::changeSprite(void)
{
	setCurrentSprite(getCurrentSprite()+1);

//	tgWhenToChangeSprite = TGITime::getCurrentTime();
//	tgWhenToChangeSprite += ANIM_SPEED;

	return true;
}

void DstroyTeleporting::quePasa(void)
{
	if ((getCurrentSprite() >= 8 && pNextToAppear) || (getCurrentSprite() >=17) )
	{
		//this is the end
		if (pNextToAppear)
		{
			//au cas ou ms deja fait normalement
			pNextToAppear->setPosGrid(this->gridX(), this->gridY());
			
			pNextToAppear->bVisible = true;
		}

		TGIGlobals::theMain->deleteObject(this);
		return;
	}
}

void DstroyTeleporting::init(DstroyPlayer* pNext)
{
	bVisible = true;
	pNextToAppear = pNext;
	if (pNext)
	{
		setCurrentSprite(0);
	}
	else
	{
		setCurrentSprite(9);
	}
}
