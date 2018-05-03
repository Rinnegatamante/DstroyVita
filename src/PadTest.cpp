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
#include "PadTest.h"
#include "PadTestItem.h"

#include "DstroyGlobals.h"

#include "DstroyMenuOptions.h"

PadTest::PadTest(void)
{
}

PadTest::~PadTest(void)
{
}

bool PadTest::init(void)
{
	if (!TGIMain::init())
		return false;

	TGISurface* pSurfaceText;
	pSurfaceText = new TGISurface;
	pSurfaceText->setInvisibleColor(0, 0, 0);
	pSurfaceText->loadImage(DstroyGlobals::addResText("l1.pcx"));
	
	font.setSurface(pSurfaceText);
	font.importFixedFont(true, 0, 0, 320, 8*7, 8, 8);
	font.importFixedFont(false, 0, 8*7, 320, 8*7, 8, 8);

	font.writeText("Press Start to go back", 160, 180, TAcenter, 0, NULL);

	TGISurface* pSurface;
	TGISprite spriteNon, spriteOui;
	PadTestItem* pObject;
	
	pSurface = new TGISurface;
	pSurface->createPlainSurface(16, 16, 255, 0, 0);
	vecSurface.push_back(pSurface);
	spriteOui.setSurface(vecSurface[vecSurface.size()-1]);
	spriteOui.setPlacement(0, 0, 16, 16);

	pSurface = new TGISurface;
	pSurface->createPlainSurface(16, 16, 0, 0, 255);
	vecSurface.push_back(pSurface);
	spriteNon.setSurface(vecSurface[vecSurface.size()-1]);
	spriteNon.setPlacement(0, 0, 16, 16);

	pObject = new PadTestItem;
	pObject->addSprite(spriteOui);
	pObject->addSprite(spriteNon);
	pObject->setPos(160-30-8, 120-8);
	pObject->lId = 1;
	pObject->bVisible = true;
	pObject->bFixedOnScreen = true;
	addObject(pObject, 1);

	pObject = new PadTestItem;
	pObject->addSprite(spriteOui);
	pObject->addSprite(spriteNon);
	pObject->setPos(160-8, 120+30-8);
	pObject->lId = 2;
	pObject->bVisible = true;
	pObject->bFixedOnScreen = true;
	addObject(pObject, 1);

	pObject = new PadTestItem;
	pObject->addSprite(spriteOui);
	pObject->addSprite(spriteNon);
	pObject->setPos(160+30-8, 120-8);
	pObject->lId = 3;
	pObject->bVisible = true;
	pObject->bFixedOnScreen = true;
	addObject(pObject, 1);

	pObject = new PadTestItem;
	pObject->addSprite(spriteOui);
	pObject->addSprite(spriteNon);
	pObject->setPos(160-8, 120-30-8);
	pObject->lId = 4;
	pObject->bVisible = true;
	pObject->bFixedOnScreen = true;
	addObject(pObject, 1);

	TGIInputMessage message;

	//gp2x
	message.reset();
	message.lId	= left;
	message.lIdRecipient = 1;
	message.buttonEvent.button = GP2X_BUTTON_LEFT;
	message.buttonEvent.which = 0;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= down;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_DOWN;
	message.buttonEvent.which = 0;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= right;
	message.lIdRecipient = 3;
	message.buttonEvent.button = GP2X_BUTTON_RIGHT;
	message.buttonEvent.which = 0;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= up;
	message.lIdRecipient = 4;
	message.buttonEvent.button = GP2X_BUTTON_UP;
	message.buttonEvent.which = 0;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	//pc
	message.reset();
	message.lId	= left;
	message.lIdRecipient = 1;
	message.sdlKey = SDLK_LEFT;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= down;
	message.lIdRecipient = 2;
	message.sdlKey = SDLK_DOWN;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= right;
	message.lIdRecipient = 3;
	message.sdlKey = SDLK_RIGHT;
	message.bAutofire = true;
	vecInputMessage.push_back(message);

	message.reset();
	message.lId	= up;
	message.lIdRecipient = 4;
	message.sdlKey = SDLK_UP;
	message.bAutofire = true;
	vecInputMessage.push_back(message);
	

	return true;
}

bool PadTest::exit(void)
{
	DstroyMenuOptions* pMenu = new DstroyMenuOptions;

	return TGIMain::exit();
}
