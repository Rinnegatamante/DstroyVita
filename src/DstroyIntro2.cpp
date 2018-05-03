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
	font.writeText("EPISODE UN POINT TROIS.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("LA RERECONQUETE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("L'INFAME DARK BAVOR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("VIENT ENFIN DE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("REALISER SES REVES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DE CONQUETES ET S'", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("APPRETE A FORMALISER", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TOUT L'UNIVERS...!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("MAIS DEJA,", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("LA RESISTANCE S'", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ORGANISE ET LES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("REBELLES BOODIES SE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("PREPARENT A LANCER", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("UNE CONTRE ATTAQUE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("POUR DELIVRER LEUR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("CHER PAYS DE L'", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ENVAHISSEUR MEURIES.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("POUR CELA,", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ILS COMPTENT SUR UNE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ESCOUADE DE JEUNES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("SOLDATS QUI ONT LE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("POUVOIR DE PONDRE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DES BOMBES POUR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("EXTERMINER L'ENNEMI.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("VOUS FAITES PARTIE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DE CETTE ESCOUADE DE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("REBELLES BOODIES QUI", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DOIT AFFRONTER TOUS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("LES DANGERS POUR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("QUE BOODLAND", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("REDEVIENNE A NOUVEAU", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("UN PAYS OU LE SOLEIL", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("RAVIVE DE SES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("RAYON LA JOIE ET LE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("CHOCOLAT AU FRAISE.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("VOUS VOICI DONC", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DEVANT L'ENNEMI!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("N'AYANT QUE VOTRE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("COURAGE ENTRE LES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("MAINS...MEME SI VOUS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("REMARQUEZ QUE VOUS", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("N'AVEZ PAS DE MAINS!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("VOUS ETES PRET", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("A AFFRONTER CE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TERRIBLE ADVERSAIRE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("QUE SONT LES HORDES", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DE MEURIES BAVEUX...", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("BONNE CHANCE!", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("OUI OK VOUS L'AVEZ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DEJA FAIT IL Y A DIX", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ANS. VOUS AVEZ DEJA ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("BATTU DARK BAVOR ET", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("VOUS ETES LE PLUS FORT", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("SEULEMENT DARK BAVOR", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("EST REMONTE DANS LE", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("TEMPS ET A TOUT ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("RECOMMENCE.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText(" ", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("DONC ON Y VA.", 160, y, TAcenter, 1, NULL, true); y += 13;
	font.writeText("ALLEZ ALLEZ.", 160, y, TAcenter, 1, NULL, true); y += 13;


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
