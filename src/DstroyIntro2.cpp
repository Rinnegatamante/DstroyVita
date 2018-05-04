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
#include "DstroyIntro2.h"

#include "DstroyGlobals.h"

#include "DstroyMenuMain.h"

DstroyIntro2::DstroyIntro2(void)
{
}

DstroyIntro2::~DstroyIntro2(void)
{
}

bool DstroyIntro2::init(void)
{
	if (!TGIMain::init())
		return false;

	TGISurface* pSurface;
	
	TGIGlobals::playMusic(DstroyGlobals::addResText("starwars.mod"), 1);

	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(DstroyGlobals::addResText("l1.pcx"));
	
	font.setSurface(pSurface);
	font.importFixedFont(true, 0, 0, 320, 8*7, 8, 8);
	font.importFixedFont(false, 0, 8*7, 320, 8*7, 8, 8);
	pSurface = NULL;

	pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("lf2.pcx"));
	setBackground(pSurface);

	nSpeed = 0;

	TGIint y = 240;
	font.writeText("EPISODE 1 DOT 3.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE RE-RECONQUEST", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE INFAMOUS DARK BAVOR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("HAS MADE HIS DREAMS OF", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("CONQUEST TRUE AND IS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ABOUT TO MOLD THE WORLD", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TO HIS IMAGE..!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("IN THE SHADOWS,", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE RESISTANCE IS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("GROWING STRONGER AND", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE BOODIES ARE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("PREPARING A", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("COUNTER-ATTACK", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TO FREE THEIR COUNTRY", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("OF THE VILE INVADING", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("MEURIES.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THEIR HOPES RESIDE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ON A SQUAD OF YOUNG", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("SOLDIERS WITH THE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("UNIQUE ABILITY TO", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("LAY BOMBS TO DESTROY", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE ENEMY.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("AS A SOLDIER IN THIS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("SQUAD, YOU MUST BRAVE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ALL DANGERS TO RETURN", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("BOODLAND ITS GLORY AS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("A COUNTRY WHERE THE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("SUN BRINGS STRAWBERRY", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("CHOCOLATE TO LIFE.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("IN THE FACE OF DEATH,", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ARMED ONLY WITH COURAGE...", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("BUT WITHOUT ARMS...", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("YOU ARE READY TO", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("FIGHT AGAINST THE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("HORDES OF SLIMY MEURIES!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("GOOD LUCK!!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("AND YES, YOU'VE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ALREADY DONE THAT", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TEN YEARS AGO..", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("YOU'VE ALREADY DEFEATED", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DARK BAVOR, YOU'RE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("THE STRONGEST!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("BUT HE TRAVELED BACK", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("IN TIME AND EVERYTHING", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("STARTED OVER AGAIN.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("WHAT ARE YOU WAITING", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("FOR? GO, NOW!", 160, y, TAcenter, 1, NULL, true); y += 13;


	return true;
}

bool DstroyIntro2::events(void)
{
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 

	itObject = getFirstObject();

	TGIint maxPos = itObject->first->Y();
	nSpeed++;
	if (nSpeed > 4)
	{
		for (;itObject!=getEndObject();itObject++)
		{
			itObject->first->setY(itObject->first->Y()-1);
			if (itObject->first->Y() > maxPos)
				maxPos = itObject->first->Y();
		}
		nSpeed = 0;
	}

	if (maxPos <= -13)
	{
		
		stop();
		
	}

	return TGIMain::events();
}

bool DstroyIntro2::exit(void)
{
	DstroyMenuMain* pMenu = new DstroyMenuMain;
	TGIGlobals::stopMusic();

	return TGIMain::exit();
}
