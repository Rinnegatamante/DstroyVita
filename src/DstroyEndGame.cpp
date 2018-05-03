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
		font.writeText("BRAVO BOODIES BLEU", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("TA VAILLANCE ET TON COURAGE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("T'ONT PERMIS D'EVITER TOUT LES", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("PIEGES QUE CES HORDES DE MEURIES", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AVAIENT LACHEMENT TENDU POUR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("T'EMPECHER DE LIBERER TON PAYS.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAINTENANT, TOUS LES GENERATEURS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("DE MEURIES ONT ETE DETRUITS, ET", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("TOUTES LES CONTREES SONT DE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("NOUVEAU OCCUPEES PAR LES TIENS...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAIS IL FAUT RESTER VIGILANT CAR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("DARK BAVOR PEUT, LUI AUSSI,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOULOIR A NOUVEAU SE VENGER DE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("CETTE DEFAITE HUMILIANTE QUE TU", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("LUI A INFLIGE.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAIS SAVOURE TA VICTOIRE, GRAND", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("BOODIES, CAR TON PAYS EST BEL", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ET BIEN LIBRE A NOUVEAU.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("LES AUTRES BOODIES SONT HEUREUX,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("LE SOLEIL REAPPARAIT A L'HORIZON...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ET SES RAYONS RECHAUFFENT TON", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("COEUR DE GUERRIER.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
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
		font.writeText("BRAVO BOODIES.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 2, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOTRE PARFAITE COLLABORATION ENTRE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOUS VOUS ONT PERMIS D'EVITER TOUT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("LES PIEGES QUE CES HORDES DE MEURIES", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("AVAIENT LACHEMENT TENDU POUR VOUS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("EMPECHER DE LIBERER VOTRE PAYS.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAINTENANT, TOUS LES GENERATEURS", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("DE MEURIES ONT ETE DETRUITS, ET", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("TOUTES LES CONTREES SONT DE NOUVEAUX", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("OCCUPEES PAR LES VOTRES...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAIS IL FAUT RESTER VIGILANT CAR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("DARK BAVOR PEUT, LUI AUSSI,", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOULOIR SE VENGER DE LA DEFAITE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HUMILIANTE QUE VOUS LUI AVEZ", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("INFLIGE A LUI ET SES TROUPES.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("MAIS POUR LE MOMENT, SAVOUREZ VOTRE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VICTOIRE, VALEUREUX BOODIES, CAR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOTRE PAYS EST BEL ET BIEN LIBRE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("A NOUVEAU. LES AUTRES BOODIES SONT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("HEUREUX, LE SOLEIL REAPARAIT A", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("L'HORIZON...", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("ET SES RAYONS RECHAUFFENT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
		font.writeText("VOS COEUR DE GRAND GUERRIER.", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
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
	font.writeText("DSTROY A ETE DEVELOPPE A L'ORIGINE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("SOUS DOS PAR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("NICOLAS RIVIERE", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("ANDRE RIEUSSEC", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("JEROME ANGELOT", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("DAVID GALLO", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("REDEVELOPPE AVEC LIBSDL", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("SOUS WINDOWS, MAC, DS, LINUX PAR", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
	font.writeText("MICHAEL DOGUET", TGIGlobals::screenWidth/2, nPos+=nStep, TAcenter, 0, NULL);
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
