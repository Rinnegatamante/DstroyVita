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
#include "DstroyMenuOptions.h"

#include "DstroyGlobals.h"

#include "DstroyMenuMain.h"
#include "DstroyMenuCommandConfig.h"
#include "DstroyMenuGP2XCommands.h"

#include "PadTest.h"

DstroyMenuOptions::DstroyMenuOptions(void)
{
}

DstroyMenuOptions::~DstroyMenuOptions(void)
{
}

bool DstroyMenuOptions::init(void)
{
	if (!DstroyMenu::init())
		return false; 

	options.load();

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

	TGIuint8 x,y;


	DstroyMenuItem item;
#ifdef DESKTOP
	writeText("PLAYER 1 COMMANDS", 160, 40, TAcenter, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	writeText("PLAYER 2 COMMANDS", 160, 60, TAcenter, &item);
	item.nId = 2;
	pManager->vecMenuItem.push_back(item);
	writeText("PLAYER 3 COMMANDS", 160, 80, TAcenter, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);
	writeText("PLAYER 4 COMMANDS", 160, 100, TAcenter, &item);
	item.nId = 4;
	pManager->vecMenuItem.push_back(item);
	if (options.bFullScreen)
	{
		writeText("FULLSCREEN: ON", 160, 120, TAcenter, &item);
	}
	else
	{
		writeText("FULLSCREEN: OFF", 160, 120, TAcenter, &item);
	}
	item.nId = 5;
	pManager->vecMenuItem.push_back(item);
	if (options.bDoubleSize)
	{
		writeText("DOUBLE SIZE: ON", 160, 140, TAcenter, &item);
	}
	else
	{
		writeText("DOUBLE SIZE: OFF", 160, 140, TAcenter, &item);
	}
	item.nId = 6;
	pManager->vecMenuItem.push_back(item);
#endif
#ifdef GP2X
	writeText("CONTROLS MODE", 160, 100, TAcenter, &item);
	item.nId = 102;
	pManager->vecMenuItem.push_back(item);
	writeText("TEST CONTROLS", 160, 120, TAcenter, &item);
	item.nId = 103;
	pManager->vecMenuItem.push_back(item);
	if (options.bRotateScreen)
	{
		writeText("ROTATE SCREEN: ON", 160, 140, TAcenter, &item);
	}
	else
	{
		writeText("ROTATE SCREEN: OFF", 160, 140, TAcenter, &item);
	}
	item.nId = 101;
	pManager->vecMenuItem.push_back(item);
#endif
#ifndef __NDS__
	x = 160;
	y = 160;
#else
	x = 128;
	y = 30;
#endif
	if (options.bOptionsText)
	{
		writeText("BONUS TEXT DESCRIPTION: ON", x, y, TAcenter, &item);
	}
	else
	{
		writeText("BONUS TEXT DESCRIPTION: OFF", x, y, TAcenter, &item);
	}
	item.nId = 7;
	pManager->vecMenuItem.push_back(item);

	writeText("BACK", x, y+40, TAcenter, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);

	TGIuint8 i;
	for (i=0;i<pManager->vecMenuItem.size();i++)
	{
		if (i==0)
		{
			pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[pManager->vecMenuItem.size()-1]);
		}
		else
		{
			pManager->vecMenuItem[i].pUp = &(pManager->vecMenuItem[i-1]);
		}
		pManager->vecMenuItem[i].pDown = &(pManager->vecMenuItem[(i+1)%pManager->vecMenuItem.size()]);
	}

/*	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[6]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[4].pUp = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[5].pUp = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[6].pUp = &(pManager->vecMenuItem[5]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[4].pDown = &(pManager->vecMenuItem[5]);
	pManager->vecMenuItem[5].pDown = &(pManager->vecMenuItem[6]);
	pManager->vecMenuItem[6].pDown = &(pManager->vecMenuItem[0]);*/

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);

	return true;
}

void DstroyMenuOptions::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	if (pMessage->lId == 10)
	{
		if (pItem->nId >= 1 && pItem->nId <= 4)
		{
			stop();
			DstroyMenuCommandConfig* pMenu = new DstroyMenuCommandConfig(pItem->nId);
		}
		if (pItem->nId == -1)
		{
			//quit
			stop();
			DstroyMenuMain* pMenu = new DstroyMenuMain;
			
		}
		if (pItem->nId == 5)
		{
			options.bFullScreen = !options.bFullScreen;

			eraseText(pItem);

			if (options.bFullScreen)
			{
				writeText("FULLSCREEN: ON", 160, 120, TAcenter, pItem);
			}
			else
			{
				writeText("FULLSCREEN: OFF", 160, 120, TAcenter, pItem);
			}

			options.save();
		}
		if (pItem->nId == 6)
		{
			options.bDoubleSize = !options.bDoubleSize;
			options.save();

			eraseText(pItem);
			if (options.bDoubleSize)
			{
				writeText("DOUBLE SIZE: ON", 160, 140, TAcenter, pItem);
			}
			else
			{
				writeText("DOUBLE SIZE: OFF", 160, 140, TAcenter, pItem);
			}
		}
		if (pItem->nId == 7)
		{
			options.bOptionsText = !options.bOptionsText;

			eraseText(pItem);
			TGIuint8 x,y;
#ifndef __NDS__
			x = 160;
			y = 160;
#else
			x = 128;
			y = 30;
#endif
			if (options.bOptionsText)
			{
				writeText("BONUS TEXT DESCRIPTION: ON", x, y, TAcenter, pItem);
			}
			else
			{
				writeText("BONUS TEXT DESCRIPTION: OFF", x, y, TAcenter, pItem);
			}

			options.save();
		}
		if (pItem->nId == 101)
		{
			options.bRotateScreen = !options.bRotateScreen;
			options.save();
			TGIGlobals::bRotateScreen = options.bRotateScreen;

			stop();
			DstroyMenuOptions* pMenu = new DstroyMenuOptions;

			/*eraseText(pItem);
			if (options.bRotateScreen)
			{
				writeText("ROTATE SCREEN: ON", 160, 160, TAcenter, pItem);
			}
			else
			{
				writeText("ROTATE SCREEN: OFF", 160, 160, TAcenter, pItem);
			}*/

			
		}
		if (pItem->nId == 102)
		{
			stop();
			DstroyMenuGP2XCommands* pMenu = new DstroyMenuGP2XCommands;
		}
		if (pItem->nId == 103)
		{
			stop();
			PadTest* pMenu = new PadTest;
		}
	}
}