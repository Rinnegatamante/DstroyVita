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
#include "DstroyMenuAdventure.h"

#include "DstroyMenuMain.h"
#include "DstroyMenuLoad.h"

#include "DstroyGame.h"
#include "DstroyPressFire.h"

DstroyMenuAdventure::DstroyMenuAdventure(void)
{
	nJoueurs = 1;
#ifdef DESKTOP
	nMaxJoueurs = 4;
#endif
#ifdef GP2X
	nMaxJoueurs = 2;
#endif
	nMaxJoueurs = 4;
}

DstroyMenuAdventure::~DstroyMenuAdventure(void)
{
}

bool DstroyMenuAdventure::init(void)
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

	DstroyGame::params.nDifficulty = 1;

	TGIuint8 x,y;
#ifndef __NDS__
	x = 150;
	y = 80;
#else
	x = 130;
	y = 50;
#endif

	DstroyMenuItem item;
	writeText("PLAYERS: 1", x, y, TAleft, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	writeText("LEVEL: NORMAL", x, y+20, TAleft, &item);
	item.nId = 4;
	pManager->vecMenuItem.push_back(item);
	writeText("LOAD", x, y+40, TAleft, &item);
	item.nId = 2;
	pManager->vecMenuItem.push_back(item);
	writeText("PLAY", x, y+60, TAleft, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);
#ifndef __NDS__
	writeText("BACK", x, y+100, TAleft, &item);
	item.nId = -1;
	pManager->vecMenuItem.push_back(item);

	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[4].pUp = &(pManager->vecMenuItem[3]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[4]);
	pManager->vecMenuItem[4].pDown = &(pManager->vecMenuItem[0]);
#else
	pManager->vecMenuItem[0].pUp = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[1].pUp = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pUp = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[3].pUp = &(pManager->vecMenuItem[2]);

	pManager->vecMenuItem[0].pDown = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pDown = &(pManager->vecMenuItem[2]);
	pManager->vecMenuItem[2].pDown = &(pManager->vecMenuItem[3]);
	pManager->vecMenuItem[3].pDown = &(pManager->vecMenuItem[0]);
#endif

	pManager->vecMenuItem[0].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[0]);

	return true;
}

void DstroyMenuAdventure::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
	TGIuint8 x,y;
#ifndef __NDS__
	x = 150;
	y = 80;
#else
	x = 130;
	y = 50;
#endif

	if (pMessage->lId == 10)
	{

		if (pItem->nId == -1)
		{
#ifndef __NDS__
			stop();

			DstroyMenuMain* pMenu = new DstroyMenuMain;
#endif
		} 
		if (pItem->nId == 2)
		{
			//charger une partie
			stop();
			DstroyMenuLoad* pMenu = new DstroyMenuLoad(false);
		}
		if (pItem->nId == 3)
		{
			stop();
			DstroyPressFire* pMenu = new DstroyPressFire;
			//DstroyGame* pGame = new DstroyGame;
			DstroyGame::params.setLevel(1);
			DstroyGame::params.nPlayers = nJoueurs;
			//DstroyGame::params.nDifficulty = 1;
			DstroyGame::params.setMode(GAMEMODE_ADVENTURE);
			TGIint i;
			for (i=0;i<nJoueurs;i++)
			{
				DstroyGame::params.pnLives[i] = 5;
				DstroyGame::params.pnBombDuration[i] = 4;
				DstroyGame::params.pnBombs[i] = 1;
				DstroyGame::params.pnFlame[i] = 1;
			}
		}
		if (pItem->nId == 1)
		{
			nJoueurs = (nJoueurs+1)%nMaxJoueurs;
			if (nJoueurs == 0)
				nJoueurs = nMaxJoueurs;
			eraseText(pItem);


			char strText[256];
			sprintf(strText, "PLAYERS: %d", nJoueurs);
			writeText(strText, x, y, TAleft, pItem);
		}
		if (pItem->nId == 4)
		{
			DstroyGame::params.nDifficulty = (DstroyGame::params.nDifficulty+1)%5;
			if (DstroyGame::params.nDifficulty == 0)
			{
				DstroyGame::params.nDifficulty++;
			}
			eraseText(pItem);
			switch (DstroyGame::params.nDifficulty)
			{
			case 1:
				writeText("LEVEL: NORMAL", x, y+20, TAleft, pItem);
				break;
			case 2:
				writeText("LEVEL: HARD", x, y+20, TAleft, pItem);
				break;
			case 3:
				writeText("LEVEL: VERY HARD", x, y+20, TAleft, pItem);
				break;
			case 4:
				writeText("LEVEL: GOD", x, y+20, TAleft, pItem);
				break;
			}
		}
	}
	if (pMessage->lId == left)
	{
		if (pItem->nId == 1 && nJoueurs > 1)
		{
			nJoueurs--;
			eraseText(pItem);

			char strText[256];
			sprintf(strText, "PLAYERS: %d", nJoueurs);
			writeText(strText, x, y, TAleft, pItem);
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
			writeText(strText, x, y, TAleft, pItem);
		}
	}
}

bool DstroyMenuAdventure::exit(void)
{
	if (TGIGlobals::theMain == this)
	{
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}

	return DstroyMenu::exit();
}
