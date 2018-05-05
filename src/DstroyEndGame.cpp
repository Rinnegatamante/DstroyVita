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
#include "DstroyEndGame.h"

#include "DstroyGame.h"
#include "DstroyMenuMain.h"


DstroyEndGame::DstroyEndGame(void)
{
}

DstroyEndGame::~DstroyEndGame(void)
{
}

bool DstroyEndGame::init(void)
{
	if (!TGIMain::init())
		return false;

	TGIGlobals::playMusic(DstroyGlobals::addResText("undersea.mod"));

	

	
	
	

	TGISurface* pSurfaceText;
	pSurfaceText = new TGISurface;
	pSurfaceText->setInvisibleColor(0, 0, 0);
	pSurfaceText->loadImage(DstroyGlobals::addResText("l1.pcx"));
	
	font.setSurface(pSurfaceText);
	font.importFixedFont(true, 0, 0, 320, 8*7, 8, 8);
	font.importFixedFont(false, 0, 8*7, 320, 8*7, 8, 8);

	addScreen(0, 0, TGIGlobals::screenWidth, TGIGlobals::screenHeight, 0, 0, TGIGlobals::screenWidth, TGIGlobals::screenHeight, NULL);

	TGIuint16 nPos = TGIGlobals::screenHeight;
	TGIuint8 nStep = 10;

	TGISurface* pSurface = new TGISurface;
	if (DstroyGame::params.nPlayers == 1)
	{
		pSurface->loadImage(DstroyGlobals::addResText("v1.pcx"));
		font.writeText("CONGRATULATIONS, BLUE BOODIES!", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 2, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("YOUR BRAVERY AND COURAGE HAS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ALLOWED YOU TO COUNTER ALL THE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("TRAPS THAT THE MEURIES SET OUT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("FOR YOU TO PREVENT YOU FROM", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("FREEING YOUR COUNTRY.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ALL THE MEURIES GENERATORS HAVE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BEEN DESTROYED, AND THE COUNTRY", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("IS ONCE AGAIN A SAFE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HAVEN FOR BOODIES...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BUT YOU MUST STAY ALERT,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AS DARK BAVOR CAN, TOO,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("WANT TO ENACT REVENGE ON THE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HUMILIATING DEFEAT THAT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HE AND HIS TROOPS SUFFERED!", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BUT, FOR NOW, ENJOY YOUR VICTORY,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VALOROUS BOODIES,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BECAUSE YOUR COUNTRY IS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ONCE AGAIN FREE.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("THE OTHER BOODIES ARE HAPPY AND", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("THE SUN RISES ONCE AGAIN...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AND ITS RAYS WARM UP YOUR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("GREAT WARRIOR HEART.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	}
	else
	{
		switch(DstroyGame::params.nPlayers)
		{
		case 2:
			pSurface->loadImage(DstroyGlobals::addResText("v2.pcx"));
			break;
		case 3:
			pSurface->loadImage(DstroyGlobals::addResText("v3.pcx"));
			break;
		case 4:
			pSurface->loadImage(DstroyGlobals::addResText("v4.pcx"));
			break;
		} 
			font.writeText("CONGRATULATIONS, BOODIES!", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("YOUR PERFECT TEAMWORK HAS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ALLOWED YOU TO COUNTER ALL", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("THE TRAPS THAT THE MEURIES", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("SET OUT FOR YOU TO PREVENT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("YOU FROM FREEING YOUR COUNTRY.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ALL THE MEURIES GENERATORS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HAVE BEEN DESTROYED,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AND THE COUNTRY IS ONCE AGAIN", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("A SAFE HAVEN FOR BOODIES...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BUT YOU MUST STAY ALERT,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AS DARK BAVOR CAN, TOO,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("WANT TO ENACT REVENGE ON THE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HUMILIATING DEFEAT THAT HE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AND HIS TROOPS SUFFERED!", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BUT, FOR NOW, ENJOY YOUR VICTORY,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VALOROUS BOODIES,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BECAUSE YOUR COUNTRY IS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ONCE AGAIN FREE.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("THE OTHER BOODIES ARE HAPPY AND", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("THE SUN RISES ONCE AGAIN...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AND ITS RAYS WARM UP YOUR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("GREAT WARRIOR HEART.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	}

	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("DSTROY WAS ORIGINALLY", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("DEVELOPED FOR DOS BY", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("NICOLAS RIVIERE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("ANDRE RIEUSSEC", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("JEROME ANGELOT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("DAVID GALLO", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("RE-DEVELOPPED WITH LIBSDL", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("FOR WINDOWS, MAC, LINUX, NDS BY", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("MICHAEL DOGUET", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("PLAYSTATION VITA PORT BY", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("RINNEGATAMANTE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("SPECIAL THANKS TO", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("RSN8887", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("USINEUR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("HtheB", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("XY2_", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("OCORNUT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("THANK YOU FOR PLAYING!", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText(" ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);

	this->setBackground(pSurface);
	pSurface = NULL;

	nSpeed = 0;

	return true;
}

bool DstroyEndGame::events(void)
{
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	TGIint maxPos;

	itObject = getFirstObject();

	maxPos = itObject->first->Y();
	nSpeed++;
	if (nSpeed > 5)
	{
		for (;itObject!=getEndObject();itObject++)
		{
			itObject->first->setY(itObject->first->Y()-1);
			if (itObject->first->Y() > maxPos)
				maxPos = itObject->first->Y();
		}
		nSpeed = 0;
	}

	/*if (maxPos <= 0)
	{
		TGIGlobals::stopMusic();
		stop();
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}*/

	return true;
}
