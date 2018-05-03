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
#include "DstroyTitle.h"

#include "DstroyIntro.h"
#include "DstroyGlobals.h"
#include "DstroyMenuMain.h"

DstroyTitle::DstroyTitle(void)
{
}

DstroyTitle::~DstroyTitle(void)
{
}

bool DstroyTitle::init(void)
{
	if (!TGIMain::init())
		return false;

	/*loadCommands(DstroyGlobals::addResText("commandsgp2x");
	saveCommands(DstroyGlobals::addResText("commandsgp2x");
	loadCommands(DstroyGlobals::addResText("commandsgp2x2");
	saveCommands(DstroyGlobals::addResText("commandsgp2x2");
	loadCommands(DstroyGlobals::addResText("commandsgp2xr");
	saveCommands(DstroyGlobals::addResText("commandsgp2xr");
	loadCommands(DstroyGlobals::addResText("commandsgp2xr2");
	saveCommands(DstroyGlobals::addResText("commandsgp2xr2");*/
	nLevelMinToQuePasa = 251;
	
	sndOrage.loadFile(DstroyGlobals::addResText("orage.wav"));
	//this->playSound(&sndOrage);

	TGISurface* pSurface;
	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(DstroyGlobals::addResText("ld.pcx"));
	
	font.setSurface(pSurface);
	pSurface = NULL;

	TGIuint16 x = 0, y = 0;
	font.importLetter('A', false, x, y, 32, 32); x = 32;
	font.importLetter('B', false, x, y, 60-x, 32); x = 60;
	font.importLetter('C', false, x, y, 83-x, 32); x = 83;
	font.importLetter('D', false, x, y, 113-x, 32); x = 113;
	font.importLetter('E', false, x, y, 139-x, 32); x = 139;
	font.importLetter('F', false, x, y, 170-x, 32); x = 170;
	font.importLetter('G', false, x, y, 196-x, 32); x = 196;
	font.importLetter('H', false, x, y, 224-x, 32); x = 224;
	font.importLetter('I', false, x, y, 245-x, 32); x = 245;
	font.importLetter('J', false, x, y, 268-x, 32); x = 0;
	y += 33;
	font.importLetter('K', false, x, y, 46-x, 32); x = 46;
	font.importLetter('L', false, x, y, 81-x, 32); x = 81;
	font.importLetter('M', false, x, y, 119-x, 32); x = 119;
	font.importLetter('N', false, x, y, 154-x, 32); x = 154;
	font.importLetter('O', false, x, y, 179-x, 32); x = 179;
	font.importLetter('P', false, x, y, 205-x, 32); x = 205;
	font.importLetter('Q', false, x, y, 238-x, 32); x = 238;
	font.importLetter('R', false, x, y, 279-x, 32); x = 0;
	y += 33;
	font.importLetter('S', false, x, y, 26-x, 32); x = 26;
	font.importLetter('T', false, x, y, 57-x, 32); x = 57;
	font.importLetter('U', false, x, y, 88-x, 32); x = 88;
	font.importLetter('V', false, x, y, 116-x, 32); x = 116;
	font.importLetter('W', false, x, y, 157-x, 32); x = 157;
	font.importLetter('X', false, x, y, 195-x, 32); x = 195;
	font.importLetter('Y', false, x, y, 225-x, 32); x = 225;
	font.importLetter('Z', false, x, y, 249-x, 32); x = 249;

	x = 0;
	y = 104;
	font.importLetter('a', false, x, y, 7, 10); x = 7;
	font.importLetter('b', false, x, y, 15-x, 10); x = 15;
	font.importLetter('c', false, x, y, 23-x, 10); x = 23;
	font.importLetter('d', false, x, y, 31-x, 10); x = 31;
	font.importLetter('e', false, x, y, 38-x, 10); x = 38;
	font.importLetter('f', false, x, y, 43-x, 10); x = 43;
	font.importLetter('g', false, x, y, 51-x, 10); x = 51;
	font.importLetter('h', false, x, y, 59-x, 10); x = 59;
	font.importLetter('i', false, x, y, 62-x, 10); x = 62;
	font.importLetter('j', false, x, y, 69-x, 10); x = 69;
	font.importLetter('k', false, x, y, 77-x, 10); x = 77;
	font.importLetter('l', false, x, y, 84-x, 10); x = 84;
	font.importLetter('m', false, x, y, 92-x, 10); x = 92;
	font.importLetter('n', false, x, y, 100-x, 10); x = 100;
	font.importLetter('o', false, x, y, 108-x, 10); x = 108;
	font.importLetter('p', false, x, y, 115-x, 10); x = 115;
	font.importLetter('q', false, x, y, 123-x, 10); x = 123;
	font.importLetter('r', false, x, y, 130-x, 10); x = 130;
	font.importLetter('s', false, x, y, 138-x, 10); x = 138;
	font.importLetter('t', false, x, y, 146-x, 10); x = 146;
	font.importLetter('u', false, x, y, 152-x, 10); x = 152;
	font.importLetter('v', false, x, y, 160-x, 10); x = 160;
	font.importLetter('w', false, x, y, 171-x, 10); x = 171;
	font.importLetter('x', false, x, y, 179-x, 10); x = 179;
	font.importLetter('y', false, x, y, 186-x, 10); x = 186;
	font.importLetter('z', false, x, y, 195-x, 10); x = 195;

	x = 1;
	y = 121;
	font.importLetter('1', false, x, y, 8, 10); x = 9;
	font.importLetter('2', false, x, y, 15-x, 10); x = 16;
	font.importLetter('4', false, x, y, 22-x, 10); x = 22;
	font.importLetter('5', false, x, y, 30-x, 10); x = 30;
	font.importLetter('6', false, x, y, 36-x, 10); x = 36;
	font.importLetter('7', false, x, y, 43-x, 10); x = 43;
	font.importLetter('8', false, x, y, 51-x, 10); x = 51;
	font.importLetter('9', false, x, y, 57-x, 10); x = 57;
	font.importLetter('0', false, x, y, 65-x, 10); x = 65;
	font.importLetter(',', false, x, y, 68-x, 10); x = 68;
	font.importLetter('.', false, x, y, 71-x, 10); x = 71;
	font.importLetter('\'', false, x, y, 75-x, 10); x = 75;
	font.importLetter('"', false, x, y, 83-x, 10); x = 83;
	font.importLetter(':', false, x, y, 87-x, 10); x = 87;
	font.importLetter(';', false, x, y, 92-x, 10); x = 92;
	font.importLetter('?', false, x, y-1, 101-x, 10); x = 101;
	font.importLetter('!', false, x, y, 105-x, 10); x = 105;
	font.importLetter('(', false, x, y, 109-x, 10); x = 109;
	font.importLetter(')', false, x, y, 115-x, 10); x = 115;
	font.importLetter('3', false, x, y, 124-x, 10); x = 124;
	font.importLetter(' ', false, x, y, 132-x, 10); x = 132;

	if (TGIGlobals::bRotateScreen)
	{
		pSurface = new TGISurface;
		pSurface->loadImage(DstroyGlobals::addResText("tgi.pcx"));
		setBackground(pSurface);

		tgNext = TGITime::getCurrentTime();
		tgNext += 5000;
		nEtape = 0;
	}
	else
	{
		pSurface = new TGISurface;
		pSurface->loadImage(DstroyGlobals::addResText("fbs.pcx"), true);
		tgNext = TGITime::getCurrentTime();
		tgNext += 3000;
		nEtape = 1;

		setBackground(pSurface);

		
	}


	return true;
}

