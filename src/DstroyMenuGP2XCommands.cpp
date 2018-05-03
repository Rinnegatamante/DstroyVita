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
#include "DstroyMenuGP2XCommands.h"

#include "DstroyMenuOptions.h"
#include "DstroyGlobals.h"

DstroyMenuGP2XCommands::DstroyMenuGP2XCommands(void)
{
}

DstroyMenuGP2XCommands::~DstroyMenuGP2XCommands(void)
{
}

bool DstroyMenuGP2XCommands::init(void)
{
#ifdef GP2X
	if (!DstroyMenu::init())
		return false;

	options.load();

	TGISurface* pSurface = NULL;


	pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("controls.pcx"));
	this->setBackground(pSurface);
	pSurface = NULL;

	DstroyMenuItem item;
	writeText("MODE 1", 65, 120, TAcenter, &item);
	item.nId = 1;
	pManager->vecMenuItem.push_back(item);
	writeText("MODE 2", 160, 120, TAcenter, &item);
	item.nId = 2;
	pManager->vecMenuItem.push_back(item);
	writeText("MODE 3", 320-65, 120, TAcenter, &item);
	item.nId = 3;
	pManager->vecMenuItem.push_back(item);

	pManager->vecMenuItem[0].pRight = &(pManager->vecMenuItem[1]);
	pManager->vecMenuItem[1].pRight = &(pManager->vecMenuItem[2]);

	pManager->vecMenuItem[1].pLeft = &(pManager->vecMenuItem[0]);
	pManager->vecMenuItem[2].pLeft = &(pManager->vecMenuItem[1]);


	pManager->vecMenuItem[TGIGlobals::nGP2XmvtMode-1].select(true);
	pManager->pSelectedItem = &(pManager->vecMenuItem[TGIGlobals::nGP2XmvtMode-1]);
	return true;
#else
	return false;
#endif
}

void DstroyMenuGP2XCommands::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{
#ifdef GP2X
	if (pMessage->lId == 10)
	{
		//if (pItem->nId == 1)
		{
			options.nGP2XmvtMode = pItem->nId;
			options.save();

			TGIGlobals::nGP2XmvtMode = options.nGP2XmvtMode;
			
			stop();
			DstroyMenuOptions* pMenu = new DstroyMenuOptions;
		}
	}
#endif
}