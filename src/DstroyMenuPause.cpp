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
#include "DstroyMenuPause.h"

#include "DstroyMenuLoad.h"
#include "DstroyGame.h"

DstroyMenuPause::DstroyMenuPause(bool *pbRunning, bool *pbFinishGame)
{
	this->pbRunning = pbRunning;
	this->pbFinishedGame = pbFinishGame;
}

DstroyMenuPause::~DstroyMenuPause(void)
{
}

bool DstroyMenuPause::init(void)
{
	if (!DstroyMenu::init())
		return false;

	TGISurface* pSurface = NULL;
	TGISprite sprite;

	/*pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("fsw.pcx"));
	vecSurface.push_back(pSurface);*/

	
	/*sprite.setSurface(vecSurface[vecSurface.size()-1]);
	TGIObject* pObject = NULL;
	pObject = new TGIObject;
	pObject->bVisible = true;
	sprite.setPlacement(0, 0, 320, 240);
	pObject->addSprite(sprite);
	pObject->setPos(0, 0);
	addObject(pObject, 0);*/

	TGIuint8 x,y;
#ifndef __NDS__
	x = 160;
	y = 80;
#else
	x = 128;
	y = 60;
#endif

	DstroyMenuItem item;
	writeText("RETURN TO THE GAME", x, y, TAcenter, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	if (DstroyGame::params.nMode == GAMEMODE_ADVENTURE)
	{
		writeText("SAVE", x, y+20, TAcenter, &item);
		item.nId = 2;
		pManager->vecMenuItem.push_back(item);
		writeText("SKIP LEVEL", x, y+40, TAcenter, &item);
		item.nId = 3;
		pManager->vecMenuItem.push_back(item);
	}
	writeText("BACK TO MAIN MENU", x, y+60, TAcenter, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);

	if (DstroyGame::params.nMode != GAMEMODE_ADVENTURE)
	{
		pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[1]);
		pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);

		pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
		pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[0]);
	}
	else
	{
		pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[3]);
		pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
		pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
		pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);

		pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
		pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
		pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
		pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[0]);
	}

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);

	return true;
}

void DstroyMenuPause::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	if (pMessage->lId == 10)
	{
		if (pItem->nId == 1)
		{
			stop();
			TGIGlobals::theMain = NULL;
		} 
		if (pItem->nId == 2)
		{
			//sauver une partie
			stop();
			DstroyMenuLoad* pMenu = new DstroyMenuLoad(true);
		}
		if (pItem->nId == 3)
		{
			//skip le niveau
			stop();
			*pbFinishedGame = true;
			TGIGlobals::theMain = NULL;
		}
		if (pItem->nId == -1)
		{
			stop();
			TGIGlobals::stopMusic();
			*pbRunning = false;
			TGIGlobals::theMain = NULL;
		}

	}
}

bool DstroyMenuPause::exit(void)
{
	return DstroyMenu::exit();
}