bool DstroyTitle::events(void)
{
	if (tgNext < TGITime::getCurrentTime())
	{
		TGISurface* pSurface;

		nEtape++;
		deleteAllObjects();
		switch(nEtape)
		{
		case 1:
			setBackground(NULL);
			pSurface = new TGISurface;
			pSurface->loadImage(DstroyGlobals::addResText("fbs.pcx"));
			setBackground(pSurface);
			tgNext = TGITime::getCurrentTime();
			tgNext += 3000;
			break;
		case 2:
			setBackground(NULL);
			font.writeText("and", TGIGlobals::screenWidth/2, TGIGlobals::screenHeight/2, TAcenter, 0, NULL);
			tgNext = TGITime::getCurrentTime();
			tgNext += 1000;
			break;
		case 3:
			pSurface = new TGISurface;
			pSurface->loadImage(DstroyGlobals::addResText("chassin.pcx"), true);
			setBackground(pSurface);
			tgNext = TGITime::getCurrentTime();
			tgNext += 3000;
			break;
		case 4:
			setBackground(NULL);
			font.writeText("present", TGIGlobals::screenWidth/2, TGIGlobals::screenHeight/2, TAcenter, 0, NULL);
			tgNext = TGITime::getCurrentTime();
			tgNext += 2000;
			break;
		case 5:
			sndOrage.play();
			pSurface = new TGISurface;
			pSurface->loadImage(DstroyGlobals::addResText("dstroy.pcx"), true);
			setBackground(pSurface);
			tgNext = TGITime::getCurrentTime();
			tgNext += 7000;
			break;
		case 6:
			stop();
		}
	}

	return TGIMain::events();
}

bool DstroyTitle::exit(void)
{
#ifndef __NDS__     
	DstroyIntro* pIntro = new DstroyIntro;
#else
	DstroyMenuMain* pMenu = new DstroyMenuMain;
#endif

	return TGIMain::exit();
}
