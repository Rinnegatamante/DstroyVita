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
#include "DstroyMenuFight.h"

#include "DstroyMenuMain.h"
#include "DstroyPressFire.h"
#include "DstroyGame.h"

DstroyMenuFight::DstroyMenuFight(void)
{
	nJoueurs = 2;
#ifdef DESKTOP
	nMaxJoueurs = 4;
#endif
#ifdef GP2X
	nMaxJoueurs = 2;
#endif
}

DstroyMenuFight::~DstroyMenuFight(void)
{
}

bool DstroyMenuFight::init(void)
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
	writeText("PLAYERS: 2", 150, 80, TAleft, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	writeText("MODE: NORMAL", 150, 100, TAleft, &item);
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
	pManager->vecMenuItem.push_back(item);

	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[4]);
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
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);

	nMode = GAMEMODE_FIGHT;
	DstroyGame::params.nWins = 5;

	return true;
}

void DstroyMenuFight::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
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
			//DstroyMenuGame* pGame = new DstroyMenuGame;
			
			DstroyGame::params.nPlayers = nJoueurs;
			DstroyGame::params.setMode(nMode);
			for (TGIint i=0;i<4;i++)
			{
				DstroyGame::params.pnWins[i] = 0;
				DstroyGame::params.pnSwap[i] = i;
				DstroyGame::params.pnLives[i] = 1;
			}
			//pGame->setParams(params);
		}
		if (pItem->nId == 1)
		{
			nJoueurs = (nJoueurs+1)%nMaxJoueurs;
			if (nJoueurs == 0)
				nJoueurs = 4;
			if (nJoueurs == 1)
				nJoueurs = 2;
			eraseText(pItem);

			char strText[256];
			sprintf(strText, "PLAYERS: %d", nJoueurs);
			writeText(strText, 150, 80, TAleft, pItem);
		}
		if (pItem->nId == 2)
		{
			if (nMode == GAMEMODE_FIGHT)
			{
				nMode = GAMEMODE_KILLER;
				eraseText(pItem);

				writeText("MODE: KILLER", 150, 100, TAleft, pItem);
			}
			else
			{
				nMode = GAMEMODE_FIGHT;
				eraseText(pItem);

				writeText("MODE: NORMAL", 150, 100, TAleft, pItem);
			}
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
		if (pItem->nId == 1 && nJoueurs > 2)
		{
			nJoueurs--;
			eraseText(pItem);

			char strText[256];
			sprintf(strText, "PLAYERS: %d", nJoueurs);
			writeText(strText, 150, 80, TAleft, pItem);
		}
	}
	if (pMessage->lId == right)
	{
		if (pItem->nId == 1 && nJoueurs < nMaxJoueurs)
		{
			nJoueurs++;
			eraseText(pItem);

			char strText[256];
			sprintf(strText, "PLAYERS: %d", nJoueurs);
			writeText(strText, 150, 80, TAleft, pItem);
		}
	}
}

bool DstroyMenuFight::exit(void)
{
	if (TGIGlobals::theMain == this)
	{
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}

	return DstroyMenu::exit();
}
