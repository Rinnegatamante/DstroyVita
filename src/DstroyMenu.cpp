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
 
#include <vitasdk.h>
#include "DstroyMenu.h"

#include "DstroyGlobals.h"

DstroyMenu::DstroyMenu(void)
{
	pManager = NULL;
}

DstroyMenu::~DstroyMenu(void)
{
}

bool DstroyMenu::init(void)
{
	if (!TGIMain::init())
		return false;
	
#ifdef GP2X
	if (TGIGlobals::bRotateScreen)
	{
		loadCommands(DstroyGlobals::addResText("commandsgp2xr"));
	}
	else
	{
		loadCommands(DstroyGlobals::addResText("commandsgp2x"));
	}
#endif

	if ( !loadCommands(DstroyGlobals::addConfigText("commands")) )
	{
		loadCommands(DstroyGlobals::addResText("commands"));
	}

	pManager = new DstroyMenuManager;
	pManager->lId = 1;
	addObject(pManager, 1);
	
	TGISurface* pSurfaceText;
	pSurfaceText = new TGISurface;
	pSurfaceText->setInvisibleColor(0, 0, 0);
	pSurfaceText->loadImage(DstroyGlobals::addResText("l1.pcx"));
	
	font.setSurface(pSurfaceText);
	font.importFixedFont(true, 0, 0, 320, 8*7, 8, 8);
	font.importFixedFont(false, 0, 8*7, 320, 8*7, 8, 8);

	addScreen(0, 0, TGIGlobals::screenWidth, TGIGlobals::screenHeight, 0, 0, TGIGlobals::screenWidth, TGIGlobals::screenHeight, NULL);

	TGIInputMessage message;
	message.lId	= up;
	message.lIdRecipient = 1;
	message.bAutofire = false;
	message.sdlKey = SCE_CTRL_UP;
	vecInputMessage.push_back(message);

	message.lId	= down;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_DOWN;
	vecInputMessage.push_back(message);

	message.lId	= left;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_LEFT;
	vecInputMessage.push_back(message);

	message.lId	= right;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_RIGHT;
	vecInputMessage.push_back(message);

	message.lId	= 10;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_CROSS;
	vecInputMessage.push_back(message);
	return true;
}

void DstroyMenu::writeText(std::string cstrText , TGIint x, TGIint y, TextAlign align, DstroyMenuItem* pItem)
{
	if (pItem)
	{
		pItem->vecObject.clear();
	}

	if (pItem)
	{
		font.writeText(cstrText, x, y, align, 0, &(pItem->vecObject));
	}
	else
	{
		font.writeText(cstrText, x, y, align, 0, NULL);
	}
}

void DstroyMenu::doStuff(DstroyMenuItem* pItem, TGIInputMessage* pMessage)
{

}

bool DstroyMenu::eraseText(DstroyMenuItem* pItem)
{
	for (unsigned int i=0;i<pItem->vecObject.size();i++)
	{
		TGIGlobals::theMain->deleteObject(pItem->vecObject[i]);
	}

	return true;
}
