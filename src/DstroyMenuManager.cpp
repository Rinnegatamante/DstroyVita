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
#include "DstroyMenuManager.h"

#include "DstroyMenu.h"

DstroyMenuManager::DstroyMenuManager(void)
{
	pSelectedItem = 0;
	ttNextMessage += 300;
}

DstroyMenuManager::~DstroyMenuManager(void)
{
}

void DstroyMenuManager::treatMessage(TGIInputMessage* pMessage)
{
	if (TGITime::getCurrentTime() < ttNextMessage )
		return; 

	ttNextMessage = TGITime::getCurrentTime();
	ttNextMessage += 150;


	if (pSelectedItem)
	{
		pSelectedItem->select(false);
		pSelectedItem = pSelectedItem->doStuff(pMessage);
		pSelectedItem->select(true);
	}
	else
	{
		((DstroyMenu*)TGIGlobals::theMain)->doStuff(NULL, pMessage);
	}
	/*if (pMessage->lId == 10)
	{
		((DstroyMenu*)TGIGlobals::theMain)->doStuff(vecMenuItem[nSelected].nId);
		return;
	}

	vecMenuItem[nSelected].select(false);
	if (pMessage->lId == up)
	{
		nSelected--;
	}
	if (pMessage->lId == down)
	{
		nSelected++;
	}
	nSelected = nSelected%vecMenuItem.size();
	vecMenuItem[nSelected].select(true);*/

	
}
