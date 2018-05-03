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
#include "DstroyMenuLoad.h"

#include "DstroyMenuAdventure.h"
#include "DstroyMenuPause.h"
#include "DstroyGame.h"
#include "DstroyPressFire.h"

DstroyMenuLoad::DstroyMenuLoad(bool bSave)
{
	this->bSave = bSave;
}

DstroyMenuLoad::~DstroyMenuLoad(void)
{
}

bool DstroyMenuLoad::init(void)
{
	if (!DstroyMenu::init())
		return false;

	TGISurface* pSurface = NULL;
	TGISprite sprite;

	pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("fsw.pcx"));
	vecSurface.push_back(pSurface);

	
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	TGIObject* pObject = NULL;
	pObject = new TGIObject;
	pObject->bVisible = true;
	sprite.setPlacement(0, 0, 320, 240);
	pObject->addSprite(sprite);
	pObject->setPos(0, 0);
	addObject(pObject, 0);

	DstroyMenuItem item;
	TGIuint8 i;
	char strText[256];
	strText[0] = 0;

	TGIint nPos = 20;
	DstroyGameParams params;
	for (i=0;i<8;i++)
	{
		if (DstroyGameParams::load(i, params))
		{
			if (i==7)
			{
				sprintf(strText, "AUTO: Lev%d - Dif%d - %d players", 
					params.nLevel, params.nDifficulty, params.nPlayers);
			}
			else
			{
				sprintf(strText, "%d: Lev%d - Dif%d - %d players", 
					i+1, params.nLevel, params.nDifficulty, params.nPlayers);
			}
		}
		else
		{
			if (i==7)
			{
				sprintf(strText, "AUTO: --- ", i+1);
			}
			else
			{
				sprintf(strText, "%d: --- ", i+1);
			}
		}
		writeText(strText, 30, nPos, TAleft, &item);
		item.nId = i+100;
		pManager->vecMenuItem.push_back(item);

		nPos += 20;
	}

	nPos += 20;

	writeText("BACK", 30, nPos, TAleft, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);

	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[8]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[4].pUp = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[5].pUp = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[6].pUp = &(pManager->vecMenuItem[5]);
	pManager->vecMenuItem[7].pUp = &(pManager->vecMenuItem[6]);
	pManager->vecMenuItem[8].pUp = &(pManager->vecMenuItem[7]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[4].pDown = &(pManager->vecMenuItem[5]);
	pManager->vecMenuItem[5].pDown = &(pManager->vecMenuItem[6]);
	pManager->vecMenuItem[6].pDown = &(pManager->vecMenuItem[7]);
	pManager->vecMenuItem[7].pDown = &(pManager->vecMenuItem[8]);
	pManager->vecMenuItem[8].pDown = &(pManager->vecMenuItem[0]);

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);

	return true;
}

void DstroyMenuLoad::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	if (pMessage->lId == 10)
	{
		if (pItem->nId == -1)
		{
			stop();
		} 
		if (pItem->nId >= 100)
		{
			if (!bSave)
			{
				//on load
				if (DstroyGameParams::load(pItem->nId-100, DstroyGame::params))
				{
					stop();
					DstroyPressFire* pMenu = new DstroyPressFire;
					bSave = true;
					//DstroyGame* pGame = new DstroyGame;
				}
			}
			else
			{
				//on save
				if (pItem->nId-100 == 7) //si c'est l'auto save
					return;
				DstroyGame::params.save(pItem->nId-100);
				stop();
			}
		}
	}
}

bool DstroyMenuLoad::exit(void)
{
	if (!bSave)
		DstroyMenuAdventure* pMenu = new DstroyMenuAdventure;

	return DstroyMenu::exit();
}
