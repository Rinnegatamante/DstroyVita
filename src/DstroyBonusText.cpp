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
#include "DstroyBonusText.h"

#include "DstroyGame.h"

DstroyBonusText::DstroyBonusText(void)
{
	classId = CLASSID_BONUSTEXT;

	nAnimSpeed = 20;

}

DstroyBonusText::~DstroyBonusText(void)
{
}

bool DstroyBonusText::init(TGIuint16 x, TGIuint16 y, char* strN)
{
	width = 16;
	height = 16;
	this->setPosGrid(x, y);
	//strncpy(strName, strN, 8);

	yStart = this->Y();

	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	pGame->font.writeText(strN, X()+8, Y()+8, TAcenter, 0, &vecObject, false);

	tgWhenToMove = TGITime::getCurrentTime();
	tgWhenToMove += nAnimSpeed;

	return true;
}

void DstroyBonusText::quePasa(void)
{
	TGIuint16 i;
	
	if (TGITime::getCurrentTime() > tgWhenToMove)
	{
		this->setY(Y()-1);
		for (i=0;i<vecObject.size();i++)
		{
			vecObject[i]->setY(vecObject[i]->Y()-1);
		}
		nAnimSpeed += nAnimSpeed/5;

		tgWhenToMove = TGITime::getCurrentTime();
		tgWhenToMove += nAnimSpeed;
	}

	if (yStart - Y() > 10)
	{
		DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;

		for (i=0;i<vecObject.size();i++)
		{
			pGame->deleteObject(vecObject[i]);
		}
		pGame->deleteObject(this);
	}
}
