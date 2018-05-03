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
#include "DstroyMenuNetServer.h"

#include "DstroyMenuMain.h"
#include "DstroyPressFire.h"
#include "DstroyGame.h"

DstroyMenuNetServer::DstroyMenuNetServer(void)
{
}

DstroyMenuNetServer::~DstroyMenuNetServer(void)
{
}

bool DstroyMenuNetServer::init(void)
{
	if (!DstroyMenu::init())
		return false;

	DstroyGlobals::server.open(666);

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
	writeText("PLAYERS:", 20, 30, TAleft, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);

	int i,y;
	y = 50;
	for (i=0;i<8;i++)
	{
		writeText("...", 40, y, TAleft, &item);
		item.nId = 100+i;
		pManager->vecMenuItem.push_back(item);
		vecClientItem.push_back(pManager->vecMenuItem.size()-1);
		y += 15;
	}

	writeText("PLAY", 20, y + 20, TAleft, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);
	

	/*writeText("MODE: NORMAL", 150, 100, TAleft, &item);
	item.nId = 2;
	pManager->vecMenuItem.push_back(item);
	writeText("VICTORIES: 5", 150, 120, TAleft, &item);
	item.nId = 4;
	pManager->vecMenuItem.push_back(item);
	writeText("PLAY", 150, 140, TAleft, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);
	writeText("BACK", 150, 180, TAleft, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);*/

	/*pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[4].pUp = &(pManager->vecMenuItem[2]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[4].pDown = &(pManager->vecMenuItem[0]);

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);*/

	//nMode = GAMEMODE_FIGHT;
	DstroyGame::params.nWins = 5;

	return true;
}

void DstroyMenuNetServer::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	if (pMessage->lId == 10)
	{
		if (pItem->nId == -1)
		{ 
			stop();

			DstroyMenuMain* pMenu = new DstroyMenuMain;
		}
		if (pItem->nId == 3)
		{
			stop();
			DstroyPressFire* pMenu = new DstroyPressFire;
			
		}
		if (pItem->nId == 1)
		{
		
		}
		if (pItem->nId == 2)
		{
			
		}
		if (pItem->nId == 4)
		{
			eraseText(pItem);
			switch (DstroyGame::params.nWins)
			{
			case 1:
				DstroyGame::params.nWins = 3;
				writeText("VICTORIES: 3", 150, 120, TAleft, pItem);
				break;
			case 3:
				DstroyGame::params.nWins = 5;
				writeText("VICTORIES: 5", 150, 120, TAleft, pItem);
				break;
			case 5:
				DstroyGame::params.nWins = 10;
				writeText("VICTORIES: 10", 150, 120, TAleft, pItem);
				break;
			case 10:
				DstroyGame::params.nWins = 1;
				writeText("VICTORIES: 1", 150, 120, TAleft, pItem);
				break;
			}
		}
	}
	if (pMessage->lId == left)
	{
		
	}
	if (pMessage->lId == right)
	{
		
	}
}

bool DstroyMenuNetServer::exit(void)
{
	if (TGIGlobals::theMain == this)
	{
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}

	return DstroyMenu::exit();
}

bool DstroyMenuNetServer::events(void)
{
	if (DstroyGlobals::server.receivePacketWaitingConnect())
	{
		redrawClients();
	}

	return DstroyMenu::events();
}

void DstroyMenuNetServer::redrawClients()
{
	int y;
	unsigned int i;
	DstroyMenuItem* pItem;

	y = 50;

	for (i=0;i<vecClientItem.size();i++)
	{
		pItem = &(pManager->vecMenuItem[vecClientItem[i]]);

		eraseText(pItem);
		if (i < DstroyGlobals::server.vecClientName.size())
		{
			writeText(DstroyGlobals::server.vecClientName[i], 40, y, TAleft, pItem); 
		}
		else
		{
			writeText("...", 40, y, TAleft, pItem); 
		}
		y += 15;
	}
}