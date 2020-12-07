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
#include "DstroyMenuMain.h"

#include "DstroyGame.h"
#include "DstroyMenuAdventure.h"
#include "DstroyMenuFight.h"
#include "DstroyMenuOptions.h"

#include <vitasdk.h>

DstroyMenuMain::DstroyMenuMain(void)
{
}

DstroyMenuMain::~DstroyMenuMain(void)
{
}

bool DstroyMenuMain::init(void)
{



	if (!DstroyMenu::init())
		return false; 

	TGISurface* pSurface = NULL;
	TGISprite sprite;

	pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("fsw.pcx"), true);
	vecSurface.push_back(pSurface);

	if (!isMusicPlaying())
	{
		TGIGlobals::playMusic(DstroyGlobals::addResText("mainmenu.mod"), -1, 3);
	}

	
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	TGIObject* pObject = NULL;
	pObject = new TGIObject;
	pObject->bVisible = true;
	sprite.setPlacement(0, 0, 320, 240);
	pObject->addSprite(sprite);
	pObject->setPos(0, 0);
	addObject(pObject, 0);

	DstroyMenuItem item;
	TGIuint8 nXPos, nYPos;
#ifndef __NDS__
	nXPos = 230;
	nYPos = 80;
#else
	nXPos = 183;
	nYPos = 60;
#endif

	
	font.writeText("Dstroy Vita v.1.1", TGIGlobals::screenWidth/2, 5, TAcenter, 1, NULL);

	writeText("ADVENTURE", nXPos, nYPos, TAcenter, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	writeText("FIGHT", nXPos, nYPos+20, TAcenter, &item);
	item.nId = 2;
	pManager->vecMenuItem.push_back(item);
	writeText("OPTIONS", nXPos, nYPos+40, TAcenter, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);
	writeText("EXIT", nXPos, nYPos+60, TAcenter, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);

	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[0]);

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);
	return true;
}

void DstroyMenuMain::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	if (pMessage->lId == 10)
	{
		if (pItem->nId == 1)
		{
			//aventure
			stop();
			
			DstroyMenuAdventure* pMenu = new DstroyMenuAdventure;
		}
		if (pItem->nId == 2)
		{
			//fight
#ifndef __NDS__
			stop();
			
			DstroyMenuFight* pMenu = new DstroyMenuFight;
#endif
		}
		if (pItem->nId == 3)
		{
			//options
			stop();
			
			DstroyMenuOptions* pMenu = new DstroyMenuOptions;
		}
		if (pItem->nId == -1)
		{
#ifndef __NDS__
			//quit
			stop();
			sceKernelExitProcess(0);
#endif
		}
	}
}

bool DstroyMenuMain::exit()
{
	return TGIMain::exit();
}
